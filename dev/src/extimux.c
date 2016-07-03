/*
 * extimux.c
 *
 *  Created on: 12-06-2016
 *      Author: Tomek
 */

#include <stm32l476/rcc.h>
#include <stm32l476/exti.h>
#include <stm32l476/nvic.h>
#include <stm32l476/syscfg.h>
#include <sys/critical.h>
#include <sys/err.h>

/* routines */
#include <dev/buttons.h>

/* exti interrupt mux for lines 5 to 9 */
void ExtiMux_Exti5_9Isr(void)
{
	/* get pending register */
//	uint32_t pr = EXTI->PR;
}

/* exti interrupt mux for lines 10 to 15 */
void ExtiMux_Exti10_15Isr(void)
{
	/* get pending register */
	uint32_t pr = EXTI->PR1;

//	/* sw2 interrupt line */
//	if (pr & EXTI_PR1_PIF10)
//		Buttons_Exti10Isr();
//
//	/* lis3de interrupt line */
//	if (pr & EXTI_PR1_PIF11)
//		LIS3DE_Exti11Isr();
//
//	/* lps25hb interrupt line */
//	if (pr & EXTI_PR1_PIF14)
//		LPS25HB_Exti14Isr();

	/* user button */
	if (pr & EXTI_PR1_PIF13)
		Buttons_Exti13Isr();
}

/* initialize exti mux */
int ExtiMux_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable syscfg */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* set priority */
	NVIC_SETINTPRI(STM32_INT_EXTI5_9, 0xf0);
	/* enable */
	NVIC_ENABLEINT(STM32_INT_EXTI5_9);

	/* set priority */
	NVIC_SETINTPRI(STM32_INT_EXTI10_15, 0xf0);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_EXTI10_15);

	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}
