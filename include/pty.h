/**
 * @file pty.h
 *
 * Provides a pseudo-terminal interface meant mainly for XINU shells.
 * Ideally, this would be a pseudo-device proper.
 * As it stands, it's a series of kernel calls to abstract the multiplexing logic away from the shells.
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#ifndef _PTY_H_
#define _PTY_H_

#include <tty.h>
#include <stdio.h>
 
/* Global variable that stores our active PTY */
extern int activePtyId;

/* Pseudo-TTY functions */
uint ptyRead(int, void *, uint);
void ptyPutc(int, char);
char ptyGetc(int);
void ptyPrintf(int, const char *, ...);
void ptyControl(int, int, long, long);

#endif                          /* _PTY_H_ */
