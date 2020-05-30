#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}

#define NULL 0

/*

source from
http://www.koders.com/c/fidE1F6D546E578F9FF41B8000B08F8A73D4D86F8FA.aspx

*/
int strcspn(const char *s, const char *reject) {
  int count = 0;

  while (*s != '\0')
    if (strchr(reject, *s++) == NULL)
      ++count;
    else
      return count;

  return count;
}

char *
strtok(char *s, const char *delim)
{
     /*s: string to search for tokens */
     /*delim: delimiting characters */

    static char *lasts;
    register int ch;
    
    if (s == 0)
    {
    	s = lasts;
    }

    do {
	if ((ch = *s++) == '\0')
	    return 0;
    } while (strchr(delim, ch));
    --s;
    lasts = s + strcspn(s, delim);
    if (*lasts != 0)
	*lasts++ = 0;

    return s;
}
