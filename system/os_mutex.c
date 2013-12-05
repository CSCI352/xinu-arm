#include <os_mutex.h>
#include <os_semaphore.h>
#include <thread.h>
#include <interrupt.h>


mut_id os_create_mutex()
{
    return os_create_semaphore(1);
}

int os_remove_mutex(mut_id mutToDelete)
{
    return os_remove_semaphore(mutToDelete);
}

int os_lock_mutex(mut_id id)
{
    return os_lock_semaphore(id);
}

int os_unlock_mutex(mut_id id)
{
    return os_unlock_semaphore(id);
}

void os_print_all_mut()
{
    return os_print_all_mut();
}

