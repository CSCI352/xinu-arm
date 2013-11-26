/**
 * File: xsh_jobsgroup.c
 * Author: Rebecca Vessal
 * Contributors:
 * Description: (change this later)
 *      Linked list for processes and use the parent process as the group ID
 */

#include <jobsgroup.h>
//Get each thread from the thread table and put them into jobs
void generateJob()
{
    while((thrptr = &thrtab[i]) != NULL)
    {
        if (thrptr->state == THRFREE)
        {
            continue;
        }
    }
}