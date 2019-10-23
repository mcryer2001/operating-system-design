/* Luke Evans, David Howick, Kenneth Smith, William Scott, Michael Cryer */
/* Lab_2_Team_2.c - main, signaler, waiter */

#include <xinu.h>

void signaler(), waiter();
int  sem_start_value = 20, count_start = 0, count_stop = 2000;
char * waiter_sentence = "Wow, I am running \n";
sid32 sem;

/*------------------------------------------------------------------------
 *  main  -  Creates the signaler and waiter processes
 *------------------------------------------------------------------------
 */
int main(void)
{
  sem = semcreate(sem_start_value);
  pid32 signaler_pid = create(signaler, 1024, 20, "signaler", 0);
  pid32 waiter_pid   = create(waiter, 1024, 40, "waiter", 1, signaler_pid);
  resume(signaler_pid);
  resume(waiter_pid);
}

/*------------------------------------------------------------------------
*  waiter -  Prints numbers from count_start to count_stop
*------------------------------------------------------------------------
*/
void waiter(pid32 signaler_pid)
{
  int i;
  for(i = count_start; i <= count_stop; i++) {
    kprintf("%d\n", i);
    wait(sem);
  }
  kill(signaler_pid);
  semdelete(sem);
}

/*------------------------------------------------------------------------
*  signaler  -  Prints a sentence
*------------------------------------------------------------------------
*/
void signaler(void)
{
  yield();
  while(1) {
    kprintf("%s", waiter_sentence);
    signaln(sem, 5);
  }
}
