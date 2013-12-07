#include <stddef.h>
#include <stdio.h>
#include <shell.h>
#include <thread.h>
#include <os_mutex.h>

void muttest_justPrint();
void muttest_lockAndUnlock();
void muttest_lockSleepAndUnlock();
void muttest_lock();

mut_id muttest_s;

/**
 * Shell command for testing mutexs
 */
shellcmd xsh_os_mutex(int nargs, char *args[])
{
    muttest_test1();
}

void muttest_test1()
{
    muttest_s = os_create_mutex();

    //tid_typ t1 = create(muttest_lockSleepAndUnlock, INITSTK, 21, "t1", 0);
    //tid_typ t1 = create(muttest_lockSleepAndUnlock, INITSTK, 21, "t1", 0);
    tid_typ t1 = create(muttest_lock, INITSTK, 21, "t1", 0);
    ready(t1, RESCHED_YES);

    sleep(1000);

    tid_typ t2 = create(muttest_lockAndUnlock, INITSTK, 21, "t2", 0);
    ready(t2, RESCHED_YES);
    fprintf(0, "Test 1 finished\n");
}

// This does not unlock after
void muttest_lock()
{
    fprintf(0, "Thread %u running lock()\n", thrcurrent);
    os_lock_mutex(muttest_s);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}

void muttest_lockSleepAndUnlock()
{
    fprintf(0, "Thread %u running lockSleepAndUnlock()\n", thrcurrent);
    os_lock_mutex(muttest_s);
    fprintf(0, "Thread %u locked mutex %u\n", thrcurrent, muttest_s);
    fprintf(0, "Thread %u sleep\n", thrcurrent);
    sleep(3000);
    os_unlock_mutex(muttest_s);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}

void muttest_lockAndUnlock()
{
    fprintf(0, "Thread %u running lockAndUnlock()\n", thrcurrent);
    printf("%d", os_lock_mutex(muttest_s));
    printf(0, "Thread %u locked mutex %u\n", thrcurrent, muttest_s);
    os_unlock_mutex(muttest_s);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}

void muttest_justPrint()
{
    fprintf(0, "Thread %u running justPrint\n", thrcurrent);
    fprintf(0, "Thread %u ending\n", thrcurrent);
}
