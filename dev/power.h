/*
 * power.h
 *
 *  Created on: 11-06-2016
 *      Author: Tomek
 */

#ifndef DEV_POWER_H_
#define DEV_POWER_H_

/* power level detector init */
int Power_Init(void);
/* sleep mode */
void Power_SleepMode(void);
/* enter stop mode, exit on exti event */
void Power_StopMode(void);

#endif /* DEV_POWER_H_ */
