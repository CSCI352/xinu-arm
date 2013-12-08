/**
 * @file insert.c
 * @provides insert.
 *
 * $Id: insert.c 2020 2009-08-13 17:50:08Z mschul $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <thread.h>
#include <queue.h>
#include <schedule.h>

/**
 * Insert a thread into a queue. Order is determined based on
 * current scheduling algorithm.
 * @param tid    thread ID to insert
 * @param q      target queue
 * @param key    sorting key
 * @return OK
 */
int insert(tid_typ tid, qid_typ q, int key)
{
    int next;                   /* runs through list         */
    int prev;                   /* follows next through list */

    if (isbadqid(q) || isbadtid(tid))
    {
        return SYSERR;
    }

    next = quetab[quehead(q)].next;

	// if priority scheduing
	if (SCH_PRIO == SCHEDULER) 
	{
		// find next ps of eq. or higher priority
    	while (quetab[next].key >= key)
    	{
    	    next = quetab[next].next;
    	}
	}

	// if fcfs or round robin
	if (SCH_FCFS == SCHEDULER || SCH_RR == SCHEDULER )
	{	
		// find end of list
    	while (quetab[next].next != EMPTY)
    	{
    	    next = quetab[next].next;
		}
	}
    
	/* insert tid between prev and next */
    quetab[tid].next = next;
    quetab[tid].prev = prev = quetab[next].prev;
    quetab[tid].key = key;
    quetab[prev].next = tid;
    quetab[next].prev = tid;
    return OK;
}
