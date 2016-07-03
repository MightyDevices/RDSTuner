/*
 * main.c
 *
 *      Author: Tomek
 */

#include <stm32l476/rcc.h>
#include <stm32l476/gpio.h>
#include <stm32l476/dma.h>
#include <stm32l476/usart.h>
#include <stm32l476/dfsdm.h>
#include <stm32l476/sai.h>
#include <stm32l476/lptim.h>
#include <stm32l476/spi.h>
#include <dev/watchdog.h>
#include <dev/usart1.h>
#include <dev/systime.h>
#include <dev/cpuclock.h>
#include <dev/power.h>
#include <dev/extimux.h>
#include <dev/spisw.h>
#include <dev/lc72131.h>
#include <dev/buttons.h>
#include <dev/bu1924.h>
#include <rds/rds.h>
#include <sys/time.h>
#include <util/elems.h>

#define DEBUG
#include <dev/debug.h>

/* initial frequency */
static int freq = 96400000;
/* frequency limits */
static int fmin = 87500000, fmax = 108000000;

/* callback */
static void Main_BU1924Callback(void *arg)
{
	/* mape event argument */
	bu1924_evarg_t *ea = arg;
	/* input new data */
	RDS_Input(ea->data, 16);

//	dprintf_i("test = %x\n", ea->data);
}

/* set fm frequency */
static void Main_SetFMFrequency(int hz)
{
	/* convert to prescaler ratio */
	int div = (freq + 10700000) / 25000 / 2;
	/* send command */
	LC72131_SetFMDivisor(div, LC72131_REF_25K);
}

/* keypress support */
static void Main_KeyPressedCallback(void *arg)
{
	/* increment frequency */
	freq += 100000;
	/* wrap frequency */
	if (freq < fmin) freq = fmax;
	if (freq > fmax) freq = fmin;

	/* some debug maybe? */
	dprintf_i("freq = %d\n", freq);
	/* set up tuner pll */
	Main_SetFMFrequency(freq);
}

/* system entry point */
int main(void)
{
	/* initialize watchdog */
	Watchdog_Init();
	/* kick watchdog */
	Watchdog_Kick();

	/* initialize power manager */
	Power_Init();
	/* initialize clock (4MHz) */
	CpuClock_Init();
	/* initialize exti multiplexer */
	ExtiMux_Init();

	/* initialize systime */
	SysTime_Init();
	/* wait for some time */
	SysTime_Delay(1000);

	/* initialize usart1 */
	USART1_Init();
	/* initialize software spi */
	SPISW_Init();
	/* initalize lc72131 */
	LC72131_Init();
	/* initialize button support */
	Buttons_Init();
	/* initialize rds chip support */
	BU1924_Init();

	/* enable tuner */
	LC72131_EnableTuner();
	/* set initial frequency */
	Main_SetFMFrequency(freq);

	/* subscribe for key-press events */
	Ev_RegisterCallback(&buttons_ev, Main_KeyPressedCallback);
	/* subscribe for data received from rds decoder chip */
	Ev_RegisterCallback(&bu1924_ev, Main_BU1924Callback);


	/* main loop */
	while (1) {
		/* kick the dog */
		Watchdog_Kick();
	}

	/* never reached */
	return 0;
}
