/* send.c - send */ 
#include <xinu.h> 
#include <stdio.h> 
#include <stdlib.h> 
int MSG_SIZE; 
int findpos(procent); 
/*------------------------------------------------------------------------ 
* send - pass a message to a process and start recipient if waiting 
*------------------------------------------------------------------------
*/

syscall sendk( 
	pid32 pid, /* ID of recipient process */ 
	umsg32 msg /* contents of message */ 
	) 
	{ 
		intmask mask; /* saved interrupt mask */
		struct procent *prptr; /* ptr to process' table entry */ 
		mask = disable(); 
		if (isbadpid(pid)) 
		{ 
	restore(mask); 
	return SYSERR; 
	} 
	prptr = &proctab[pid]; 
	if ((prptr->prstate == PR_FREE)) 
	{ 
		restore(mask); 
		return SYSERR; 
		} 
	int pos = findpos(prptr); 
	if (pos == -1) 
	{ 
		restore(mask); 
		return SYSERR; 
	}
	
	prptr->messages[pos] = msg; /* deliver message */ 
	if (prptr->msgcount == NULL) 
	{ 
		prptr->msgcount = 1; 
	}
	
	else if (prptr->msgcount > 4) 
	{ 
		restore(mask); 
		return SYSERR; 
		} 
		else 
		{ 
			prptr->msgcount += 1; 
		} prptr->prhasmsg = TRUE; /* indicate message is waiting */ 
		/* If recipient waiting or in timed-wait make it ready */ 
		
		if (prptr->prstate == PR_RECV) 
		{ 
			ready(pid, RESCHED_YES); 
		} else if (prptr->prstate == PR_RECTIM) 
		{ 
			unsleep(pid); 
			ready(pid, RESCHED_YES); 
			} 
			restore(mask); /* restore interrupts */ 
			return OK; 
			} 
	int findpos(struct procent *prptr) 
	{ 
			int i = 0; 
			for (i; i < MSGLIMIT; i++) 
			{ 
				if (prptr->messages[i] == NULL) 
				{ 
					return i; } 
			} return -1; 
	}
	
	
	
	