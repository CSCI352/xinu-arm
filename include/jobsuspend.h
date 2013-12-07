/**
 * File: jobssuspend.h
 * Author:
 * Contributors: 
 * Description: (change this later)
 *	This should be linked into signal handling. There are
 *	a couple of different functionalities that need to be implemented,
 *	especially if we support being able to suspend things with signals
 */

#ifndef _JOB_SUSPEND_H_
#define _JOB_SUSPEND_H_

//include necessary files
#include <thread.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <jobgroup.h>

//Define suspend command
command xsh_suspend( int nargs, char *args[] );

#endif
