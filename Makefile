KDIR ?=
EXTRA_CFLAGS += -DDEBUG

ifneq ($(KERNELRELEASE),)
	obj-m:= nvme.o
	nvme-objs += nvme_device.o nvme_platform.o nvme_msg.o nvme_debugfs.o
else
default:
	$(MAKE) -C $(KDIR) M=`pwd` modules
endif

clean:
	rm -rf *.o
	rm -rf *.p
	rm -rf *.symvers
	rm -rf *.mod
	rm -rf *.ko
	rm -rf *.order
	rm -rf *.mod.c

