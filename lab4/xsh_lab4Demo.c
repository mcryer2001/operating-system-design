/* xsh_lab4Demo */

#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*------------------------------------------------------------------------------
**
**-----------------------------------------------------------------------------*/
shellcmd xsh_lab4Demo(int nargs, char *args[])
{
  int iterations = 1;
  int length;
  char * next;
  pid32 parent_pid;

  if(nargs == 2) {
    length = strlen(args[1]);
    next   = args[1];

    int i;
    for(i = 0; i < length; i++) {
      if(!isdigit(next[i])) {
        kprintf("'%s' is not a valid number of iterations. \n", args[1]);
        return 1;
      }
    }
    iterations = atoi(args[1]);
    parent_pid = getpid();

    resume(create(printStatements, 1024, 30, "iteration " + i, 1, iterations));
    return 0;
  }
}
