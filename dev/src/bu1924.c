/*
 * bu1924.c
 *
 *  Created on: 03-07-2016
 *      Author: Tomek
 */

#include <dev/bu1924.h>
#include <stm32l476/rcc.h>
#include <stm32l476/gpio.h>
#include <stm32l476/nvic.h>
#include <stm32l476/spi.h>
#include <sys/err.h>
#include <sys/ev.h>
#include <sys/critical.h>

#define DEBUG
#include <dev/debug.h>

/* data received event */
ev_t bu1924_ev;

/* interrupt routine */
void BU1924_Spi2Isr(void)
{
	/* read data */
	bu1924_evarg_t ea = {SPI2->DR};
	/* notify others */
	Ev_Notify(&bu1924_ev, &ea);
}

/* initialize chip support */
int BU1924_Init(void)
{
	/* enter critical mode */
	Critical_Enter();

	/* enable gpiob */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	/* enable spi2 */
	RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;

	/* reset spi2 */
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_SPI2RST;
	/* disable reset */
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_SPI2RST;

	/* reset moder */
	GPIOB->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER15);
	/* set alternate function */
	GPIOB->AFRH |= 5 << (5*4) | 5 << (7*4);
	/* enable pull-ups */
	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR13_0 | GPIO_PUPDR_PUPDR15_0;
	/* enable alternate function */
	GPIOB->MODER |= GPIO_MODER_MODER13_1 | GPIO_MODER_MODER15_1;

	/* set slave mode, slave select always on */
	SPI2->CR1 = SPI_CR1_SSM | SPI_CR1_RXONLY;
	/* enable interrupt generation, select data size: 16b */
	SPI2->CR2 = SPI_CR2_DS| SPI_CR2_RXNEIE;

	/* set priority */
	NVIC_SETINTPRI(STM32_INT_SPI2, 0xff);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_SPI2);

	/* start spi operation */
	SPI2->CR1 |= SPI_CR1_SPE;

	/* exit critical mode */
	Critical_Exit();

	/* report */
	return EOK;
}
