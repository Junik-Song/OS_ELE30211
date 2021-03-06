#include "types.h"
#include "user.h"
#include "stat.h"

#define NULL 0

int main()
{
    if(getadmin("2016024884")!=0)
    {
        printf(1,"Admin Error\n");
        return 0;
    }
    printf(1,"[Process Manager]\n\n");
    

    char *temp;
    char *path;
    int pid, num;
    temp = "Iwanttogohome";

    while(1!=0)
    {
        printf(1,"\n>");
       
        gets(temp, 100);
    	temp=strtok(temp, " ");
        if(strcmp(temp, "list\n") == 0 || strcmp(temp, "list")==0)
        {
            list();
        }

        else if(strcmp(temp, "memlim")==0)
        {
    	    pid = atoi(strtok(0, " "));
            num = atoi(strtok(0, " "));
	  
	        printf(1,"setting Process %d's limit to %d...\n", pid, num);
            
    	    if(setmemorylimit(pid, num) == 0)
            {
                 printf(1,"setmemorylimit success!\n");
            }

            else printf(1, "setmemorylimit failed. so sad.\n");
                
        }

        else if(strcmp(temp, "kill")==0)
        {
	        pid = atoi(strtok(NULL, " "));
            if(kill(pid) == 0)
            {
                printf(1,"killed process %d!\n", pid);
            }

            else printf(1,"kill error\n");
            
        }

    	else if(strcmp(temp, "exit\n")==0 || strcmp(temp, "exit") == 0) 
        {
            wait();
            break;
        }

        else if(strcmp(temp, "execute") == 0)
        {
            path = strtok(NULL, " ");
            num = atoi(strtok(NULL, " "));
           
            if(fork()==0)
            {
                if(exec2(path, &path, num) != 0)
                {
                        printf(1, "exec2 Failed :(\n");
                }
            }
            
        }

    }


    printf(1, "Bye!\n");

    exit();
    
}
