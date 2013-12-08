#ifndef OS_SEMAPHORE_
#define OS_SEMAPHORE_

#include <queue.h>

/**
 * Value used to identify a semaphore
 */
typedef unsigned int sem_id;

struct os_semaphore
{
    /**
     * Unique id for this semaphore
     */
    sem_id id;

    /**
     * Available resources left
     */
    int value;

    /**
     * This holds all threads that are waiting on this semaphore to be free
     */
    qid_typ threads;
};

struct os_sem_list
{
    struct os_semaphore* sem;
    struct os_sem_list* next;
};

extern struct os_sem_list* sem_list;
extern sem_id os_sem_next_id;

/**
 * Create a semaphore and return its id
 * @param resources Number of resources available
 * @return semaphore id
 */
sem_id os_create_semaphore(resources);

/**
 * Delete a semaphore
 * @param sem_to_delete ID of semaphore
 * @return 0 if success. Otherwise, 1.
 */
int os_remove_semaphore(sem_id sem_to_delete);

/**
 * Gives current thread access to semaphore
 * @param sem ID of semaphore
 * @return 0 if success. Otherwise, 1.
 */
int os_lock_semaphore(sem_id sem);

/**
 * Releases current thread from semaphore
 * @return 0 if success. Otherwise, 1.
 */
int os_unlock_semaphore();

/**
 * Print all semaphores and their values. For debugging.
 */
void os_print_all_sem();


#endif // OS_SEMAPHORE_
