/**
 * @file     xsh_create.c
 * @provides xsh_create
 *
 * A create command for the shell to open a new PTY.
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pty.h>

/**
 * Shell command (create).
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_create(int nargs, char *args[])
{

        /* Output help, if '--help' argument was supplied */
        if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
        {
                printf("Usage: %s\n\n", args[0]);
                printf("Description:\n");
                printf("\tCreates a new pseudoterminal\n");
                printf("Options:\n");
                printf("\t--help\tdisplay this help and exit\n");
                return OK;
        }

        /* Check for correct number of arguments */
        if (nargs > 1)
	{
                fprintf(stderr, "%s: too many arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
        }

        /* Create a new pty, if there is room for another */
	/* Be sure to do this in the hackiest way possible */
	if (ptyCount == ptyMax) {
		printf("Terminal limit reached, no terminal created\n");
	} else {
		ptyCount++;
		printf("Terminal %d created\n", ptyCount);
	}

        return OK;

}

