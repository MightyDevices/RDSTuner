/*
 * critical.h
 *
 *  Created on: 26-08-2015
 *      Author: Tomek
 */

#ifndef SYS_CRITICAL_H_
#define SYS_CRITICAL_H_

/* critical section counter - used for nesting critical sections */
extern int critical_nesting_cnt;

/* enter critical section */
static inline __attribute__((always_inline)) void Critical_Enter(void)
{
	/* critical section counter - used for nesting critical sections */
	extern int critical_nesting_cnt;

	__asm__ volatile (
		"MSR 	basepri, %0\n"
		:
		: "r" (16)
	);

	/* increment counter */
	critical_nesting_cnt++;
}

/* exit critical section */
static inline __attribute__((always_inline)) void Critical_Exit(void)
{
	/* critical section counter - used for nesting critical sections */
	extern int critical_nesting_cnt;

	/* decrement counter */
	critical_nesting_cnt--;

	/* decrement counter */
	if (critical_nesting_cnt == 0) {
		__asm__ volatile (
			"MSR 	basepri, %0\n"
			:
			: "r" (0)
		);
	}
}


#endif /* SYS_CRITICAL_H_ */
