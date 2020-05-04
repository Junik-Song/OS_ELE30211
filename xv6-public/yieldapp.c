#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int i;
    int pid;
    char *par="Parent";
    char *chi="Child";

    pid = fork();
    if(pid == -1)
    {
        printf(0,"FORK ERROR\n");
        exit();
    }
    if(pid == 0)
    {
         for(i=0; i<10; i++)
         {
              my_yield(chi);
         }
         exit();
     }       
     else
     {
         for(i=0; i<10; i++)
         {
            my_yield(par);
         }
         wait();
         exit();
     }
  
    return 0;
}
