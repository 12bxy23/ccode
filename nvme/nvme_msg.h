/*******************************************************************************
 Copyright (C) 2014-2020 TengLing Technologies Co.,Ltd. All Rights Reserved.
--------------------------------------------------------------------------------
 *    Filename: fpga_msg.h
 * Description:
 *     Version: 1.0
 *     Created: 06/01/2020 03:16:07 PM
 *    Revision: none
 *      Author: hj
 *     Company: TengLing Technologies
*******************************************************************************/
#ifndef __NVME_MSG_H_
#define __NVME_MSG_H_

#include "nvme_device.h"

#define FPGA_MSG_QUEUE_COUNT		1024
#define FPGA_HANDLE_MAX_MSG_COUNT	32

/* RX MSG HDR */
struct msg_rx_hdr {
	uint8_t done;
	uint8_t unused;
	uint16_t timestamp;
	uint32_t seq;
};

/* RX MSG */
struct msg_rcv {
	struct msg_rx_hdr msg_hdr;
	uint8_t data[8];
};

/* TX64 MSG */
struct msg_tx64 {
	uint8_t data[64];
};

struct hw_ttail {
	uint32_t tail;
};

struct mq_rcv {
	struct msg_rcv *rcv;	/* DMA base address of rx */
	uint32_t rcv_pos;
	uint32_t rcv_seq;
};

struct mq_snd {
	void *snd;				/* DMA base address of tx */
	struct hw_ttail *hw_tail;	/* DMA base address of hw tail*/
	uint32_t next_to_write;
	uint32_t snd_num;
};

struct mq {
	struct platform_device *pdev;
	
	void __iomem *regs;

	struct mq_rcv rcv;
	struct mq_snd snd;

	spinlock_t mq_lock;
	
	uint32_t rcv_num;
};

#endif /* __FPGA_MSG_H_ */
