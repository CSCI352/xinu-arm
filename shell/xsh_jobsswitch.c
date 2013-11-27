/**
 * File: jobswitch.c
 * Author: Cody Holley (cmh6807)
 * Contributors: 
 * Description: (change this later)
 *	(Foreground/Background processes)
 *	Implement shifting processes between levels.
 *	This stage will include testing to make sure signals are
 *	handled correctly, no matter which direction the processes switch
 */

#include <../include/jobsswitch.h>

int toForeground(tid_typ pid) {
	fprintf(stdout, "Sending to Foreground");
	return 0;
}

int toBackground(tid_typ pid) {
	fprintf(stdout, "Sending to Background");
	return 0;
}
