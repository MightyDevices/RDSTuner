/*
 * watchdog.c
 *
 *  Created on: 12-06-2013
 *      Author: Tomek
 */

#include <stm32l476/wwdg.h>
#include <stm32l476/rcc.h>
#include <stm32l476/nvic.h>
#include <dev/watchdog.h>
#include <sys/err.h>
#include <sys/critical.h>

/* initialize watchdog */
int Watchdog_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* enable watchdog */
	RCC->APB1ENR1 |= RCC_APB1ENR1_WWDGEN;

	/* configure for max interval */
	WWDG->CR = WWDG_CR_WDGA | WWDG_CR_T;
	/* set up prescaler and interrupt */
	WWDG->CFR = WWDG_CFR_EWI | WWDG_CFR_WDGTB | WWDG_CFR_W;

	/* set priority */
	NVIC_SETINTPRI(STM32_INT_WWDG, 0x00);
	/* enable interrupt */
	NVIC_ENABLEINT(STM32_INT_WWDG);

	/* restore interrupts */
	Critical_Exit();

	/* what could possibly go wrong here */
	return EOK;
}

/* kick the dog! */
void Watchdog_Kick(void)
{
	/* reset counter */
	WWDG->CR = WWDG_CR_T;
}
