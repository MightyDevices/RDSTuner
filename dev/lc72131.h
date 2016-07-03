/*
 * lc72131.h
 *
 *  Created on: 02-07-2016
 *      Author: Tomek
 */

#ifndef DEV_LC72131_H_
#define DEV_LC72131_H_

/* reference frequencies */
#define LC72131_REF_100K					0x00000000
#define LC72131_REF_50K						0x00100000
#define LC72131_REF_25K						0x00200000
#define LC72131_REF_12K5					0x00400000
#define LC72131_REF_6K25					0x00500000
#define LC72131_REF_3K125					0x00600000
#define LC72131_REF_10K						0x00800000
#define LC72131_REF_9K						0x00900000
#define LC72131_REF_5K						0x00A00000
#define LC72131_REF_1K						0x00B00000
#define LC72131_REF_3K						0x00C00000
#define LC72131_REF_15K						0x00D00000

/* initialize pll chip */
int LC72131_Init(void);
/* enable tuner */
void LC72131_EnableTuner(void);
/* set up fm reception */
void LC72131_SetFMDivisor(int p, int ref);


#endif /* DEV_LC72131_H_ */
