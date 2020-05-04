#include "types.h"
#include "defs.h"

int my_yield(char *str)
{
    yield();
    cprintf("%s\n", str);
    return 0;
}

//Wrapper
int sys_my_yield(void)
{
    char *str;
    if(argstr(0, &str) < 0)
        return -1;

    return my_yield(str);
}
