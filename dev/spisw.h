/*
 * spisw.h
 *
 *  Created on: 01-07-2015
 *      Author: Tomek
 */

#ifndef DEV_SPISW_H_
#define DEV_SPISW_H_

#include <util/size.h>
#include <sys/sem.h>
#include <sys/cb.h>

extern sem_t spisw_sem;

/* software spi */
int SPISW_Init(void);
/* deinitialize spi */
int SPISW_Deinit(void);
/* transfer data data */
int SPISW_Transfer(void *ptr, size_t size, cb_t cb);

#endif /* SPISW_H_ */
