/*
 * rds.h
 *
 *  Created on: 03-07-2016
 *      Author: Tomek
 */

#ifndef RDS_RDS_H_
#define RDS_RDS_H_

#include <stdint.h>

/* initialize rds module */
int RDS_Init(void);
/* input binary data */
void RDS_Input(uint32_t data, int bit_num);


#endif /* RDS_RDS_H_ */
