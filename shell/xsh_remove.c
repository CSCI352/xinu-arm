/**
 * @file     xsh_remove.c
 * @provides xsh_remove
 *
 * A remove command for the shell to close a PTY.
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pty.h>
/**
 * Shell command (remove).
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_remove(int nargs, char *args[])
{

        /* Output help, if '--help' argument was supplied */
        if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
        {
                printf("Usage: %s\n\n", args[0]);
                printf("Description:\n");
                printf("\tCloses an active pseudoterminal\n");
                printf("Options:\n");
                printf("\t--help\tdisplay this help and exit\n");
                return OK;
        }

        /* Check for correct number of arguments */
        if (nargs == 1)
        {
                fprintf(stderr, "%s: too few arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
        }

	if (nargs > 2)
	{
		 fprintf(stderr, "%s: too many arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n",
                args[0]);
        return SYSERR;
	}

        /* Remove a pty, if it is active */
	int ptyToRemove = atoi(args[1]);

	if (!isTermActive(ptyToRemove))
	{
		printf("Failed to remove: terminal %d is not active\n", ptyToRemove);
	}
	else if (ptyToRemove < 1 || ptyToRemove > ptyMax)
	{
		printf("Failed to remove: invalid terminal number %d\n", ptyToRemove);
	}
	else if (ptyToRemove == activePtyId)
	{
		printf("Failed to remove: Cannot remove current terminal\n");
	}
	else
	{
		printf("Closing terminal %d...\n", ptyToRemove);
		int thisId = activePtyId;
//		activePtyId = ptyToRemove;
//		kill(gettid());
//		activePtyId = thisId;
		deactivate(ptyToRemove); //call to main
		printf("Terminal %d removed.\n", ptyToRemove);
	}

        return OK;

}

