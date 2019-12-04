/*receivek.c - receivek */
#include <xinu.h>

/*------------------------------------------------------------------------
 *receivek  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32 receivek(void)
{
	intmask mask;          /* saved interrupt mask		*/
	struct procent *prptr; /* ptr to process' table entry	*/
	umsg32 msg;            /* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];

	if (prptr->msgcounter == 0)
	{
		prptr->prstate = PR_RECV;
		resched();          /* block until message arrives */
	}

	msg = prptr->messages[0];   /* retrieve message            */

	if (prptr->nextMsgIndex == NMSG)
	{
		prptr->nextMsgIndex--;
		shiftMessages(prptr, prptr->nextMsgIndex++);
	}
	prptr->msgcounter--;

	prptr->prhasmsg = FALSE;    /* reset message flag         */
	restore(mask);
	return msg;
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
}
