#include <linux/debugfs.h>
#include <linux/nvme.h>

#include "nvme_device.h"

static struct dentry *nvme_dbg_root;

static char nvme_dbg_reg_ops_buf[256] = "";

static uint8_t *nvme_cmd = NULL;

static uint8_t *prp = NULL;
static dma_addr_t prp_dma = 0;

static ssize_t nvme_dbg_reg_ops_read(struct file *filp, char __user *buffer,
				    size_t count, loff_t *ppos)
{
	//struct nvme_device *ndev = filp->private_data;
	char *buf;
	int len;

	/* don't allow partial reads */
	if (*ppos != 0)
		return 0;

	buf = kasprintf(GFP_KERNEL, "%s: %s\n",
			"info:",
			nvme_dbg_reg_ops_buf);
	if (!buf)
		return -ENOMEM;

	if (count < strlen(buf)) {
		kfree(buf);
		return -ENOSPC;
	}

	len = simple_read_from_buffer(buffer, count, ppos, buf, strlen(buf));

	kfree(buf);
	
	return len;
}

struct nvme_identify* build_nvme_identify(struct nvme_device *ndev, uint16_t command_id,uint32_t nsid,uint32_t cns)
{
	struct nvme_identify *cmd;
	
	if (!nvme_cmd)
		nvme_cmd = kzalloc(sizeof(struct nvme_command), GFP_KERNEL);
	cmd = (struct nvme_identify *)nvme_cmd;
	cmd->opcode = nvme_admin_identify;
	cmd->command_id = cpu_to_be16(command_id&0x3ff);
	cmd->nsid = cpu_to_le32(nsid);
	cmd->cns = cpu_to_le32(cns);
	
	if (!prp) {
		prp = dma_alloc_coherent(&ndev->pdev->dev, PAGE_SIZE, &prp_dma, GFP_KERNEL);
		if (!prp) {
			pr_info("Out of memory prp.\n");
			return NULL;
		}
	}
	memset(prp,0xee,4096);
	cmd->dptr.prp1 = cpu_to_le64(prp_dma);
	cmd->dptr.prp2 = cpu_to_le64(prp_dma);
	
	print_hex_dump(KERN_DEBUG,"Nvme cmd: ",DUMP_PREFIX_OFFSET,16,1,
					(uint8_t *)cmd,sizeof(struct nvme_identify),true);
	
	return cmd;
}

static ssize_t nvme_dbg_reg_ops_write(struct file *filp,
				     const char __user *buffer,
				     size_t count, loff_t *ppos)
{
	struct nvme_device *ndev = filp->private_data;
	int len;

	/* don't allow partial writes */
	if (*ppos != 0)
		return 0;
	
	if (count >= sizeof(nvme_dbg_reg_ops_buf))
		return -ENOSPC;

	len = simple_write_to_buffer(nvme_dbg_reg_ops_buf,
				     sizeof(nvme_dbg_reg_ops_buf)-1,
				     ppos,
				     buffer,
				     count);
	if (len < 0)
		return len;

	nvme_dbg_reg_ops_buf[len] = '\0';

	if (strncmp(nvme_dbg_reg_ops_buf, "reg", 3) == 0) {
		int cnt, reg, val;
		cnt = sscanf(&nvme_dbg_reg_ops_buf[4], "%x %x", &reg, &val);
		if (cnt == 1) {
			val = readl(ndev->bar+reg);
			pr_info("rReg: 0x%x Result: 0x%x\n", reg, val);
		} else if (cnt == 2) {
			writel(val, ndev->bar+reg);
			pr_info("wReg: 0x%x Result: 0x%x\n", reg, val);
		}
	} else if (strncmp(nvme_dbg_reg_ops_buf, "conf", 4) == 0) {
		int cnt, index;
		cnt = sscanf(&nvme_dbg_reg_ops_buf[5], "%x", &index);
		if (cnt == 1) {
			tldrv_fpga_nvme_config(ndev, index);
			pr_info("Config successfully");
		}
	} else if (strncmp(nvme_dbg_reg_ops_buf, "identify", 8) == 0) {
		int cnt, command, nsid, cns;
		struct nvme_identify *cmd;
		cnt = sscanf(&nvme_dbg_reg_ops_buf[9], "%x %x %x", &command, &nsid, &cns);
		if (cnt == 3) {
			cmd = build_nvme_identify(ndev, command, nsid, cns);
			nvme_cmd_send(cmd, sizeof(struct nvme_identify));
			pr_info("Identify cmd send successfully.");
		}
	} else if (strncmp(nvme_dbg_reg_ops_buf, "cq", 2) == 0) {
		int cnnt, num = 1, cnt;
		void *cq;
		
		cnt = sscanf(&nvme_dbg_reg_ops_buf[3], "%d %d", &cnnt, &num);
		if (cnt) {
			if((cnnt + num) > 1024) {
				pr_err("cnnt: %x invalid!\n", cnnt);
			} else {
				for( ; num >0 ; num-- ) {
					cq = fpga_recv_msg_dump(num);
					print_hex_dump(KERN_DEBUG,"Nvme cq: ",DUMP_PREFIX_OFFSET,16,1,
											(uint8_t *)cq, 16, true);
					cnnt++;
				}
			}
		}
	} else {
		pr_info("Unknown command %s\n", nvme_dbg_reg_ops_buf);
		pr_info("Available commands:\n");
		pr_info("   read or send\n");
	}

	return count;
}

static const struct file_operations nvme_dbg_reg_ops_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read =  nvme_dbg_reg_ops_read,
	.write = nvme_dbg_reg_ops_write,
};

void nvme_dbg_adapter_init(struct nvme_device *ndev)
{
	struct dentry *pfile;
	
	ndev->dbg_adapter = debugfs_create_dir("debug", nvme_dbg_root);
	if (ndev->dbg_adapter) {
		pfile = debugfs_create_file("cmd_ops", 0600,
					    ndev->dbg_adapter, ndev,
					    &nvme_dbg_reg_ops_fops);
		if (!pfile)
			pr_err("debugfs cmd_ops for %s failed\n", "nvme");
	} else {
		pr_err("debugfs entry for %s failed\n", "nvme");
	}
}

void nvme_dbg_adapter_exit(struct nvme_device *ndev)
{
	debugfs_remove_recursive(ndev->dbg_adapter);
	ndev->dbg_adapter = NULL;
}

void nvme_dbg_init(void)
{
	nvme_dbg_root = debugfs_create_dir("tldrv_nvme", NULL);
	if (nvme_dbg_root == NULL)
		pr_err("init of debugfs failed\n");
}

void nvme_dbg_exit(void)
{
	debugfs_remove_recursive(nvme_dbg_root);
}
