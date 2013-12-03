/**
 * File: xsh_jobskill.c
 * Author:
 * Contributors:
 * Description: (change this later)
 *      Implement shifting processes between levels.
 *      This stage will include testin gto make sure signals
 *      are handled correctly no matter which direction the
 *      processes shift.
 */

#include <jobskill.h>

shellcmd xsh_killjob( int nargs, char *args[] ) {

	/* Check for correct number of arguments */
	if( nargs != 2 ) {
		if( nargs < 2 ) {
			fprintf( stderr, "%s: missing operand\n", args[0] );
			fprintf( stderr, "Try '%s --help' for more information.\n", args[0] );
		} else {
			fprintf( stderr, "%s: too many arguments\n", args[0] );
			fprintf( stderr, "Try '%s --help' for more information\n", args[0] );
		}

		return 1;
	}

	/* Output help, if '--help' argument was supplied */
	else if( strcmp( args[1], "--help", 7) == 0 ) {
		printf( "Usage: %s <PID>\n\n", args[0] );
		printf( "Description:\n" );
			printf( "\tKill all processes in a job grouping\n\n" );
		printf( "Options:\n" );
			printf( "\t<PID>\tID of job to kill\n" );
			printf( "\t--help\tDisplay this help and exit\n" );
	}

	/* Argument was not help, kill all the processes in the job if it exists */
	else {
		int arrayPos = doesJobExist( atoi(args[1]) );

		if( arrayPos > -1 ) {
			Job* job = listOfJobs[arrayPos];
			Process* process;	//Temp process variable
			tid_typ pID;		//Thread ID of current process
			
			process = job->headProcess;
			while( process != NULL ) {
				pID = process->dataThreadID;
				kill(pID);
				process = process->nextProcess;
			}
		} else {
			fprintf( stderr, "%s: job ID, %u, does not exist\n", args[0], args[1] );
			 fprintf( stderr, "Try '%s --help' for more information\n", args[0] );
			return 1;
		}
	}

	return 0;
}
