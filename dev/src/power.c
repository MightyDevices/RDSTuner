/*
 * power.c
 *
 *  Created on: 11-06-2016
 *      Author: Tomek
 */

#include <stm32l476/rcc.h>
#include <stm32l476/pwr.h>
#include <stm32l476/gpio.h>
#include <stm32l476/scb.h>
#include <sys/critical.h>
#include <sys/err.h>

/* power level detector init */
int Power_Init(void)
{
	/* disable interrupts to ensure atomicity of register access */
	Critical_Enter();

	/* enable power management */
	RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
	/* enable all gpios for configuring before low power mode */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN |
			RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIODEN | RCC_AHB2ENR_GPIOHEN;

	/* reset all gpios */
	RCC->AHB2RSTR |= RCC_AHB2RSTR_GPIOARST | RCC_AHB2RSTR_GPIOBRST |
			RCC_AHB2RSTR_GPIOCRST | RCC_AHB2RSTR_GPIODRST |
			RCC_AHB2RSTR_GPIOHRST;
	RCC->AHB2RSTR &= ~(RCC_AHB2RSTR_GPIOARST | RCC_AHB2RSTR_GPIOBRST |
			RCC_AHB2RSTR_GPIOCRST | RCC_AHB2RSTR_GPIODRST |
			RCC_AHB2RSTR_GPIOHRST);

	/* reset power manager */
	RCC->APB1RSTR1 |= RCC_APB1RSTR1_PWRRST;
	/* disable reset */
	RCC->APB1RSTR1 &= ~RCC_APB1RSTR1_PWRRST;

	/* set outputs for lowest consumption */
	GPIOA->ODR = 0x0000; GPIOB->ODR = 0x0000;
	/* set outputs for lowest consumption */
	GPIOC->ODR = 0x0000; GPIOD->ODR = 0x0000;
	/* set outputs for lowest consumption */
	GPIOH->ODR = 0x0000;

	/* set for lowest consumption */
	GPIOA->MODER = 0xfd5fffff; GPIOB->MODER = 0xfff7ffff;
	/* set for lowest consumption */
	GPIOC->MODER = 0xffffffff; GPIOD->MODER = 0xffffffff;
	/* set for lowest consumption */
	GPIOH->MODER = 0xffffffff;

	/* set default low power mode, select range1 */
	PWR->CR1 = PWR_CR1_VOS_0 | PWR_CR1_LPMS_STOP2;

	/* restore interrupts */
	Critical_Exit();

	/* report status */
	return EOK;
}

/* sleep mode */
void Power_SleepMode(void)
{
	/* go to sleep, wait for wakeup event */
	__asm__ volatile ("wfi");
}

/* enter stop mode, exit on exti event */
void Power_StopMode(void)
{
	/* Set SLEEPDEEP bit of Cortex System Control Register */
	SCB->SCR |= SCB_SCR_SLEEPDEEP;
	/* go to sleep, wait for wakeup event */
	__asm__ volatile ("wfi");
	/* reset deep sleep bit */
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP;
}
