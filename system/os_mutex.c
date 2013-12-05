#include <os_mutex.h>
#include <thread.h>
#include <interrupt.h>


mut_id os_create_mutex()
{
    irqmask imask = disable();

    // go to leaf node or create one if empty
    struct os_mut_list* current = mut_list;
    if(current == 0)
    {
        mut_list = malloc(sizeof(struct os_mut_list));
        current = mut_list;
        current->next = 0;
        current->mut = malloc(sizeof(struct os_mutex));
        current->mut->id = os_mut_next_id++;
        current->mut->available = 1;
        current->mut->threads = queinit();
        restore(imask);
        return current->mut->id;
    }
    while(current->next != 0)
    {
        current = current->next;
    }

    // turn leaf node into mutex node
    struct os_mut_list* newNode = malloc(sizeof(struct os_mut_list));
    current->next = newNode;
    newNode->next = 0;
    newNode->mut = malloc(sizeof(struct os_mutex));
    newNode->mut->id = os_mut_next_id++;
    newNode->mut->available = 1;
    newNode->mut->threads = queinit();
    restore(imask);
    return newNode->mut->id;
}

int os_remove_mutex(mut_id mutToDelete)
{
    irqmask imask = disable();

    struct os_mut_list* current = mut_list;

    // if there are no nodes
    if(current == 0)
    {
        restore(imask);
        return 1;
    }
    // if the first node matches, remove and free it
    if(current->mut->id == mutToDelete)
    {
        if(current->mut->id == mutToDelete)
        {
            mut_list = 0;
            free(current->mut);
            free(current);
            mut_list = current->next;
            restore(imask);
            return 0;
        }
    }

    // go to node before matching node 
    while(current->next->next != 0 && current->next->mut->id != mutToDelete)
    {
        current = current->next;
    }

    // remove node
    if(current->next->mut->id == mutToDelete)
    {
        struct os_mut_list* nodeToRemove = current->next;
        struct os_mut_list* nextNode = current->next->next;
        current->next = nextNode;

        // free node
        free(nodeToRemove->mut);
        free(nodeToRemove);

        restore(imask);
        return 0;
    }
    restore(imask);
    return 1;
}

int os_lock_mutex(mut_id id)
{
    irqmask imask = disable();

    // find matching mutex in list
    struct os_mut_list* current = mut_list;
    while(current != 0 && current->mut->id != id)
    {
        current = current->next;
    }
    if(current == 0)
    {
        restore(imask);
        return 1;
    }
    struct os_mutex* mut = current->mut;

    // wait this process if mutex is not available
    if(!(mut->available))
    {
#ifdef DEBUG
        fprintf(0, "Thread %u is waiting for mutex %u\n", thrcurrent, id);
#endif
        thrtab[thrcurrent].state = THRWAIT;
        enqueue(thrcurrent, mut->threads);
        resched();
#ifdef DEBUG
        fprintf(0, "Thread %u aquired mutex %u after waiting\n", thrcurrent,
            id);
#endif
    }
    mut->available = 0;

    restore(imask);
    return 0;
}

int os_unlock_mutex(mut_id id)
{
    irqmask imask = disable();

    // find matching mutex in list
    struct os_mut_list* current = mut_list;
    while(current != 0 && current->mut->id != id)
    {
        current = current->next;
    }
    if(current == 0)
    {
        restore(imask);
        return 1;
    }
    struct os_mutex* mut = current->mut;

    // increment
    mut->available = 1;

    // if there are waiting threads, make one ready
    //if(mut->available < 0)
    if(nonempty(mut->threads))
    {
        tid_typ otherThread = dequeue(mut->threads);
        ready(otherThread, RESCHED_YES);
    }

    restore(imask);
    return 0;
}

void os_print_all_mut()
{
    printf("Printing all mutexs\n");

    struct os_mut_list* current = mut_list;
    while(current != 0)
    {
        printf("Semaphore %u has value %d\n", current->mut->id,
            current->mut->available);
        current = current->next;
    }

    printf("Done printing mutexs\n");

}

