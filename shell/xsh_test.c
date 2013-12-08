/**
 * @file     xsh_test.c
 * @provides xsh_test.
 *
 * $Id: xsh_test.c 2070 2009-09-18 22:36:02Z brylow $
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
	// wimpy tests
	// TODO: command line args
	
	//sleep(6000);
    //wait(6000);

	// Time to put on the big boy pants and do a big boy test
	// runtime: ~2 minutes, prints 10 P's and 10 C's
	int childProcess();

	resume(create(childProcess, 200, 20, "child process", 0));

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