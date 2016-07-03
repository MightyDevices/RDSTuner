/*
 * buttons.c
 *
 *  Created on: 14-06-2016
 *      Author: Tomek
 */

#include <dev/extimux.h>
#include <dev/buttons.h>
#include <stm32l476/rcc.h>
#include <stm32l476/gpio.h>
#include <stm32l476/syscfg.h>
#include <stm32l476/exti.h>
#include <stm32l476/nvic.h>
#include <sys/err.h>
#include <sys/critical.h>
#include <sys/ev.h>

#define DEBUG
#include <dev/debug.h>

/* button press event */
ev_t buttons_ev;

/* sw1 interrupt */
void Buttons_Exti13Isr(void)
{
	/* clear interrupt */
	EXTI->PR1 = EXTI_PR1_PIF13;

	/* build up event argument */
	buttons_evarg_t ea = {Buttons_GetStatus()};
	/* notify */
	Ev_Notify(&buttons_ev, &ea);
}

/* initialize buttons support */
int Buttons_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable gpios */
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	/* enable syscfg */
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* switch sw2 located @ pd2 */
	GPIOC->MODER &= ~GPIO_MODER_MODER13;

	/* route exti13 to pc */
	SYSCFG->EXTICR4 = (SYSCFG->EXTICR4 & ~SYSCFG_EXTICR4_EXTI13) |
			SYSCFG_EXTICR4_EXTI13_PC;

	/* configure for falling edge detection */
	EXTI->FTSR1 |= EXTI_FTSR1_FT13;
	/* enable interrupts */
	EXTI->IMR1 |= EXTI_IMR1_IM13;

	/* exit critical section */
	Critical_Exit();
	/* report status */
	return EOK;
}

/* report button status */
int Buttons_GetStatus(void)
{
	/* button bit mask */
	int mask = 0;

	/* sw1 - right button */
	if ((GPIOC->IDR & GPIO_IDR_IDR_13) == 0)
		mask |= BUTTON_RIGHT;

	/* report button state */
	return mask;
}
