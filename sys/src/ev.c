/*
 * ev.c
 *
 *  Created on: 07-06-2013
 *      Author: Tomek
 */

#include <sys/critical.h>
#include <sys/ev.h>
#include <sys/err.h>
#include <util/string.h>

/* send notification */
void Ev_Notify(ev_t *ev, void *arg)
{
	cb_t *cb = ev->cb;
	/* max number of callbacks */
	int i = EV_MAXCALLS;

	/* call callbacks */
	while (i--) {
		/* callback present? */
		if (*cb)
			(*cb)(arg);
		/* next callback */
		cb++;
	}
}

/* register callback */
int Ev_RegisterCallback(ev_t *ev, cb_t callback)
{
	/* max number of callbacks, status */
	int i = EV_MAXCALLS, rc = EFATAL;
	/* callback pointer, free callback */
	cb_t *cb = ev->cb, *fcb = 0;

	/* enter critical section */
	Critical_Enter();

	/* look for slot */
	while (i--) {
		/* found free slot */
		if (*cb == 0 && fcb == 0) {
			fcb = cb;
		/* already registered? */
		} else if (*cb == callback) {
			fcb = 0; break;
		}
		/* next element */
		cb++;
	}

	/* found free slot? */
	if (fcb)
		rc = EOK, *fcb = callback;

	/* exit critical section */
	Critical_Exit();

	/* report status */
	return rc;
}

/* unregister callback */
int Ev_UnregisterCallback(ev_t *ev, cb_t callback)
{
	/* max number of callbacks */
	int i = EV_MAXCALLS, rc = EFATAL;
	/* callback pointer, free callback */
	cb_t *cb = ev->cb;

	/* enter critical section */
	Critical_Enter();

	/* look for callback */
	while (i--) {
		/* found callback? */
		if (*cb == callback) {
			/* reset entry */
			*cb = 0, rc = EOK;
			/* end loop */
			break;
		}
		/* next element */
		cb++;
	}

	/* exit critical section */
	Critical_Exit();

	/* report status */
	return rc;
}
