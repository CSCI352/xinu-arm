#include <stdio.h>
#include <stddef.h>
#include <conf.h>
#include "SEMAPHORE.h"


SEMAPHORE s;

 tid_typ atid, btid;

extern void WAIT(SEMAPHORE* S);
extern void SIGNAL(SEMAPHORE* S);

shellcmd xsh_mutexTesting(int nargs, char* args[])
{
    int prA(), prB();
s.value = 1;
s.queue = queinit();

    resume( btid = create(prB, 200, 20, "proc 1", 0));
    resume( atid = create(prA, 200, 20, "proc 2", 0) );


    sleep(60);
}

prA()
{
   s.pid=atid;
    fprintf(0, "s.value= %d\n", s.value);
  fprintf(0, "Semaphore A acquiring lock\n");
  WAIT(&s);
  sleep(5);
  fprintf(0, "Semaphore A release lock\n");
  SIGNAL(&s);
    fprintf(0, "s.value= %d\n", s.value);
}

prB()
{
    s.pid=btid;
    fprintf(0, "B Value: %d\n", s.value);
    fprintf(0,"Semaphore B waiting for lock\n");
    WAIT(&s);
    fprintf(0, "Semaphore B lock acquired\n");
    SIGNAL(&s);
}
