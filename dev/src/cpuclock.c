/*
 * cpuclock.c
 *
 *  Created on: 14-04-2016
 *      Author: Tomek
 */

#include <sys/err.h>
#include <sys/critical.h>
#include <stm32l476/rcc.h>
#include <stm32l476/gpio.h>
#include <stm32l476/flash.h>

/* initialize cpu clock */
int CpuClock_Init(void)
{
	/* enter critical section */
	Critical_Enter();

	/* exit critical section */
	Critical_Exit();

	/* report status */
	return EOK;
}
