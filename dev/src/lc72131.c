/*
 * lc72131.c
 *
 *  Created on: 02-07-2016
 *      Author: Tomek
 */

#include <dev/spisw.h>
#include <stm32l476/gpio.h>
#include <stm32l476/rcc.h>
#include <sys/err.h>
#include <sys/critical.h>

/* device addresses */
#define LC72131_ADDR_IN1					0x28
#define LC72131_ADDR_IN2					0x29
#define LC72131_ADDR_OUT					0x2A

/* in1 register bits */
#define LC72131_IN1_P						0x0000ffff
#define LC72131_IN1_SNS						0x00010000
#define LC72131_IN1_DVS						0x00020000
#define LC72131_IN1_CTE						0x00040000
#define LC72131_IN1_XS						0x00080000
#define LC72131_IN1_R						0x00f00000

/* in2 register bits */
#define LC72131_IN2_IOC1					0x00000001
#define LC72131_IN2_IOC2					0x00000002
#define LC72131_IN2_IO1						0x00000004
#define LC72131_IN2_IO2						0x00000008
#define LC72131_IN2_BO1						0x00000010
#define LC72131_IN2_BO2						0x00000020
#define LC72131_IN2_BO3						0x00000040
#define LC72131_IN2_BO4						0x00000080
#define LC72131_IN2_DOC0					0x00000200
#define LC72131_IN2_DOC1					0x00000400
#define LC72131_IN2_DOC2					0x00000800
#define LC72131_IN2_UL0						0x00001000
#define LC72131_IN2_UL1						0x00002000
#define LC72131_IN2_DZ0						0x00004000
#define LC72131_IN2_DZ1						0x00008000
#define LC72131_IN2_GT0						0x00010000
#define LC72131_IN2_GT1						0x00020000
#define LC72131_IN2_TBC						0x00040000
#define LC72131_IN2_DLC						0x00080000
#define LC72131_IN2_IFS						0x00100000
#define LC72131_IN2_TEST0					0x00200000
#define LC72131_IN2_TEST1					0x00400000
#define LC72131_IN2_TEST2					0x00800000

/* out register bits */
#define LC72131_OUT_C						0x000fffff
#define LC72131_OUT_UL						0x00100000
#define LC72131_OUT_I1						0x00400000
#define LC72131_OUT_I2						0x00800000

/* initialize pll chip */
int LC72131_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable gpios */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	/* reset gpioa */
	GPIOC->MODER &= ~(GPIO_MODER_MODER5);
	/* default state */
	GPIOC->BSRR = GPIO_BSRR_BR_5;
	/* outputs */
	GPIOC->MODER |= GPIO_MODER_MODER5_0;

	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* enable tuner */
void LC72131_EnableTuner(void)
{
	/* io mode */
	uint8_t io = LC72131_ADDR_IN2;
	/* register data to be written */
	uint32_t reg = LC72131_IN2_BO2 | LC72131_IN2_IFS;

	/* set io mode */
	SPISW_Transfer(&io, 1, 0);
	/* ce is high */
	GPIOC->BSRR = GPIO_BSRR_BS_5;
	/* set io mode */
	SPISW_Transfer(&reg, 3, 0);
	/* ce is high */
	GPIOC->BSRR = GPIO_BSRR_BR_5;
}

/* set up fm reception */
void LC72131_SetFMDivisor(uint16_t p, uint8_t ref)
{
	/* io mode */
	uint8_t io = LC72131_ADDR_IN1;
	/* register data to be written */
	uint32_t reg = p | ref | LC72131_IN1_DVS | LC72131_IN1_XS;

	/* set io mode */
	SPISW_Transfer(&io, 1, 0);
	/* ce is high */
	GPIOC->BSRR = GPIO_BSRR_BS_5;
	/* set io mode */
	SPISW_Transfer(&reg, 3, 0);
	/* ce is high */
	GPIOC->BSRR = GPIO_BSRR_BR_5;
}
