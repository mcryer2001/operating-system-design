/*sendk.c - sendk */
#include <xinu.h>

/*------------------------------------------------------------------------
 *sendk  -  pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall sendk(	pid32 pid,      /* ID of recipient process	*/
	        umsg32 msg      /* contents of message		*/
)

{
	intmask mask;           /*saved interrupt mask		*/
	struct procent * prptr; /*ptr to process' table entry	*/

	mask = disable();
	if (isbadpid(pid))
	{
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];

	prptr->msgcounter++;

	if (prptr->prstate == PR_FREE)
	{
		restore(mask);
		return SYSERR;
	}

	if (prptr->msgcounter > NMSG)
	{
		prptr->msgcounter--;
		kprintf("%s! Original Message: %s\n", "Error processing message", msg);
	}
	else
	{
		kprintf("Processing message: %s\n", msg);
		prptr->messages[prptr->nextMsgIndex] = msg;
		prptr->nextMsgIndex++;
		prptr->prmsg = msg;     /*deliver message		*/
		prptr->prhasmsg = TRUE; /*indicate message is waiting	*/
	}

	/*If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV)
	{
		ready(pid, RESCHED_YES);
	}
	else if (prptr->prstate == PR_RECTIM)
	{
		unsleep(pid);
		ready(pid, RESCHED_YES);
	}
	restore(mask); /*restore interrupts */
	return OK;
}
