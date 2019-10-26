/* xsh_newproc */
#include <xinu.h>
/* ---------------------------------------------------------------------------
* xsh_newproc - shell command to create a new process with priority or default 
* ---------------------------------------------------------------------------- 
*/
shellcmd xsh_newproc(int nargs, char *args[])
{
	int32 p;
	char ch;
	char* chprio;
	pid32 pid;
	int32 defaultPrio = 20;

	if (nargs == 1) {
		p = defaultPrio;
	}
	else if (nargs == 2) {
		chprio = args[1];
		ch = *chprio++;
		p = 0;

		while (ch != NULLCH) {
			if ((ch < '0') || (ch > '9')) {
				kprintf("%s: non-digit in p \n", args[1]);
				return 1;
			}
			p = 10 * p + (ch - '0');
			ch = *chprio++;
		}
	}
	else {
		kprintf("Too many arguments \n");
		return 1;
	}

	pid = create(foreverRun, 1024, p, "Test", 0);
	resume(pid);
	return 0;
}