/*******************************************************************************
 Copyright (C) 2014-2020 TengLing Technologies Co.,Ltd. All Rights Reserved.
--------------------------------------------------------------------------------
 *    Filename: fpga_msg.c
 * Description:
 *     Version: 1.0
 *     Created: 06/01/2020 03:16:07 PM
 *    Revision: none
 *      Author: hj
 *     Company: TengLing Technologies
*******************************************************************************/
#include <linux/types.h>
#include <linux/nvme.h>

#include "nvme_msg.h"

struct mq *gmq;

uint32_t fpga_setup_rx_mq(struct mq *mq)
{
	struct platform_device *pdev = mq->pdev;
	struct mq_rcv *mq_rcv = &mq->rcv;
	dma_addr_t dma;
	void *ptr;
	uint32_t size;

	size = 16*FPGA_MSG_QUEUE_COUNT;
	size = ALIGN(size, 4096);
	ptr = dma_alloc_coherent(&pdev->dev, size, &dma, GFP_KERNEL);
	if(!ptr)
	{
		pr_err("Out of memory for rcv MQ(%d)!\n",size);
		return 1;
	}

	mq_rcv->rcv = (struct msg_rcv *)ptr;

	WRITE_REG(mq->regs + (0x1a<<2), dma&DMA_BIT_MASK(32));
	WRITE_REG(mq->regs + (0x19<<2), dma>>32);
	WRITE_REG(mq->regs + (0x1b<<2), 16);

	return 0;
}

uint32_t fpga_setup_tx_mq(struct mq *mq)
{
	struct platform_device *pdev = mq->pdev;
	struct mq_snd *mq_snd = &mq->snd;
	dma_addr_t dma_snd, dma_tail;
	void *ptr_snd, *ptr_tail;
	uint32_t size;

	size = 64*FPGA_MSG_QUEUE_COUNT;
	size = ALIGN(size, 4096);
	ptr_snd = dma_alloc_coherent(&pdev->dev, size, &dma_snd, GFP_KERNEL);
	if(!ptr_snd) {
		pr_err("Out of memory for snd msg(%d)!\n", size);
		return -1;
	}
	mq_snd->snd = (void *)ptr_snd;

	ptr_tail = dma_alloc_coherent(&pdev->dev, sizeof(struct hw_ttail), &dma_tail, GFP_KERNEL);
	if(!ptr_tail) {
		pr_err("Out of memory for snd pos(%lu)!\n", sizeof(struct hw_ttail));
		dma_free_coherent(&pdev->dev, 64*FPGA_MSG_QUEUE_COUNT, ptr_snd, dma_snd);
		return -1;
	}
	mq_snd->hw_tail = (struct hw_ttail *)ptr_tail;
	
	mq_snd->next_to_write = 0;
	
	WRITE_REG(mq->regs + (0x1f<<2), dma_snd&DMA_BIT_MASK(32));
	WRITE_REG(mq->regs + (0x1e<<2), dma_snd>>32);
	WRITE_REG(mq->regs + (0x20<<2), 64);
	WRITE_REG(mq->regs + (0x22<<2), dma_tail&DMA_BIT_MASK(32));
	WRITE_REG(mq->regs + (0x21<<2), dma_tail>>32);

	return 0;
}

void fpga_enable_mq(struct mq *mq,uint32_t enable)
{
	WRITE_REG(mq->regs + (0x1c<<2), enable);
	WRITE_REG(mq->regs + (0x23<<2), enable);
	
	return;
}

uint32_t fpga_rcv_msg(struct mq *mq,struct nvme_device *ndev)
{
	struct mq_rcv *mq_rcv = &mq->rcv;
	struct msg_rx_hdr *msg_hdr;
	struct msg_rcv *rcv_msg;
	uint32_t rcv_pos;
	uint32_t rcv_num,nr = 0;
	uint16_t command, index;
	struct nvme_completion *cqe;
		
	rcv_msg = mq_rcv->rcv;
	rcv_pos = mq_rcv->rcv_pos;

	rcv_num = FPGA_MSG_QUEUE_COUNT - rcv_pos;
	rcv_num = rcv_num > FPGA_HANDLE_MAX_MSG_COUNT ? FPGA_HANDLE_MAX_MSG_COUNT : rcv_num;

	rcv_msg += rcv_pos;

	while(rcv_num--)
	{
		msg_hdr = &rcv_msg->msg_hdr;

		if(msg_hdr->done != 0xaa)
		{
			break;
		}
		#if 0
		if(unlikely(tldrv_fpga.debug&TLDRV_LOGIC_CMD_DEBUG_MSG_SEQ))
		{
			pr_info("Rcv msg:timestamp 0x%x, seq 0x%x\n", be16_to_cpu(msg_hdr->timestamp), be32_to_cpu(msg_hdr->seq));
		}
		#endif
		if(unlikely(mq_rcv->rcv_seq != be32_to_cpu(msg_hdr->seq))) 
		{
			pr_err("msg seq err now %u Expect %u\n", be32_to_cpu(msg_hdr->seq), mq_rcv->rcv_seq);
			break;
		}

		mq_rcv->rcv_seq++;
		msg_hdr->done = 0;

		//data[nr] = be64_to_cpu(*((uint64_t *)rcv_msg->data));
		//data[nr] = (*((uint64_t *)rcv_msg->data));
		cqe = (struct nvme_completion *)&rcv_msg->data;
		command = be16_to_cpu(cqe->command_id);
		index = (command >> 10)&0xf;
		nvme_process_cq_poll(ndev->dev[index], rcv_msg->data);
		#if 0
		//if(unlikely(tldrv_fpga.debug&TLDRV_LOGIC_CMD_DEBUG_MSG))
		{
			pr_info("[TLDRV]Recv data 0x%llx-0x%llx, %p.\n",data[nr],be64_to_cpu(data[nr]), rcv_msg);
		}
		#endif
		rcv_msg++;
		nr++;
	}
	
	if(!nr) 
	{
		return 0;
	}
	
	mq_rcv->rcv_pos = (rcv_pos+nr)&(FPGA_MSG_QUEUE_COUNT-1);
	smp_wmb();
	WRITE_REG(mq->regs + (0x1d<<2),mq_rcv->rcv_pos);

	return nr;
}

void *fpga_recv_msg_dump(uint32_t index)
{
	struct mq_rcv *mq_rcv = &gmq->rcv;
	struct msg_rcv *rcv_msg;

	rcv_msg = mq_rcv->rcv;

	rcv_msg += index;
	
	return rcv_msg;
}

int fpga_snd_msg(struct mq *mq, void *data, uint32_t len)
{
	uint32_t snd_pos;
	void *msg;
	struct hw_ttail *tail;
	struct mq_snd *mq_snd = &mq->snd;
	
	spin_lock_bh(&mq->mq_lock);
	
	snd_pos = mq_snd->next_to_write;
	tail = mq_snd->hw_tail;
	
	snd_pos = (snd_pos+1)&(FPGA_MSG_QUEUE_COUNT-1);
	if(snd_pos == be32_to_cpu(tail->tail)){
		spin_unlock_bh(&mq->mq_lock);
		pr_err("Fpga send msg is busy. \n");
		return -1;
	}
	
	msg = mq_snd->snd + 64*mq_snd->next_to_write;
	memcpy(msg, data, len);
	smp_wmb();
	mq_snd->next_to_write = snd_pos;
	mq_snd->snd_num++;
	WRITE_REG(mq->regs + (0x24<<2),mq_snd->next_to_write);
	spin_unlock_bh(&mq->mq_lock);
	return 0;
}

void nvme_cmd_send(void *cmd, uint32_t cmd_len)
{
	fpga_snd_msg(gmq, cmd, cmd_len);
}

int create_mq(struct platform_device *pdev, void __iomem *addr)
{
	struct mq *mq;
	
	mq = (struct mq *)kzalloc(sizeof(struct mq), GFP_KERNEL);
	if(!mq){
		pr_err("Out of memory for fpga msg!\n");
		return -1;
	}
	
	/* setup queue */
	mq->pdev = pdev;
	mq->regs = addr;
	
	fpga_setup_rx_mq(mq);
	fpga_setup_tx_mq(mq);

	spin_lock_init(&mq->mq_lock);
	mq->rcv_num = 0;

	gmq = mq;
	
	return 0;
}