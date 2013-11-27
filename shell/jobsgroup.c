/**
 * File: jobsgroup.c
 * Author: Rebecca Vessal
 * Contributors:
 * Description: (change this later)
 *      Linked list for processes and use the parent process as the group ID
 */

#include <jobsgroup.h>

//Extern keyword makes the property global
//see: http://stackoverflow.com/questions/1433204/how-do-i-share-a-variable-between-source-files-in-c-with-extern-but-how
//Number of jobs in the job list
int numberOfJobs;
//List of jobs
Job **listOfJobs;

//Basic initialization
void init(void)
{
	//Allocate enough space for at least one job
	listOfJobs = (Job**)malloc(sizeof(Job*));
	numberOfJobs = 0;
}

//Get each thread from the thread table and put them into a job
void generateJob(void)
{
	//Temp thread pointer
	struct thrent *threadPointer;
	//Index that will serve as the tid
	uchar i;
	//Flag for indicating the first thread in the job
	bool firstThread = FALSE;
	Job *job = (Job*)malloc(sizeof(Job));
    for(i = 0; i < NTHREAD; i++)
    {
    	threadPointer = &thrtab[i];
        if (threadPointer->state == THRFREE)
        {
            continue;
        }
		Process *process = (Process*)malloc(sizeof(Process));
		//Make the first thread that is not free the parent process
		if(!firstThread)
		{
			process->groupID = i;
			process->isParentProcess = TRUE;
			process->dataThread = threadPointer;
			process->nextProcess = NULL;
			firstThread = TRUE;
			//Place this process into a job
			job->headProcess = process;
			job->tailProcess = process;
		}
		else
		{
			//Grab the headProcess to assign the groupID to this child process
			Process *parentProcess = job->headProcess;
			process->groupID = parentProcess->groupID;
			//Initialize the other properties of the child process
			process->isParentProcess = FALSE;
			process->dataThread = threadPointer;
			process->nextProcess = NULL;
			//Grab the last process in the job and assign it's next thread to the newly created child process
			Process *lastProcessInJob = job->tailProcess;
			lastProcessInJob->nextProcess = process;
			//Make the new process the tail thread
			job->tailProcess = process;
		}
    }
	//Add the job onto the list of jobs
	listOfJobs[numberOfJobs] = job;
	numberOfJobs++;
}

//Print out the jobs
void printJobs(void)
{
	//Taken form xsh_ps.c in Xinu
	/* readable names for PR* status in thread.h */
    char *pstnams[] = { "curr ", "free ", "ready", "recv ",
        "sleep", "susp ", "wait ", "rtim "
    };
	
	//Print out the header info
	//Taken from xsh_ps.c in Xinu
	/* Output thread table header */
/*    printf(
            "TID NAME         STATE PRIO PPID STACK BASE STACK PTR  STACK LEN \n");

    printf(
            "--- ------------ ----- ---- ---- ---------- ---------- ----------\n");
*/
	printf("Jobs:");
    printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
           "TID", "NAME", "STATE", "PRIO", "PPID", "STACK BASE",
           "STACK PTR", "STACK LEN");


    printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
           "---", "----------------", "-----", "----", "----",
           "----------", "----------", " ---------");
    //Temp process variable
    Process *process;
    //Counter to act as tid
    int counter = 0;
    int i = 0;
	while(i < numberOfJobs)
	{
		//Get the job from the list of jobs
		Job *job = listOfJobs[i];
		//Get the head process to start traversing through the list of processes
		process = job->headProcess;
		while(process != NULL)
		{
			//Otherwise go to next process
			process = process->nextProcess;
			struct thrent *threadPointer = process->dataThread;
		
			//Print out the thread info
			//Taken form xsh_ps.c in Xinu
			printf("%3d %-16s %s %4d %4d 0x%08X 0x%08X %10d\n",
               		counter, threadPointer->name,
               		pstnams[(int)threadPointer->state - 1],
               		threadPointer->prio, threadPointer->parent,
               		threadPointer->stkbase, threadPointer->stkptr, threadPointer->stklen);
            counter++;
        }
        //Reset the counter for tid
        counter = 0;
        //Increment the while loop counter
        i++;
	}
}