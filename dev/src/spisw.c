/*
 * spisw.c
 *
 *  Created on: 30-06-2015
 *      Author: Tomek
 */

#include <stm32l476/gpio.h>
#include <stm32l476/rcc.h>
#include <sys/err.h>
#include <sys/sem.h>
#include <sys/cb.h>
#include <sys/critical.h>
#include <util/size.h>

/* sem */
sem_t spisw_sem;
/* callback */
//static cb_t callback;

/* do the transfer, output: lsb first, input msb first */
static uint32_t SPISW_TransferByte(uint32_t tx)
{
	/* rx buffer */
	uint32_t rx = 0, i = 8;

	/* transfer bit by bit */
	while (i--) {
		/* set mosi */
		GPIOC->BSRR = tx & 1 ? GPIO_BSRR_BS_8 : GPIO_BSRR_BR_8;
		/* capture strobe */
		GPIOC->BSRR = GPIO_BSRR_BS_9;
		/* get miso */
		rx = rx << 1 | ((GPIOC->IDR & GPIO_IDR_IDR_6) >> 6);
		/* shift */
		tx >>= 1;
		/* clock idle */
		GPIOC->BSRR = GPIO_BSRR_BR_9;
	}

	/* mosi idle */
	GPIOC->BSRR = GPIO_BSRR_BR_8;
	/* report rx */
	return rx;
}

/* software spi */
int SPISW_Init(void)
{
	/* disable interrupts to ensure atomicity of register access */
	Critical_Enter();

	/* enable gpios */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	/* reset gpioa */
	GPIOC->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER8 |
			GPIO_MODER_MODER9);
	/* default state */
	GPIOC->BSRR = GPIO_BSRR_BR_8 | GPIO_BSRR_BR_9;
	/* pull down */
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR6_1;
	/* outputs */
	GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;

	/* restore interrupts */
	Critical_Exit();

	/* release sem */
	Sem_Release(&spisw_sem);

	/* report status */
	return EOK;
}

/* transfer data */
int SPISW_Transfer(void *ptr, size_t size, cb_t cb)
{
	/* data pointer */
	uint8_t *p = ptr;

	/* push every byte */
	while (size--) {
		/* transfer byte */
		*p = SPISW_TransferByte(*p);
		/* next byte */
		p++;
	}

	/* call callback */
	if (cb != CB_NULL)
		cb(0);

	/* report status */
	return EOK;
}
