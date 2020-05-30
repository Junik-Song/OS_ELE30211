#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_getppid(void)
{
    return myproc()->parent->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

void
sys_yield(void)
{
#ifdef MLFQ_SCHED
    myproc()->level=0;
    myproc()->tick=0;
#endif
    yield();
    return;
}

int
sys_getlev(void)
{
    int level = getlev();
    return level;
}

int
sys_setpriority(int pid, int priority)
{  
    
    int spid, spriority;
    argint(0, &spid);
    argint(1, &spriority);
    return setpriority(spid, spriority);
}

void
sys_list(void)
{
    list();
    return;
}

void
sys_procdump(void)
{
    procdump();
    return;
}

int
sys_getadmin(char *password)
{
    char *spw;
    argstr(0, &spw);
    char *rpw = "2016024884";
    
    if(strncmp(spw,rpw,30)==0)
    {

        return getadmin(spw);
    }

    else return -1;
}

int
sys_setmemorylimit(int pid, int limit)
{
    argint(0, &pid);
    argint(1, &limit);


    if(myproc()->admin != 1) return -1;

    else return setmemorylimit(pid, limit);
}

char*
sys_getshmem(int pid)
{
    argint(0, &pid);

    return getshmem(pid);
}
