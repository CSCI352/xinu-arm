#include <interrupt.h>
#include "SEMAPHORE.h"


void WAIT(SEMAPHORE* S)
{
    irqmask im;

    im = disable();
    while(S->value <= 0)
    {
        enqueue(S->pid, S->queue);        
        //put pid thred to sleep....?
        sleep(1000);
    }
    //criticl operation.. disable interrupts for decrement

    S->value--;
    restore(im);
}

void SIGNAL(SEMAPHORE* S)
{
    //critical operation. disable interrupts for increment
    irqmask im;
    im = disable();

    tid_typ cthread = dequeue(S->queue);
    unsleep(cthread);
    S->value++;
    restore(im);
}


