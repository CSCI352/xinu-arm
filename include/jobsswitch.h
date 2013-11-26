/**
 * File: jobswitch.h
 * Author: Cody Holley (cmh6807)
 * Contributors: 
 * Description: (change this later)
 *	(Foreground/Background processes)
 *	Implement shifting processes between levels.
 *	This stage will include testing to make sure signals are
 *	handled correctly, no matter which direction the processes switch
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Sends the inputted job to the foreground
 *
 * @args pid The ID of the process to send to the foreground
 * @return Returns 1 if successful, or 0 if unsuccessful
 */
int toForeground(pid_t pid);

/**
 * Sends the inputted job to background
 *
 * @args pid The ID of the process to send to the background
 * @return Returns 1 if successful, or 0 if unsuccessful
 */
int toBackground(pid_t pid);
