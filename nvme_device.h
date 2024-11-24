#ifndef __NVME_DEVICE_H__
#define __NVME_DEVICE_H__

#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/module.h>

#include <linux/device.h>
#include <linux/platform_device.h>

#include <linux/dma-direction.h>
#include <linux/dma-mapping.h>

static inline void WRITE_REG(volatile void __iomem *addr, unsigned int b)
{
	//printk("[Mem Write] reg 0x%px value 0x%x.\n",addr,b);
	*(volatile unsigned int __force *) addr = (b);
}

struct nvme_device {
	void __iomem *bar;
	struct platform_device *pdev;
	struct nvme_dev *dev[16];
	struct dentry *dbg_adapter;
};

int create_mq(struct platform_device *pdev, void __iomem *addr);
void nvme_cmd_send(void *cmd, uint32_t cmd_len);
void *fpga_recv_msg_dump(uint32_t index);
int tldrv_fpga_nvme_config(struct nvme_device *ndev, uint32_t index);
void nvme_dbg_adapter_init(struct nvme_device *ndev);
void nvme_dbg_adapter_exit(struct nvme_device *ndev);
void nvme_dbg_init(void);
void nvme_dbg_exit(void);
void nvme_process_cq_poll(void *dev, void *data);
#endif
