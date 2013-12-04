#include <stddef.h>
#include <stdio.h>
#include <shell.h>
#include <thread.h>
#include <os_semaphore.h>

void justPrint();
void lockAndUnlock();
void lockSleepAndUnlock();
void lock();

sem_id s;

/**
 * Shell command for testing semaphores
 */
shellcmd xsh_os_semaphore(int nargs, char *args[])
{
    test1();
    //printf("%d\n", thrtab[thrcurrent].prio);
}

void test1()
{
    s = os_create_semaphore(1);

    //tid_typ t1 = create(lockSleepAndUnlock, INITSTK, 21, "t1", 0);
    tid_typ t1 = create(lockSleepAndUnlock, INITSTK, 21, "t1", 0);
    ready(t1, RESCHED_YES);

    sleep(1000);

    tid_typ t2 = create(lockAndUnlock, INITSTK, 21, "t2", 0);
    ready(t2, RESCHED_YES);
    fprintf(0, "Test 1 finished\n");
}

// This does not unlock after
void lock()
{
    fprintf(0, "Thread %u running lock()\n", thrcurrent);
    os_lock_semaphore(s);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}

void lockSleepAndUnlock()
{
    fprintf(0, "Thread %u running lockSleepAndUnlock()\n", thrcurrent);
    os_lock_semaphore(s);
    fprintf(0, "Thread %u locked semaphore %u\n", thrcurrent, s);
    fprintf(0, "Thread %u sleep\n", thrcurrent);
    sleep(3000);
    os_unlock_semaphore(s);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}

void lockAndUnlock()
{
    fprintf(0, "Thread %u running lockAndUnlock()\n", thrcurrent);
    os_lock_semaphore(s);
    printf(0, "Thread %u locked semaphore %u\n", thrcurrent, s);
    os_unlock_semaphore(s);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}

void justPrint()
{
    fprintf(0, "Thread %u running justPrint\n", thrcurrent);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}
