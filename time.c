#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int main(int argc, char **argv)
{
	int wt=-1,rt=-1,stat=-1;
	int pid = fork();
    if(pid>0)
	{
		stat = waitx(&wt,&rt);
        if(argc>1)
        {
		    printf(1,"Wait time: %d\nRun time: %d\nStatus %d\n",wt,rt,stat);
        }
		exit();
	}
	else
	{
		if (argc<2)
		{
			printf(2,"Error: time requires 1 command\n");
		}
		else
		{
			exec(argv[1], argv + 1);
			printf(2, "exec %s failed\n", argv[1]);
		}
        exit();
	}
}