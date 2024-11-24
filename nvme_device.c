#include <linux/interrupt.h>
#include <linux/of.h>

#include <linux/delay.h>

#include "nvme_device.h"

#define DRIVER_NAME	"tldrv_nvme"

int nvme_debug = 0;
module_param_named(debug_value, nvme_debug, int,
		   S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_value, "Debug commands:\n"
	"\tbit 0x1 - Print ssp\n"
	"\tbit 0x2 - Print cdb\n"
	"\tbit 0x8 - Print allocate and free of tag_id \n"
	"\tbit 0x10 - Print crq");

#ifdef CONFIG_OF
static struct of_device_id tldrv_of_id_table[] = {
	{ .compatible = "tengling,nvme-controlle" },
	{ },
};
MODULE_DEVICE_TABLE(of, tldrv_of_id_table);
#endif

#define R			0
#define W			1

static inline void write_bar(struct nvme_device *ndev, uint32_t addr, uint32_t val, uint32_t index)
{
	addr = (addr<<8) | (index<<3) | (1<<2) | (W<<1) | 1;
	WRITE_REG(ndev->bar + (0x25<<2),addr);
	WRITE_REG(ndev->bar + (0x26<<2), val);
}

static inline void write_cfg(struct nvme_device *ndev, uint32_t addr, uint32_t val, uint32_t index)
{
	addr = (addr<<8) | (index<<3) | (0<<2) | (W<<1);
	WRITE_REG(ndev->bar + (0x25<<2),addr);
	WRITE_REG(ndev->bar + (0x26<<2), val);
}

int tldrv_fpga_nvme_config(struct nvme_device *ndev, uint32_t index)
{
	write_cfg(ndev,0x4,0x00100507,index);
	
	write_cfg(ndev,0xb0,0x8010c011,index);

	//nvme pcie pci header max payload size;
	//write_cfg(0xc8, 0x2940, to, index, sw);
	
	write_cfg(ndev,0x78, 0x2830, index);


	write_bar(ndev,0x14,0x0,index);

	write_bar(ndev,0x24,0x03ff03ff,index);

	write_bar(ndev,0x28,(0x100000+64*1024*index),index);

	write_bar(ndev,0x2c,0x2,index);

	write_bar(ndev,0x30,(0x900000+16*1024*index),index);

	write_bar(ndev,0x34,0x2,index);
	
	write_bar(ndev,0x14,0x460001,index);
	
	/* MSI-X Table Configuration
	 * And
	 * Refer to pci_write_msi_msg */
	//nvmeq 0
	write_bar(ndev,0x2000,0xfee02004,index);
	write_bar(ndev,0x2004,0x0,index);
	write_bar(ndev,0x2008,0x4022,index);
	write_bar(ndev,0x200c,0x0,index);
	
	//nvmeq 1
	write_bar(ndev,0x2010,0xfee02004,index);
	write_bar(ndev,0x2014,0x0,index);
	write_bar(ndev,0x2018,0x4022,index);
	write_bar(ndev,0x201c,0x0,index);
	
	//nvmeq 2
	write_bar(ndev,0x2020,0xfee02004,index);
	write_bar(ndev,0x2024,0x0,index);
	write_bar(ndev,0x2028,0x4022,index);
	write_bar(ndev,0x202c,0x0,index);

	return 0;
}


static int tldrv_common_setdma(struct nvme_device *ndev)
{
	int ret;
	struct device *dev = &ndev->pdev->dev;

	// Set mask
	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	if (ret) {
		dev_warn(dev, "Warning: failed to set 64 bit PCI DMA mask");
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		if (ret) {
			dev_err(dev, "Failed to set DMA mask");
			return ret;
		}
	}

	// Set max segment size
	dma_set_max_seg_size(dev, DMA_BIT_MASK(32));

	return ret;
}

static int tldrv_nvme_platform_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct nvme_device *ndev;
	int ret;

	dev_info(dev, DRIVER_NAME " platform probe");

	ndev = devm_kzalloc(dev, sizeof(struct nvme_device), GFP_KERNEL);
	if (!ndev)
		return -ENOMEM;

	memset(ndev, 0, sizeof(struct nvme_device));
	ndev->pdev = pdev;

	// Set DMA properties
	ret = tldrv_common_setdma(ndev);
	if (ret)
		goto fail;
#if 0	
	// Reserve and map regions
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	
	dev_info(dev, "Control BAR size: %llu", resource_size(res));

	ndev->bar = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ndev->bar)) {
		ret = PTR_ERR(ndev->bar);
		dev_err(dev, "Failed to map control BAR");
		goto fail;
	}
#else
	ndev->bar = ioremap(0xa0000000,0x10000);
#endif
	create_mq(pdev, ndev->bar);

	//tldrv_fpga_nvme_config(ndev,0);
	//ndev->dev[0] = nvme_probe(pdev,0);
	
	nvme_dbg_adapter_init(ndev);
	
	platform_set_drvdata(pdev, ndev);
	
	return 0;
fail:
	return ret;
}

static int tldrv_nvme_platform_remove(struct platform_device *pdev)
{
	struct nvme_device *ndev = platform_get_drvdata(pdev);
	dev_info(&pdev->dev, DRIVER_NAME " platform remove");
	
	nvme_dbg_adapter_exit(ndev);
	
	return 0;
}

static struct platform_driver tldrv_nvme_platform_driver = {
	.probe = tldrv_nvme_platform_probe,
	.remove = tldrv_nvme_platform_remove,
	.driver = {
		.name = DRIVER_NAME,
		.of_match_table = of_match_ptr(tldrv_of_id_table),
	},
};

static int __init tldrv_nvme_init_module(void)
{
	int ret;
	struct platform_device *pdev;
	
	nvme_dbg_init();
	
	ret = platform_driver_register(&tldrv_nvme_platform_driver);
	if (ret)
		return -1;

	pdev = platform_device_register_simple(DRIVER_NAME, -1, NULL, 0);
	if(IS_ERR(pdev)){
		ret = PTR_ERR(pdev);
		platform_driver_unregister(&tldrv_nvme_platform_driver);
		return -1;
	}
	
	return 0;
}
module_init(tldrv_nvme_init_module);

static void __exit tldrv_nvme_exit_module(void)
{
	nvme_dbg_exit();

	platform_driver_unregister(&tldrv_nvme_platform_driver);
}
module_exit(tldrv_nvme_exit_module);

MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
