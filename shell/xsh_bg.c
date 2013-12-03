/**
 * File: xsh_bg.c
 * Author: Cody Holley (cmh6807)
 * Contributors: Marit Brocker (mlb8494)
 * Description: (change this later)
 *	(Foreground/Background processes)
 *	Implement shifting processes between levels.
 *	This stage will include testing to make sure signals are
 *	handled correctly, no matter which direction the processes switch
 */
 #include <background.h>

shellcmd xsh_bg( int nargs, char *args[] ) {

	tid_typ tid;	/* tid for thread to move to the background */


	/* Output help, if '--help' argument was supplied */
    if( nargs == 2 && strcmp( args[1], "--help", 7 ) == 0)
    {
        printf("Usage: %s <PID>\n\n", args[0]);
        printf("Description:\n");
		printf("\tMoves the thread with PID to run in the background.\n");
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

	fprintf(stdout, "Sending to Background");
	return 0;
}
