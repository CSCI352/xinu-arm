/**
 * File: xsh_fg.c
 * Author: Cody Holley (cmh6807)
 * Contributors: Marit Brocker (mlb8494)
 * Description: (change this later)
 *	(Foreground/Background processes)
 *	Implement shifting processes between levels.
 *	This stage will include testing to make sure signals are
 *	handled correctly, no matter which direction the processes switch
 */

#include <foreground.h>

shellcmd xsh_fg( int nargs, char *args[] ) {

	tid_typ tid;	/* tid for thread to move to the foreground */

	/* Output help, if '--help' argument was supplied */
    if( nargs == 2 && strncmp( args[1], "--help", 7 ) == 0)
    {
        printf("Usage: %s <PID>\n\n", args[0]);
        printf("Description:\n");
		printf("\tMove the thread with PID to run in the foreground.\n");
		printf("Options:\n");
		printf("\t<PID>\tID of thread to move.\n");
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

    /* Don't try to move a null thread */
    if( tid == NULLTHREAD )
    {
		fprintf( stderr, "%s: (%d) Operation not permitted.\n", args[0], tid);

		return 1;
    }


	fprintf(stdout, "Sending to Foreground");
	//Resume the job
	if (resume(tid) == SYSERR) {
		return -1;
	} else {
		return 1;
	}

	return 0;
}
