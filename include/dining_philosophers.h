#ifndef DINING_PHILOSOPHERS_H_
#define DINING_PHILOSOPHERS_H_

#include <os_semaphore.h>


typedef int philosopher;

#define THINKING 0
#define HUNGRY 1
#define EATING 2

#define AVAILABLE 0
#define TAKEN 1

struct dining_table
{
    /**
     * The number of forks/philosophers
     */
    int size;

    /**
     * Whether each for is available or being used
     */
    bool* forks;

    /**
     * States of the philosophers
     */
    philosopher* people;

    /**
     * The waiter(semaphore) that grants permission to use forks
     */
    sem_id waiter;
};

struct dining_table dining_table_init(int size);

void free_dining_table(struct dining_table* t);

void eat(struct dining_table* t, int index);

void think(struct dining_table* t, int index);

#endif // DINING_PHILOSOPHERS_H_
