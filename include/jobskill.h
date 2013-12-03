/**
 * File: jobskill.h
 * Author:
 * Contributors: 
 * Description: (change this later)
 *	Implement shifting processes between levels.
 *	This stage will include testing to make sure signals
 *	are handled correctly no matter which direction the 
 *	processes shift.
 */

#ifndef _JOBS_KILL_H_
#define _JOBS_KILL_H_

#include <jobsgroup.h>
#include <stdlib.h>
#include <string.h>

shellcmd xsh_killjob( int nargs, char *args[] );

#endif
