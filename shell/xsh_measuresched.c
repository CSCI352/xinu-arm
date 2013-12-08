/*
 * @file     xsh_ping.c
 * @provides xsh_ping
 *
 * $Id: xsh_ping.c 2065 2009-09-04 21:44:36Z brylow $
 */

#include <stddef.h>
#include <stdio.h>
#include <thread.h>
#include <clock.h>


static void calc_pi(int iterations, char* name)
{
    ulong clockStart = clkticks;
    int i = 0;
    double pi = 0;

    for (i = 0; i < iterations; i++)
    {
        pi += ((i % 2 == 0) ? 1 : -1) * (4 / ((2 * i) + 1));
    }
    fprintf(out, "Thread %s took %lu ticks\n", name, clkticks - clockStart);
}

shellcmd xsh_measuresched(int nargs, char *args[])
{
    tid_typ atid, btid, ctid, dtid;
    
    ready(atid = create((void *)calc_pi, INITSTK, 31, "CalcPiA", 2, 1000, "CalcPiA"), 0);
    ready(btid = create((void *)calc_pi, INITSTK, 31, "CalcPiB", 1, 1000, "CalcPiB"), 0);
    ready(ctid = create((void *)calc_pi, INITSTK, 31, "CalcPiC", 1, 1000, "CalcPiC"), 0);
    ready(dtid = create((void *)calc_pi, INITSTK, 31, "CalcPiD", 1, 1000, "CalcPiD"), 0);

    yield();
    return SHELL_OK;
}
