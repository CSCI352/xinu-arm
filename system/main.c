/**
 * @file     main.c
 * @provides main.
 *
 * $Id: main.c 2070 2009-09-18 22:36:02Z brylow $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <conf.h>
#include <stddef.h>
#include <stdio.h>
#include <ether.h>
#include <thread.h>
#include <device.h>
#include <pty.h>

#ifdef MAIN_HEAD
MAIN_HEAD
#endif

extern void shell(int);
extern int terms[10] = {1,0,0,0,0,0,0,0,0,0};

/*
 * Creates a new pseudoterminal
 * Assigns it the first available ID, up to 10
 * Returns the ID of the new terminal
*/
int newTerm()
{
	// find an open ID to assign the new terminal
	// calling function responsible for checking if full
	int i = 0;
	while (terms[i] != 0) i++;
	terms[i] = 1; // mark slot as assigned
	ready(create // create new terminal in slot
          ((void *)shell, INITSTK, INITPRIO, "PSHELL", 3,
           (i + 1), CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
	return i+1;
}

/*
 * Retrieves whether a given terminal ID contains an active terminal
 * NOTE: arg is terminal ID (as seen by user), NOT terminal index
*/
int isTermActive(int id)
{
	return terms[id-1];
}

/*
 * Sets a terminal's ID to "unassigned"
 * NOTE: arg is terminal ID (as seen by user), NOT terminal index
*/
void deactivate(int id)
{
	terms[id-1] = 0;
}

int main(int argc, char **argv)
{
    int i = 0;

#ifdef TTY1
    /* Associate TTY1 with second serial port. */
    open(TTY1, SERIAL1);
#endif

#ifdef NETHER
    /* Open all ethernet devices */
    for (i = 0; i < NETHER; i++)
    {
        /* Open the underlying ethernet device */
        if (SYSERR == open(ethertab[i].dev->num))
        {
            kprintf
                ("Failed to open ethernet device %s\r\n",
                 ethertab[i].dev->name);
        }
    }
#else
    i = 0;
#endif

    /* Launch one shell process for each TTY device. */
    /* Unless you're awesome. Then launch a ton of shells and multiplex the TTY device! */
#ifdef CONSOLE
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "SHELL0", 3,
           1, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
/*    ready(create
          ((void *)shell, INITSTK, INITPRIO, "PSHELL0", 3,
           2, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "PSHELL1", 3,
           3, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "PSHELL2", 3,
           4, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "PSHELL3", 3,
           5, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "PSHELL4", 3,
           6, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "PSHELL5", 3,
           7, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "PSHELL6", 3,
           8, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "PSHELL7", 3,
           9, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "PSHELL8", 3,
           10, CONSOLE, CONSOLE, CONSOLE), RESCHED_NO);
*/
#endif
#ifdef TTY1
    ready(create
          ((void *)shell, INITSTK, INITPRIO, "SHELL1", 3,
           TTY1, TTY1, TTY1), RESCHED_NO);
#endif
#ifdef MAIN_CALL
MAIN_CALL
#endif
    return 0;
}
