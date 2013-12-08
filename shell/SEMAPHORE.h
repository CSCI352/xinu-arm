#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <queue.h>
#include <thread.h>
typedef struct
{
    int value;
    tid_typ pid;
    qid_typ queue;

} SEMAPHORE;
#endif


void SIGNAL(SEMAPHORE* S);
void WAIT(SEMAPHORE* S);
