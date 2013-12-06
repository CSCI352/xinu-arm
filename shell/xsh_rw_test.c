#include <os_semaphore.h>
#include <shell.h>
#include <os_mutex.h>
#include <stdio.h>
#include <thread.h>

// Referenced from readers-writer problem article on wikipedia

int tst_reader();
int tst_writer();
/*
os_semaphore writer = os_create_semaphore(1);
os_mutex monitor = os_crete_mutex();
int readercount = 0;
*/

sem_id writer;
mut_id monitor;
int readercount = 0;
char* buffer[1];
/**
 *
 * Shell command syntax
 */
 

shellcmd xsh_rw_test(int nargs, char *args[])
{
    test();
}

void test()
{
    writer = os_create_semaphore(1);
    monitor = os_create_mutex();

    buffer[0] = 'b';
 tid_typ t1, t2, t3, t4;


 t2 = create(tst_reader, INITSTK, 21, "reader1", 0);
 ready(t2, RESCHED_YES);

 t3 = create(tst_reader, INITSTK, 21, "reader2", 0);
 ready(t3, RESCHED_YES);

 t1 = create(tst_writer, INITSTK, 21, "writer", 0);
 ready(t1, RESCHED_YES);

 t4 = create(tst_reader, INITSTK, 21, "reader3", 0);
 ready(t4, RESCHED_YES);

 fprintf(0,"Complete");

}
int tst_writer()
{

   fprintf( 0, "waiting for writer semaphore\n" );
   os_lock_semaphore(writer);
   fprintf( 0, "critical section:  writer is writing\n" );
   buffer[0] = 'a';
   os_unlock_semaphore(writer);
   fprintf( 0, "writing done\n" );
}
 
int tst_reader()
{
       fprintf( 0, "waiting for monitor signal\n" );
       os_lock_mutex(monitor);
       fprintf( 0, "start reading... (incr number of current readers)\n" );
       readercount++;
   
       // first reader must wait for writer to finish writing before beginning read
       if (readercount == 1)
       {
          
          fprintf( 0, "First reader. writer can't write now.\n" );
          os_lock_semaphore(writer);
       }
       os_unlock_mutex(monitor);
   
       fprintf( 0, "reading critical section...\n" );
       fprintf(0, "%c\n", buffer[0]);
       os_lock_mutex(monitor);
   
       fprintf( 0, "stopped reading (decr number of current readers\n" );
       readercount--;
   
   // last reader must signal to writer that it is free to start writing to critical section
       if (readercount == 0)
       {
          fprintf( 0, "last reader signals to writer\n" );
          os_unlock_semaphore(writer);
       }
       os_unlock_mutex(monitor);
}
