/**
 * @file pty.c
 *
 * Implements the pseudo-tty functions described in pty.h
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <pty.h>
 
int activePtyId = 1;
int ptyMax = 10;

uint ptyRead(int ptyId, void *buf, uint buflen) {
	/* Wait for the pty to become active */
	while(ptyId != activePtyId);
	
	/* Read from stdin into the buffer */
	return (uint)read(stdin, buf, buflen);
}

void ptyPutc(int ptyId, char ch) {
	/* Wait for the pty to become active */
	while(ptyId != activePtyId);
	
	/* Put a character */
	putc(stdout, ch);
}

char ptyGetc(int ptyId) {
	/* Wait for the pty to become active */
	while(ptyId != activePtyId);
	
	return getc(stdin);
}

void ptyPrintf(int ptyId, const char *fmt, ...) {
	/* Wait for the pty to become active */
	while(ptyId != activePtyId);
	
	va_list ap;
    
    va_start(ap, fmt);
    _doprnt((char *)fmt, ap, putc, stdout);
    va_end(ap);
}

void ptyControl(int ptyId, int func, long arg1, long arg2) {
	/* Wait for the pty to become active */
	while(ptyId != activePtyId);
	
	control(stdin, func, arg1, arg2);
}
