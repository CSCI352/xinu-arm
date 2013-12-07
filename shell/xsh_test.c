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
   int i = 0;
    while(TRUE){
	//fprintf( stdout, "yay numbers! %d", i);
    	i++;
	wait(6000);
    }
    return 0;
}
