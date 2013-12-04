/**
 * @file     xsh_switch.c
 * @provides xsh_switch
 *
 * A switch command for the shell to switch to a different PTY. 
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pty.h>

/**
 * Shell command (switch).
 * @param nargs  number of arguments in args array
 * @param args   array of arguments
 * @return OK for success, SYSERR for syntax error
 */
shellcmd xsh_switch(int nargs, char *args[])
{
	
	/* Output help, if '--help' argument was supplied */
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
    {
        printf("Usage: %s\n\n", args[0]);
        printf("Description:\n");
        printf("\tSwitches to the given shell\n");
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

	printf("This is the switch command!\n");

	// /* Check the number of the terminal to switch to, and switch if possible */
	//int newpty = atoi(args[1]);

	//if (newpty == activePtyId)
	//{
	//	printf("Already using terminal %d\n", newpty);
	//}
	//else if (newpty > 0)
	//{
	//	ptyPrintf(newpty, "Switching to terminal %d\n", newpty);
	//  activePtyId = newpty;
	//}
	//else
	//{
	//	printf("'%s' is not a valid terminal number\n", args[1]);
	//}

	return OK;

}