/**
 * @file     xsh_test.c
 * @provides xsh_test.
 *
 * $Id: xsh_test.c 2070 2009-09-18 22:36:02Z brylow $
 *
 * Contributers: Andrew Hollenbach
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Shell command (test) provides a mechanism for testing Xinu features.  The
 * action and output varies depending on the feature currently being tested.
 * This is not meant to serve as a permanent shell command for a particular
 * action.
 * @param nargs number of arguments
 * @param args  array of arguments
 * @return non-zero value on error
 */
shellcmd xsh_test(int nargs, char *args[])
{
	// TODO: Temporarily disabled forking test, because jobgroup doesn't
	// handle this
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0)
    {
        printf("Usage: %s\n\n", args[0]);
        printf("Description:\n");
        printf("\tRuns test programs\n");
        printf("Options:\n");
        printf("\t--help\tdisplay this help and exit\n");
        printf("\t-sleep\truns a program that sleeps for 6 seconds\n");
        printf("\t-wait \truns a program that waits for 6 seconds\n");
        printf("\t-endless \truns an endless loop\n");
        printf("\t-fork \truns a program that forks a child process\n");
        return OK;
    }
    if (nargs < 1)
    {
        fprintf(stderr, "%s: too few arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
        return SYSERR;
    }
    // wimpy tests
    if ((nargs == 2 && strncmp(args[1], "-sleep", 7) == 0) || nargs == 1 )
    {
        sleep(6000);
        return 0;
    }
    if (nargs == 2 && strncmp(args[1], "-wait", 7) == 0 )
    {
        wait(6000);
        return 0;
    }
    if (nargs == 2 && strncmp(args[1], "-endless", 7) == 0 )
    {
        int i = 0;
        while(TRUE){
			i++;
			wait(6000);
		}
		return 0;
    }
    if (nargs == 2 && strncmp(args[1], "-fork", 7) == 0 )
    {
        // Time to put on the big boy pants and do a big boy test
		// runtime: ~2 minutes, prints 10 P's and 10 C's
		int childProcess();

		resume(create(childProcess, 2000, 20, "child process", 0));

		int i = 1000*1000*1000;
		while(i > 0) {
			if(i%(1000*1000*100) == 0) {
				printf("P");
			}

			i--;
		}
		printf("\nparent done");
        return 0;
    }


    return SYSERR;
}

childProcess()
{
	int i = 1000*1000*1000;
	while(i > 0) {
		if(i%(1000*1000*100) == 0) {
			printf("C");
		}

		i--;
	}
	printf("\nchild done");
}