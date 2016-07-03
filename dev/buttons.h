/*
 * buttons.h
 *
 *  Created on: 14-06-2016
 *      Author: Tomek
 */

#ifndef DEV_BUTTONS_H_
#define DEV_BUTTONS_H_

#include <sys/ev.h>

/* button press event */
extern ev_t buttons_ev;

/* button bits */
/* left button */
#define BUTTON_LEFT							0x01
/* right button */
#define BUTTON_RIGHT						0x02

/* event argument type */
typedef struct {
	/* button mask */
	int mask;
} buttons_evarg_t;

/* sw1 interrupt */
void Buttons_Exti13Isr(void);

/* initialize buttons support */
int Buttons_Init(void);
/* report button status */
int Buttons_GetStatus(void);


#endif /* DEV_BUTTONS_H_ */
