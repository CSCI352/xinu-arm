/**
 * @file     xsh_buddy.c
 * @provides xsh_buddy.
 * @author Blake Gross
 */

#include <stddef.h>
#include <buddymemory.h>
#include <slabmemory.h>
//#include <linkedListMalloc.h>
#include <stdio.h>
#include <string.h>
#include <memstat.h>
#include <clock.h>

shellcmd xsh_buddy(int nargs, char *args[])
{
	int i;
	
	ulong startTime = clkticks;
	buddyMalloc(1024);
	for( i = 0; i < 100; ++i )
	{
		if( buddyMalloc(5) == 0 )
		{
			printf( "Buddy Malloc failed\n" );
			break;
		}
	}
	
	ulong endTime = clkticks;
	endTime -= startTime;
	
	printMemUsage();
	printf("Malloced memory in time of %d, %d\n", endTime);
	
	slabInit();
	startTime = clkticks;
	for( i = 0; i < 100; ++i )
	{
		printf("At malloc pos %d: ", i );
		void* object = slabAlloc( sizeof(int) );
		if( object == 0  )
		{
			printf( "Slab Malloc failed\n" );
			break;
		}
		slabFree( object );
		if( object == 0 )
		{
			printf( "Free failed" );
		}
	}
	slabCleanup();
	printMemUsage();
	endTime = clkticks;
	
	endTime-=startTime;
	printf("Malloced memory in time of %d, %d\n", endTime);
		

	printMemUsage();
	buddyDealloc();
	
	printf("Dealloced memory\n");
	
	printMemUsage();

	//////////////////////////////////////////
	/// Linked List Test
	//////////////////////////////////////////

	//void * loc;
	//printf("Allocating memory\n");
	//loc = linkedListMalloc(50);
	//printf("Memory allocated\n");
	//printf("Deallocating memory\n");
	//removeNode(loc);
	//printf("Memory deallocated");
	//printf("Freeing memory\n");
	//freeMemory();
	//printf("MemoryFreed\n");
	return 0;
}
