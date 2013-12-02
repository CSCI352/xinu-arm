/**
 * File: xsh_jobssuspend.c
 * Author: Marit Brocker (mlb8494@rit.edu)
 * Contributors:
 * Description: (change this later)
 *      This should be linked into signal handling. There are
 *      a couple of different functionalities that need to be implemented,
 *      especially if we support being able to suspend things with signals
 */

#include <jobssuspend.h>
#include <thread.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

shellcmd xsh_suspend( int nargs, char *args[] )
{

    /* Output help, if '--help' argument was supplied */
    if( nargs == 2 && strcmp( args[1], "--help", 7 ) == 0)
    {
        printf("Usage: %s <PID>\n\n", args[0]);
        printf("Description:\n");
	printf("\tSuspends the thread the identifier PID.\n");
	printf("Options:\n");
	printf("\t<PID>\tID of thread to suspend.\n");
	printf("\t--help\tdisplay this help and exit\n");
	return 0;
    }
}
