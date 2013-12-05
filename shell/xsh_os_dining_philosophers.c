#include <dining_philosophers.h>
#include <shell.h>
#include <thread.h>

struct dining_table* d;

void dining_test1();
void dining_test2();
void eatWaitAndFinish(int index);

shellcmd xsh_os_dining_philosophers(int argc, char** argv)
{
    printf("Din Phil Test\n");
    dining_test1();
    //dining_test2();
}

void dining_test1()
{
    printf("Test1 Beginning\n");
    *d = dining_table_init(10);

    int i;
    for(i = 0; i < d->size; i++)
    {
        // cant figure out how to pass args to thread
        tid_typ t1 = create(eatWaitAndFinish, INITSTK, 21, "", 1);
        ready(t1, RESCHED_YES);

    }
    printf("Test1 Finished\n");
}

// this will not finish
void dining_test2()
{
    printf("Test2 Beginning\n");
    struct dining_table d = dining_table_init(10);
    int i;
    for(i = 0; i < d.size; i++)
    {
        eat(&d, i);
    }
    printf("Test1: Everyone is eating. This should not happen.\n");
    for(i = 0; i < d.size; i++)
    {
        think(&d, i);
    }
    printf("Test2 Finished\n");
}

void eatWaitAndFinish(int index)
{
    printf("Philosopher %d is hungry.\n", index);
    eat(d->waiter, index);
    printf("Philosopher %d is eating.\n", index);
    sleep(5000);
    think(d->waiter, index);
    printf("Philosopher %d is thinking.\n", index);
}
