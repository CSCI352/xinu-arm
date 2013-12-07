/**
 * File: xsh_jobssuspend.c
 * Author: Marit Brocker (mlb8494@rit.edu)
 * Contributors:
 * Description: (change this later)
 *      This should be linked into signal handling. There are
 *      a couple of different functionalities that need to be implemented,
 *      especially if we support being able to suspend things with signals
 */

//#include <jobsuspend.h>
#include <thread.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
//#include <kernel.h>
//#include <shell.h>
//#include <../system/suspend.c>

shellcmd xsh_jobsuspend( int nargs, char *args[] )
{
    tid_typ tid;	/* tid for thread to suspend */

    /* Output help, if '--help' argument was supplied */
    if( nargs == 2 && strncmp( args[1], "--help", 7 ) == 0)
    {
        printf("Usage: %s <PID>\n\n", args[0]);
        printf("Description:\n");
        printf("\tSuspends the thread the identifier PID.\n");
        printf("Options:\n");
        printf("\t<PID>\tID of thread to suspend.\n");
        printf("\t--help\tdisplay this help and exit\n");
        return 0;
    }

    /* Check for correct number of arguments */
    if( nargs < 2 )
    {
    	fprintf(stderr, "%s: missing operand\n", args[0]);
    	fprintf(stderr, "Try '%s --help' for more information.\n", args[0]);

    	return 1;
    }

    if( nargs > 2 )
    {
    	fprintf(stderr, "%s: too many arguments.\n", args[0]);
    	fprintf(stderr, "Try '%s --help' for more information.\n", args[0]);

    	return 1;
    }

    tid = atoi( args[1] );

    /* Don't try to suspend a null thread */
    if( tid == NULLTHREAD )
    {
    	fprintf( stderr, "%s: (%d) Operation not permitted.\n", args[0], tid);

    	return 1;
    }

    /* If shell is being suspended, print notice to shell. */
    if( tid == gettid() )
    {
    	fprintf( stderr, "%s: Shell suspended.\n", args[0] );
       	sleep(2000);
    }

    /* Suspend thread, nothing is suspend failed. */
    if( suspend( tid ) == SYSERR )
    {
    	fprintf( stderr, "%s : (%d) No such thread.\n", args[0], tid);
    	return -1;
    }

    return 0;

}
