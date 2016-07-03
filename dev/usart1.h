/*
 * usart1.h
 *
 *  Created on: 15-04-2016
 *      Author: Tomek
 */

#ifndef DEV_USART1_H_
#define DEV_USART1_H_


#include <util/size.h>
#include <sys/cb.h>
#include <sys/sem.h>

/* semaphore */
extern sem_t usart1_sem;

/* dma interrupt */
void USART1_DMA1Ch4Isr(void);

/* initialize usart1 */
int USART1_Init(void);
/* send data */
int USART1_Send(void *ptr, size_t size, cb_t cb);
/* critical send, does not rely on dma transfers */
int USART1_CriticalSend(const void *ptr, size_t size);

#endif /* DEV_USART1_H_ */
