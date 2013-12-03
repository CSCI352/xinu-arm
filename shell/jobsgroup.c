/**
 * File: jobsgroup.c
 * Author: Rebecca Vessal
 * Contributors:
 * Description: (change this later)
 *      Linked list for processes and use the parent process as the group ID
 */

#include <jobsgroup.h>

//Must define the extern variables like so, otherwise you will get an undefined reference error
//see: http://www.dreamincode.net/forums/topic/220054-undefined-reference-to-an-external-global-variable/
//Define the extern variables
//Number of jobs in the job list
int numberOfJobs;
//List of jobs
Job** listOfJobs;

//Basic initialization
void init(void)
{
	//Allocate enough space for at least one job
	listOfJobs = (Job**)malloc(sizeof(Job*));
	numberOfJobs = 0;
}

//Check to see if the thread is in a job already
bool isThreadInJobAlready(struct thrent *passedInThreadPointer)
{
	bool threadInJobAlready = FALSE;
	//Temp process variable
    Process* process;
    //Counter to act as tid
    int counter = 0;
    int i = 0;
	while(i < numberOfJobs)
	{
		//Get the job from the list of jobs
		Job* job = listOfJobs[i];
		//Get the head process to start traversing through the list of processes
		process = job->headProcess;
		while(process != NULL)
		{
			//Get the data thread to compare with the thread pointer passed in
			struct thrent* threadPointer = process->dataThread;
			if(passedInThreadPointer == threadPointer)
			{
				threadInJobAlready = TRUE;
				break;
			}
            counter++;
            //Otherwise go to next process
			process = process->nextProcess;
        }
        //Break out of the outer while loop if thread is already in a job
        if(threadInJobAlready)
        {
        	break;
        }
        //Reset the counter for tid
        counter = 0;
        //Increment the while loop counter
        i++;
	}
}

//Get each thread from the thread table and put them into a job
void generateJob(void)
{
	//Temp thread pointer
	struct thrent* threadPointer;
	//Flag for indicating the first thread in the job
	bool firstThread = FALSE;
	Job* job = (Job*)malloc(sizeof(Job));
	//Temp iterative variable
	int i;
    for(i = 1; i < NTHREAD; i++)
    {
    	threadPointer = &thrtab[i];
        if (threadPointer->state == THRFREE)
        {
            continue;
        }
        
        //Check to see if the thread is in a job already
        if(!isThreadInJobAlready(threadPointer))
        {
			//Make the first thread that is not free the parent process
			if(!firstThread)
			{
				Process* process = (Process*)malloc(sizeof(Process));
				process->groupID = i;
				process->dataThreadID = i;
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
				//Check to see if the last process data thread's id is 
				//the same as the thread pointer's parent id.
				//If it is, then add it to the job.
				if(job->tailProcess->dataThreadID == threadPointer->parent)
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
}

//Print out the jobs
void printJobs(void)
{
	//Taken form xsh_ps.c in Xinu
	/* readable names for PR* status in thread.h */
    char* pstnams[] = { "curr ", "free ", "ready", "recv ",
        "sleep", "susp ", "wait ", "rtim "
    };
	
	//Print out the header info
	//Taken from xsh_ps.c in Xinu
	/* Output thread table header */
/*    printf(
            "JOB ID JOB STATUS ID NAME         STATE PRIO PPID STACK BASE STACK PTR  STACK LEN \n");

    printf(
            "------ ---------- --- ------------ ----- ---- ---- ---------- ---------- ----------\n");
*/
	printf("Jobs:\n");
    printf("%6s %10s %3s %-16s %5s %4s %4s %10s %-10s\n",
           "JOB ID", "JOB STATUS", "TID", "NAME", "STATE", "PRIO", "PPID", "STACK BASE",
           "STACK PTR");


    printf("%6s %10s %3s %-16s %5s %4s %4s %10s %-10s\n",
           "------", "----------", "---", "----------------", "-----", "----", "----", "----------", "----------");
    //Temp process variable
    Process* process;
   	//Temp iterative variable
    int i;
	for(i =0; i < numberOfJobs; i++)
	{
		//Get the job from the list of jobs
		Job* job = listOfJobs[i];
		//Get the head process to start traversing through the list of processes
		process = job->headProcess;
		while(process != NULL)
		{
			//Get the data thread to print out its info
			struct thrent* threadPointer = process->dataThread;
			//Print out the thread info
			//Taken form xsh_ps.c in Xinu
			printf("%6d %10s %3d %-16s %s %4d %4d 0x%08X 0x%08X\n",
               		process->groupID,
					job->status, 
               		process->dataThreadID, 
               		threadPointer->name,
               		pstnams[(int)threadPointer->state - 1],
               		threadPointer->prio, 
               		threadPointer->parent,
               		threadPointer->stkbase, 
               		threadPointer->stkptr);
            //Otherwise go to next process
			process = process->nextProcess;
        }
	}
}