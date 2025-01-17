/* receivek.c - receivek */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receivek  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receivek(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	//if (prptr->prhasmsg == FALSE) {
	if (prptr->msgcounter > NMSG*2) {
		prptr->prstate = PR_RECV;
		resched();		/* block until message arrives	*/
	}
	msg = prptr->prmsg;		/* retrieve message		*/
	prptr->prhasmsg = FALSE;	/* reset message flag		*/
	restore(mask);
	return msg;
}
