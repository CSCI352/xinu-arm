/**
 * File: foreground.h
 * Author: Cody Holley (cmh6807)
 * Contributors: Marit Brocker (mlb8494)
 * Description: (change this later)
 *	(Foreground/Background processes)
 *	Implement shifting processes between levels.
 *	This stage will include testing to make sure signals are
 *	handled correctly, no matter which direction the processes switch
 */

#ifndef _FOREGROUND_H_
#define _FOREGROUND_H_

#include <stdio.h>
#include <stdlib.h>
#include <thread.h>

shellcmd xsh_fg( int nargs, char *args[] );

#endif
