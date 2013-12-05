#include <stddef.h>
#include <stdio.h>
#include <shell.h>
#include <thread.h>
#include <os_semaphore.h>

void semtest_justPrint();
void semtest_lockAndUnlock();
void semtest_lockSleepAndUnlock();
void semtest_lock();

sem_id semtest_s;

/**
 * Shell command for testing semaphores
 */
shellcmd xsh_os_semaphore(int nargs, char *args[])
{
    test1();
}

void test1()
{
    semtest_s = os_create_semaphore(1);

    //tid_typ t1 = create(lockSleepAndUnlock, INITSTK, 21, "t1", 0);
    tid_typ t1 = create(semtest_lockSleepAndUnlock, INITSTK, 21, "t1", 0);
    ready(t1, RESCHED_YES);

    sleep(1000);

    tid_typ t2 = create(semtest_lockAndUnlock, INITSTK, 21, "t2", 0);
    ready(t2, RESCHED_YES);
    fprintf(0, "Test 1 finished\n");
}

// This does not unlock after
void semtest_lock()
{
    fprintf(0, "Thread %u running lock()\n", thrcurrent);
    os_lock_semaphore(semtest_s);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}

void semtest_lockSleepAndUnlock()
{
    fprintf(0, "Thread %u running lockSleepAndUnlock()\n", thrcurrent);
    os_lock_semaphore(semtest_s);
    fprintf(0, "Thread %u locked semaphore %u\n", thrcurrent, semtest_s);
    fprintf(0, "Thread %u sleep\n", thrcurrent);
    sleep(3000);
    os_unlock_semaphore(semtest_s);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}

void semtest_lockAndUnlock()
{
    fprintf(0, "Thread %u running lockAndUnlock()\n", thrcurrent);
    os_lock_semaphore(semtest_s);
    printf(0, "Thread %u locked semaphore %u\n", thrcurrent, semtest_s);
    os_unlock_semaphore(semtest_s);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}

void semtest_justPrint()
{
    fprintf(0, "Thread %u running justPrint\n", thrcurrent);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}
