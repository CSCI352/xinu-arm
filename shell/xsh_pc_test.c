#include <shell.h>
#include <thread.h>
#include <stdio.h>
#include <os_semaphore.h>
#include <os_mutex.h>

//  Pseudo-code source:  article on wikipedia

int producer();
int consumer();
void cleanup();

mut_id moni;
sem_id fillCount;
sem_id emptyCount;
#define BUFFER_SIZE 25
int buff[BUFFER_SIZE] = {-1};
int* current = buff;

shellcmd xsh_pc_test(int nargs, char* args[])
{
    test4();
    sleep(30000);
    cleanup();
    
    
}
void cleanup()
{
    os_remove_semaphore(fillCount);
    os_remove_semaphore(emptyCount);
    os_remove_mutex(moni);
        
}
void test4()
{


    moni =   os_create_mutex();
    fillCount = os_create_semaphore(0);
    emptyCount = os_create_semaphore(BUFFER_SIZE);
   
   
    tid_typ t1, t2, t3;

    t1 = create(producer, INITSTK, 21, "producer", 0 );
    ready(t1, RESCHED_YES);

    t2 = create(consumer, INITSTK, 21, "consumer1", 0);
    ready(t2, RESCHED_YES);

    t3 = create(consumer, INITSTK, 21, "consumer2", 0);
    ready(t3, RESCHED_YES);
}

int producer()
{
    while(1)
    {
      os_lock_semaphore(emptyCount);
         os_lock_mutex(moni);
            fprintf(0,"previous value: %u\n", *current);
            *current= 1;
            if(current == &buff[BUFFER_SIZE-1])
            {}
            else
                current++;// = buffer + sizeof(int);
         os_unlock_mutex(moni);
      os_unlock_semaphore(fillCount);
    }
   return 0;
}

int consumer()
{
    while(1)
    {
      os_lock_semaphore(fillCount);
         os_lock_mutex(moni);
            fprintf(0, "current consumed: %u\n", *current);
            *current = 0;
            current--;
         os_unlock_mutex(moni);
      os_unlock_semaphore(emptyCount);
    }
   return 0;
}
