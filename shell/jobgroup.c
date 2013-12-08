/**
 * File: jobsgroup.c
 * Author: Rebecca Vessal
 * Contributors: Melinda Rabenstein
 * Description:  
 * 1. Creates a linked list of processes that act as wrappers to the threads
 * to provide the threads additional information such as threadID and groupID.  The parent
 * process along with its children processes are put into a job when those threads become backgrounded
 * by typing in a & at the end of a command.  
 * 2. It checks to see if the job with the given jobID exists
 * in the job list for job control shell functionality such as kill, suspending, foregrounding, and backgrounding
 * and returns the index of that job in the list.
 * 3. It also prints out the list of jobs and the processes in those jobs.
 * 4. For debugging purposes, you can print out the threads in the thread table.
 */

#include <jobgroup.h>

//Number of jobs in the job list
int numberOfJobs;
Job** listOfJobs;


/*
 * Initializes the attributes needed for a job control shell
 * 
 * Params:
 *    None
 *
 * Returns: 
 *    None
 *
 * Created by: Rebecca Vessal
 */
void init(void)
{
	//Allocate enough space for at least one job
	listOfJobs = (Job**)malloc(sizeof(Job*));
	numberOfJobs = 0;
}

/*
 * Checks if the job with the given jobID exists
 * 
 * Params:
 *    jobID - the job id
 *
 * Returns: 
 *    The index of the job in listOfJobs, or -1 if the job was not found.
 *
 *	Created by: Melinda Rabenstein
 */
int doesJobExist( tid_typ jobID ) 
{
	int i = 0;
	for( ; i < numberOfJobs; i++ ) 
	{
		Job* job = listOfJobs[i];
		if( job->ID == jobID ) { return i; }
	}

	return -1;
}

/*
 * Check to see if the thread is in a job already
 * 
 * Params:
 *    passedInThreadPointer - The thread to check
 *
 * Returns: 
 *    True if the thread is in a job, else false.
 */
bool isThreadInJobAlready(struct thrent *passedInThreadPointer)
{
    //Counter to act as tid
    int tid_counter = 0;
    int i = 0;
	for(; i < numberOfJobs; i++)
	{
		//Get the job from the list of jobs
		Job* job = listOfJobs[i];
		//Get the head process to start traversing through the list of processes
		Process* process = job->headProcess;
		while(process != NULL)
		{
			//Get the data thread to compare with the thread pointer passed in
			struct thrent* threadPointer = process->dataThread;
			//Stack pointers are unique to each thread, so use theses as comparison
			if(passedInThreadPointer->stkptr == threadPointer->stkptr)
			{
				return TRUE;
			} 
			else 
			{
				tid_counter++;
	            process = process->nextProcess;
			}
        }
        //Reset the counter for tid
        tid_counter = 0;
	}
	return FALSE;
}

/*
 * Get each thread from the thread table and put them into a job
 * 
 * Params: None
 *     
 * Returns: None
 * 
 * Created by: Rebecca Vessal
 */
int generateJob(void)
{
	//For debugging purposes:
	//printThreads();

	bool addSpaceForNewJob = TRUE;
	//Temp thread pointer
	struct thrent* threadPointer;
	//Flag for indicating the first thread in the job
	bool firstThread = TRUE;
	//Create a job
	Job* job = (Job*)malloc(sizeof(Job));

	int i;
    for(i = 3; i < NTHREAD; i++)
    {
    	threadPointer = &thrtab[i];
        if (threadPointer->state == THRFREE)
        {
            continue;
        }
        if(!isThreadInJobAlready(threadPointer))
        {
			//Reallocate memory for adding another job
			if(numberOfJobs > 0 && addSpaceForNewJob)
			{
				//We can't use realloc, since Xinu doesn't support it.
				//So we need to use memcpy as a replacement for realloc
				//Suggestion by Professor Brown
				Job** newListOfJobs = (Job**)malloc(sizeof(Job*) * (numberOfJobs + 1));
				memcpy(newListOfJobs, listOfJobs, sizeof(Job*) * numberOfJobs);
				free(listOfJobs);
				listOfJobs = newListOfJobs;
				addSpaceForNewJob = FALSE;
			}
			//Make the first thread that is not free the parent process
			if(firstThread)
			{
				Process* process = (Process*)malloc(sizeof(Process));
				process->groupID = i;
				process->dataThreadID = i;
				process->isParentProcess = TRUE;
				process->dataThread = threadPointer;
				process->nextProcess = NULL;
				firstThread = FALSE;
				//Place this process into a job
				job->headProcess = process;
				job->tailProcess = process;
				job->ID = i;
			}
			else
			{
				//Check to see if the last process data thread's id is 
				//the same as the thread pointer's parent id or the thread pointer's parent id
				//matches the job's head process id
				//If it is, then add it to the job.
				if(job->tailProcess->dataThreadID == threadPointer->parent 
				|| job->headProcess->dataThreadID == threadPointer->parent)
				{
					//Grab the headProcess to assign the groupID to this child process
					Process* parentProcess = job->headProcess;
					Process* process = (Process*)malloc(sizeof(Process));
					process->groupID = parentProcess->groupID;
					//Initialize the other properties of the child process
					process->dataThreadID = i;
					process->isParentProcess = FALSE;
					process->dataThread = threadPointer;
					process->nextProcess = NULL;
					//Grab the last process in the job and assign it's next thread to the newly created child process
					Process* lastProcessInJob = job->tailProcess;
					lastProcessInJob->nextProcess = process;
					//Make the new process the tail thread
					job->tailProcess = process;
				}
			}
		}
    }
    
	
	//Init the status of the job to background
	job->status = "background";
	//Add the job onto the list of jobs
	listOfJobs[numberOfJobs] = job;
	numberOfJobs++;
	return job->ID;
}

/*
 * Prints out the list of jobs
 * 
 * Params: None
 *    
 * Returns: None
 *    
 * Created by: Rebecca Vessal
 */
void printJobs(void)
{
	//Taken from xsh_ps.c in Xinu
	/* readable names for PR* status in thread.h */
    char* pstnams[] = 
    { 
		"curr ", 
		"free ", 
		"ready", 
		"recv ",
		"sleep", 
		"susp ", 
		"wait ", 
		"rtim "
    };
	
	//Taken from xsh_ps.c in Xinu
	printf("\nNUMBER OF JOBS: %d\n\n", numberOfJobs);
    printf("%6s %10s %3s %-16s %5s %4s %4s %10s %-10s\n",
           "JOB ID", "JOB STATUS", "TID", "NAME", "STATE", "PRIO", "PPID",
           "STACK BASE", "STACK PTR");
    printf("%6s %10s %3s %-16s %5s %4s %4s %10s %-10s\n",
           "------", "----------", "---", "----------------", "-----", "----", "----", "----------", "----------");

    int i = 0;
	for(; i < numberOfJobs; i++)
	{
		Job* job = listOfJobs[i];
		//Get the head process to start traversing through the list of processes
		Process* process = job->headProcess;
		while(process != NULL)
		{
			//Get the data thread to print out its info
			struct thrent* threadPointer = process->dataThread;
			//Print out the thread info
			//Taken from xsh_ps.c in Xinu
			printf("%6d %10s %3d %-16s %s %4d %4d 0x%08X 0x%08X\n",
               		job->ID,
					job->status, 
               		process->dataThreadID, 
               		threadPointer->name,
               		pstnams[(int)threadPointer->state - 1],
               		threadPointer->prio, 
               		threadPointer->parent,
               		threadPointer->stkbase, 
               		threadPointer->stkptr);

			process = process->nextProcess;
        }
	}
	printf("\n");
}

/*
 * Prints out the list of threads (for debugging purposes)
 * 
 * Params: None
 *    
 * Returns: None
 *
 * Created by: Rebecca Vessal
 */
void printThreads(void) 
{
	//For printing out the entire list of threads in the thread table
	//Taken from xsh_ps.c in Xinu
	/* readable names for PR* status in thread.h */
    char* pstnams[] = 
    { 
		"curr ", 
		"free ", 
		"ready", 
		"recv ",
		"sleep", 
		"susp ", 
		"wait ", 
		"rtim "
    };

	printf("Threads:\n");
	printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
           "TID", "NAME", "STATE", "PRIO", "PPID", "STACK BASE",
           "STACK PTR", "STACK LEN");


    printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
           "---", "----------------", "-----", "----", "----",
           "----------", "----------", " ---------");

	int i;
	for(i = 1; i < NTHREAD; i++)
	{
		struct thrent* thrptr = &thrtab[i];
		printf("%3d %-16s %s %4d %4d 0x%08X 0x%08X %10d\n",
               i, thrptr->name,
               pstnams[(int)thrptr->state - 1],
               thrptr->prio, thrptr->parent,
               thrptr->stkbase, thrptr->stkptr, thrptr->stklen);
	}
}
