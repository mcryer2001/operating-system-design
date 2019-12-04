/* receivek.c - receivek */ 
#include <xinu.h> 
/*------------------------------------------------------------------------ 
* receivek - buffer multiple messages and return them one at a time to the caller 
*------------------------------------------------------------------------ */ 
int findmsgend(procent); 
void shiftMessages(procent, pos); 
umsg32 receivek(void) 
{ 
	intmask mask; /* saved interrupt mask */ 
	struct procent *prptr; /* ptr to process' table entry */ 
	umsg32 msg; /* message to return */ 
	mask = disable();
4
prptr = &proctab[currpid]; 
if (prptr->prhasmsg == FALSE) { prptr->prstate = PR_RECV; resched(); 
/* block until message arrives */ } 
int end = findmsgend(prptr); 

if (end == 0) { /* no messages */ restore(mask);
 return SYSERR; 
 } 
 int pos = end - 1; 
 msg = prptr->messages[0]; 
 shiftMessages(prptr, pos); 
 if (pos < 1) 
 { 
	prptr->prhasmsg == FALSE; 
 }
 //msg = prptr->prmsg; /* retrieve message */ 
 //prptr->prhasmsg = FALSE; /* reset message flag */ 
 restore(mask); 
 return msg; 
 } 
 int findmsgend(struct procent *prptr) 
 { 
	int i = 0; 
	for (i; i < MSGLIMIT; i++) 
	{ 
		if (prptr->messages[i] == NULL) 
		{ 
			return i; 
		} 
		} return i; 
	} 
	
void shiftMessages(struct procent *prptr, int pos) 
	{ 
			int i = 1; 
			for (i; i <= pos; i++) 
			{ 	
				int newpos = i - 1; 
				prptr->messages[newpos] = prptr->messages[i]; 
				} 
				prptr->messages[pos] = NULL; 
				prptr->msgcount -= 1; 
	}