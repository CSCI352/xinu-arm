/**
 * File: background.h
 * Author: Cody Holley (cmh6807)
 * Contributors: Marit Brocker (mlb8494)
 * Description: (change this later)
 *	(Foreground/Background processes)
 *	Implement shifting processes between levels.
 *	This stage will include testing to make sure signals are
 *	handled correctly, no matter which direction the processes switch
 */

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <stdio.h>
#include <stdlib.h>
#include <thread.h>
#include <kernel.h>
#include <shell.h>

/**
 * Send a job to the background. Returns a 1 if the job was successfully
 * sent to the background, and a -1 if there was an error
 *
 * @args nargs Number of arguments passed to the function
 * @args args The arguments passed to the function
 */
shellcmd xsh_bg( int nargs, char *args[] );

#endif
