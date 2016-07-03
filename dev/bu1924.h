/*
 * bu1924.h
 *
 *  Created on: 03-07-2016
 *      Author: Tomek
 */

#ifndef DEV_BU1924_H_
#define DEV_BU1924_H_

#include <sys/ev.h>

/* data received event */
extern ev_t bu1924_ev;

/* event argument */
typedef struct {
	uint16_t data;
}  bu1924_evarg_t;

/* interrupt routine */
void BU1924_Spi2Isr(void);
/* initialize chip support */
int BU1924_Init(void);

#endif /* DEV_BU1924_H_ */
