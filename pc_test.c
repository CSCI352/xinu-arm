//  Pseudo-code source:  article on wikipedia

#define BUFFER_SIZE 25

int main( )
{
   os_mutex monitor = 1;
   os_semaphore fillCount = 0;
   os_semaphore emptyCount = BUFFER_SIZE;
   
   int buffer [BUFFER_SIZE] = {-1};
   
   producer(buffer);
   consumer(buffer);
   consumer(buffer);
}

int producer(int & bfr)
{
   while (true)
   {  
      os_lock_semaphore(emptyCount);
         os_lock_mutex(monitor);
            *bfr = 1;
            bfr ++;
         os_unlock_mutex(monitor);
      os_unlock_semaphore(fillCount);
   }
   
   return 0;
}

int consumer(int & bfr)
{
   while (true)
   {  
      os_lock_semaphore(fillCount);
         os_lock_mutex(monitor);
            *bfr = 0;
            bfr --;
         os_unlock_mutex(monitor);
      os_unlock_semaphore(emptyCount);
   }
   
   return 0;
}
