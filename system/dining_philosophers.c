#include <dining_philosophers.h>
#include <os_semaphore.h>


struct dining_table dining_table_init(int size)
{
    struct dining_table t;
    t.size = size;
    t.forks = malloc(size * sizeof(bool));
    t.people = malloc(size * sizeof(philosopher));
    t.waiter = os_create_semaphore(size-1);

    int i;
    for(i = 0; i < size; i++)
    {
        t.forks[i] = AVAILABLE;
        t.people[i] = THINKING;
    }

    return t;
}

void eat(struct dining_table* t, int index)
{
    if(t->people[index] == EATING)
    {
        return;
    }

    t->people[index] = HUNGRY;

    // take forks
    os_lock_semaphore(t->waiter);
    while(t->forks[index] == TAKEN)
    {
    }
    t->forks[index] = TAKEN;

    os_lock_semaphore(t->waiter);
    while(t->forks[(index+1)%t->size] == TAKEN)
    {
    }
    t->forks[(index+1)%t->size] = TAKEN;

    t->people[index] = EATING;
}

void think(struct dining_table* t, int index)
{
    if(t->people[index] == THINKING)
    {
        return;
    }

    t->people[index] = THINKING;

    // return forks to table
    t->forks[index] = AVAILABLE;
    t->forks[(index+1)%t->size] = AVAILABLE;
}
