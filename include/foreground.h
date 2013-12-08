/**
 * File: foreground.h
 * Author: Cody Holley (cmh6807)
 * Contributors: Marit Brocker (mlb8494)
 * Description:
 *	Moves a job from whatever state it may currently be in 
 *	to the foreground.
 */

#ifndef _FOREGROUND_H_
#define _FOREGROUND_H_

#include <stdio.h>
#include <stdlib.h>
#include <thread.h>
#include <kernel.h>
#include <shell.h>

/**
 * Send a job to the foreground. Returns a 0 if the job was successfully
 * sent to the foreground, and a 1 if there was an error
 *
 * @args nargs Number of arguments passed to the function
 * @args args The arguments passed to the function
 */
shellcmd xsh_jobfg( int nargs, char *args[] );

#endif
