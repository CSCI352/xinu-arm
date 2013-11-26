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

int toForeground(pid_t pid) {
	fprintf(stdout, "Sending to Foreground");
	return 0;
}

int toBackground(pid_t pid) {
	fprintf(stdout, "Sending to Background");
	return 0;
}
