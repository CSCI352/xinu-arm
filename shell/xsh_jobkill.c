/**
 * File: xsh_jobkill.c
 * Author: Melinda Rabenstein
 * Description:
 *	Take in a Job ID and if that Job exists loop through all
 *	processes registered to that Job and kill each
 */

#include <jobkill.h>

shellcmd xsh_jobkill( int nargs, char *args[] ) {

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
	else if( strncmp( args[1], "--help", 7) == 0 ) {
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

		//If arrayPos is -1 then Job ID entered doesn't exist
		//If arrayPos >= 0 then loop through all processes in Job and kill each
		if( arrayPos > -1 ) {
			Job* job = listOfJobs[arrayPos];
			Process* process;	//Hold current process
			tid_typ pID;		//Thread ID of current process
			
			process = job->headProcess;
			while( process != NULL ) {
				pID = process->dataThreadID;
				
				//If the process is suspended, resume before kill
				struct thrent* threadPointer = process->dataThread;
				if( (int)threadPointer->state == 6 ) {
					resume(pID);
				}

				kill(pID);
				process = process->nextProcess;
			}
		} else {
			fprintf( stderr, "%s: job ID, %s, does not exist\n", args[0], args[1] );
			fprintf( stderr, "Try '%s --help' for more information\n", args[0] );
			return 1;
		}
	}

	return 0;
}
