#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void setPriority(int argc, char *argv[])
{
  int new_priority,pid,retvalue;
  if(argc < 3){
    printf(2,"Error: setPriority requires exaxtly 2 arguments\n");
    exit();
  }
  new_priority = atoi(argv[1]);
  pid = atoi(argv[2]);
  if (new_priority < 0 || new_priority > 100)
  {
    printf(2,"Error: new_priority should be in [0,100]\n");
    exit();
  }
  retvalue = set_priority(new_priority,pid);
  if(retvalue==-1)
  {
      printf(2,"Error: couldn't change priority.\nMay be no such process\n");
  }
  exit();
}