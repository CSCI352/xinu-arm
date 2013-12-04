#ifndef OS_MUTEX_H_
#define OS_MUTEX_H_

#include <queue.h>

typedef unsigned int mut_id;

struct os_mutex
{
    /**
     * Unique id for this mutex
     */
    mut_id id;

    /**
     * Available resources left
     */
    int value;

    /**
     * Available resources left
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

mut_id os_create_mutex();

int os_remove_mutex(mut_id mut_to_remove);

int os_lock_mutex(mut_id mut_to_lock);

int os_unlock_mutex(mut_id mut_to_lock);

void os_print_all_mut();

#endif // OS_MUTEX_H_
