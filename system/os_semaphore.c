#include <os_semaphore.h>
#include <thread.h>
#include <interrupt.h>


sem_id os_create_semaphore(resources)
{
    irqmask imask = disable();

    // go to leaf node or create one if empty
    struct os_sem_list* current = sem_list;
    if(current == 0)
    {
        sem_list = malloc(sizeof(struct os_sem_list));
        current = sem_list;
        current->next = 0;
        current->sem = malloc(sizeof(struct os_semaphore));
        current->sem->id = os_sem_next_id++;
        current->sem->value = resources;
        current->sem->threads = queinit();
        restore(imask);
        return current->sem->id;
    }
    while(current->next != 0)
    {
        current = current->next;
    }

    // turn leaf node into semaphore node
    struct os_sem_list* newNode = malloc(sizeof(struct os_sem_list));
    current->next = newNode;
    newNode->next = 0;
    newNode->sem = malloc(sizeof(struct os_semaphore));
    newNode->sem->id = os_sem_next_id++;
    newNode->sem->value = resources;
    newNode->sem->threads = queinit();
    restore(imask);
    return newNode->sem->id;
}

int os_remove_semaphore(sem_id semToDelete)
{
    irqmask imask = disable();

    struct os_sem_list* current = sem_list;

    // if there are no nodes
    if(current == 0)
    {
        restore(imask);
        return 1;
    }
    // if the first node matches, remove and free it
    if(current->sem->id == semToDelete)
    {
        if(current->sem->id == semToDelete)
        {
            sem_list = 0;
            free(current->sem);
            free(current);
            sem_list = current->next;
            restore(imask);
            return 0;
        }
    }

    // go to node before matching node 
    while(current->next->next != 0 && current->next->sem->id != semToDelete)
    {
        current = current->next;
    }

    // remove node
    if(current->next->sem->id == semToDelete)
    {
        struct os_sem_list* nodeToRemove = current->next;
        struct os_sem_list* nextNode = current->next->next;
        current->next = nextNode;

        // free node
        free(nodeToRemove->sem);
        free(nodeToRemove);

        restore(imask);
        return 0;
    }
    restore(imask);
    return 1;
}

int os_lock_semaphore(sem_id id)
{
    irqmask imask = disable();

    // find matching semaphore in list
    struct os_sem_list* current = sem_list;
    while(current != 0 && current->sem->id != id)
    {
        current = current->next;
    }
    if(current == 0)
    {
        restore(imask);
        return 1;
    }
    struct os_semaphore* sem = current->sem;

    // decrement
    sem->value--;

    // wait this process if semaphore is negative
    if(sem->value < 0)
    {
#ifdef DEBUG
        fprintf(0, "Thread %u is waiting for semaphore %u\n", thrcurrent, id);
#endif
        thrtab[thrcurrent].state = THRWAIT;
        enqueue(thrcurrent, sem->threads);
        resched();
#ifdef DEBUG
        fprintf(0, "Thread %u aquired semaphore %u after waiting\n", thrcurrent,
            id);
#endif
    }

    restore(imask);
    return 0;
}

int os_unlock_semaphore(sem_id id)
{
    irqmask imask = disable();

    // find matching semaphore in list
    struct os_sem_list* current = sem_list;
    while(current != 0 && current->sem->id != id)
    {
        current = current->next;
    }
    if(current == 0)
    {
        restore(imask);
        return 1;
    }
    struct os_semaphore* sem = current->sem;

    // increment
    sem->value++;

    // if there are waiting threads, make one ready
    if(sem->value < 0)
    {
        tid_typ otherThread = dequeue(sem->threads);
        ready(otherThread, RESCHED_YES);
    }

    restore(imask);
    return 0;
}

void os_print_all_sem()
{
    printf("Printing all semaphores\n");

    struct os_sem_list* current = sem_list;
    while(current != 0)
    {
        printf("Semaphore %u has value %d\n", current->sem->id,
            current->sem->value);
        current = current->next;
    }

    printf("Done printing semaphores\n");

}

