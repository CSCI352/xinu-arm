// Referenced from readers-writer problem article on wikipedia

os_semaphore writer = 1;
os_mutex monitor = 1;
readercount = 0;
 
int tst_writer()
{

   fprintf( 0, "waiting for writer semaphore\n" );
   os_lock_semaphore(writer);
   fprintf( 0, "critical section:  writer is writing\n" );
   os_unlock_semaphore(writer);
   fprintf( 0, "writing done\n" );

   return 0;
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

   return 0;
}
