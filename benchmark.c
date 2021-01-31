#include "types.h"
#include "user.h"

int number_of_processes = 10;

int main(int argc, char *argv[])
{
  int j;
  for (j = 0; j < number_of_processes; j++)
  {
    int pid = fork();
    if (pid < 0)
    {
      printf(1, "Fork failed\n");
      continue;
    }
    if (pid == 0)
    {
        // ps();
      volatile int i;
      for (volatile int k = 0; k < number_of_processes; k++)
      {
        if (k <= j)
        {
          sleep(200); //io time
        }
        else
        {
          for (i = 0; i < 100000000; i++)
          {
            ; //cpu time
          }
        }
      }
      printf(1, "Process: %d Finished\n", j);
      exit();
    }
    else{
      // if(j<5)
      // {
      //   set_priority(100,pid); 
      // }
      // else
      // {
      //   set_priority(0,pid);
      // }
      set_priority(100-10*j,pid);
      
    }
  }
  for (j = 0; j < number_of_processes+5; j++)
  {
    // ps();
    wait();
     // ps();
  }
  exit();
}