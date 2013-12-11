/**
 * File: jobsgroup.c
 * Author: Rebecca Vessal
 * Contributors: Melinda Rabenstein, Andrew Hollenbach
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
 
#ifndef _JOBS_GROUP_H_
#define _JOBS_GROUP_H_
 
#include <stddef.h>
#include <thread.h>//For the threads that make up Xinu
#include <stdio.h>
#include <string.h>
#include <stdlib.h>//For memory management functions such as malloc and realloc
 
//True and false are not keywords in C and must be defined
//see: http://cboard.cprogramming.com/c-programming/146209-false-true-undeclared.html
#define TRUE 1
#define FALSE 0
 
//Struct for allowing a thread to have groupID and a parentThread 
//as it is being pulled out of the threadTable
typedef struct Process{
	tid_typ groupID;			//This groupID corresponds to the parent process ID.
								//thrent struct uses tid_type as its PPID AKA Parent process ID.  
								//See:thrent in thread.h in Xinu shell.
	tid_typ dataThreadID;		//Id for data thread
	bool isParentProcess;
	struct thrent* dataThread; //Pointer to thread that is being represented as a process
	struct thrent* nextProcess;//Pointer to next process
}Process;

//Struct for job that is implemented like a linked list
typedef struct Job{
	Process* headProcess;//Pointer to process that is first thread to be added to the job
	Process* tailProcess;//Pointer to process that is last thread to be added to the job
	char* status;			//Status of the job.  It can either be backgrounded, foregrounded, or suspended.
	tid_typ ID; //Same as groupID of the processes in the job
}Job;

//Extern keyword makes the property global
//see: http://stackoverflow.com/questions/1433204/how-do-i-share-a-variable-between-source-files-in-c-with-extern-but-how
//Number of jobs in the job list
extern int numberOfJobs;
//List of jobs
extern Job** listOfJobs;

//Basic initialization of job control shell
void init(void);
//Get each thread from the thread table and put them into jobs
int generateJob(void);
//Check to see if thread is already included in a job
bool isThreadInJobAlready(struct thrent* passedInThreadPointer);
//Get the job id for a given thread
int getJobId(struct thrent *passedInThreadPointer);
//Print out the jobs and their states
void printJobs(void);
//Check to see if job id exists
int doesJobExist( tid_typ jobID );
//Print out the jobs and their states
void printThreads(void);
//Frees any jobs that are done
void freeJobs(void);

#endif
	
