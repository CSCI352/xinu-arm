// Referenced from readers-writer problem article on wikipedia
// Source: Communications of the ACM :Concurrent Control with "Readers" and "Writers" P.J. Courtois,* F. H, 1971

os_semaphore writer = 1;
os_mutex monitor = 1;

// Number of readers accessing critical section
readercount = 0;

// Writer attempts to write in critical section
//   Cannot if Readers (at least 1) are accessing critical section.
int tst_writer()
{

   fprintf( 0, "waiting for writer semaphore\n" );
   os_lock_semaphore(writer);
   fprintf( 0, "critical section:  writer is writing\n" );
   os_unlock_semaphore(writer);
   fprintf( 0, "writing done\n" );

   return 0;
}

// Reader attempts to read from critical section
//   Cannot access if writer is writing to critical section
//     (only first reader checks this)
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
