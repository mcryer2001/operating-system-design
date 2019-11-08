/* xsh_newproc */
#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/* ---------------------------------------------------------------------------
* xsh_newproc - shell command to create a new process with priority or default 
* ---------------------------------------------------------------------------- 
*/
shellcmd xsh_newproc(int nargs, char *args[])
{
	pri16 p;
	char* next;
	int length;
	int i;
	pid32 pid;
	pri16 defaultPrio = INITPRIO;
	pri16 startPrio = 90;

	if (nargs == 1) {
		p = defaultPrio;
	}
	else if (nargs == 2) {
		/* Argument error check code.  THIS SHOULD WORK as Xinu does have the isdigit macro in ctype.h */
		length = strlen(args[1]);
		next = args[1];

		for (i = 0; i < length; i++) {
			if (!isdigit(next[i])) {
				kprintf ("'%s' is not valid \n", args[1]);
				return 1;
			}
		}
		p = atoi(args[1]);
	}
	else {
		kprintf("Too many arguments \n");
		return 1;
	}

	pid = create(foreverRun, 1024, startPrio, "Test", 1, p);
	resume(pid);
	return 0;
}
