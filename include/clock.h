/**
 * @file clock.h
 * Definitions relating to the hardware clock and the Xinu clock interrupt.
 *
 * $Id: clock.h 2020 2009-08-13 17:50:08Z mschul $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <queue.h>
#include <stddef.h>

#define CLKTICKS_PER_SEC  1000  /**< clock timer resolution             */
#define RRQUANTUM 10
extern ulong clkticks;          /**< counts clock interrupts            */
extern ulong clktime;           /**< current time in secs since boot    */
extern int rescheduleMSLeft;    /**< ms left before RR schedule         */
extern qid_typ sleepq;          /**< queue for sleeping processes       */
extern ulong msclkticks;        /**< counts clock interruts for ms      */

/* Clock function prototypes */
void clkinit(void);
void clkupdate(ulong);
ulong clkcount(void);
interrupt clkhandler(void);

#endif                          /* _CLOCK_H_ */
