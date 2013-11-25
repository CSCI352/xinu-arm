/**
 * File: jobsgroup.h
 * Author: Rebecca Vessal
 * Contributors: 
 * Description: (change this later)
 *	Linked list for processes and use the parent process as the group ID
 */
 
 class GroupThreads
 {
public:
	//Struct for job that is implemented like a linked list
	typedef struct{
		struct thrent *headThread;//Pointer to thread that is first thread to be added to the job
		struct thrent *tailThread;//Pointer to the thread that is last thread to be added to the job
	}Job
	//Struct for allowing a thread to have groupID and a parentThread 
	//as it is being pulled out of the threadTable
	typedef struct{
		tid_typ groupID;			//This groupID corresponds to the parent process ID.
									//thrent struct uses tid_type as its PPID AKA Parent process ID.  
									//See:thrent in Xinu shell.
		struct thrent *parentThread;//Pointer to thread that is parent to the current one
		struct thrent *childThread;//Pointer to a child thread if this thread has a child thread
	}Process
	//List of jobs
	struct Job *listOfJobs;
	//Get each thread from the thread table and put them into jobs
	void generateJob();
 }
