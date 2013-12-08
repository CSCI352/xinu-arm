#ifndef OS_MUTEX_H_
#define OS_MUTEX_H_

#include <queue.h>

/**
 * Value used to identify a mutex
 */
typedef unsigned int mut_id;

struct os_mutex
{
    /**
     * Unique id for this mutex
     */
    mut_id id;

    /**
     * Whether this the resource is available
     */
    bool available;

    /**
     * This holds all threads that are waiting on this mutex to be free
     */
    qid_typ threads;
};

struct os_mut_list
{
    struct os_mutex* mut;
    struct os_mut_list* next;
};

extern struct os_mut_list* mut_list;
extern mut_id os_mut_next_id;

/**
 * Create a mutex and return its id
 * @return mutex id
 */
mut_id os_create_mutex();

/**
 * Delete a mutex
 * @param mut_to_delete ID of mutex
 * @return 0 if success. Otherwise, 1.
 */
int os_remove_mutex(mut_id mut_to_remove);

/**
 * Gives current thread access to mutex
 * @param mut ID of mutex
 * @return 0 if success. Otherwise, 1.
 */
int os_lock_mutex(mut_id mut_to_lock);

/**
 * Releases current thread from mutex
 * @return 0 if success. Otherwise, 1.
 */
int os_unlock_mutex(mut_id mut_to_lock);

/**
 * Print all mutex and their values. For debugging.
 */
void os_print_all_mut();

#endif // OS_MUTEX_H_
