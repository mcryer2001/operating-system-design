/* Place code in this file */
/* Luke Evans, David Howick, Kenneth Smith, William Scott, Michael Cryer */

#include <xinu.h>

void dummy(int32);

/*------------------------------------------------------------------------
 *  main  -  Creates the signaler and waiter processes
 *------------------------------------------------------------------------
 */
int main(void)
{
    
    resume(create(dummy, 1024,  5, "Process 2", 1, 2));
    resume(create(dummy, 1024, 10, "Process 3", 1, 3));
    resume(create(dummy, 1024, 20, "Process 4", 1, 4));
    
}

void dummy(int32 i)
{
    kprintf("Process %d is running...\n", i);
    sleep(5);
    while(1){
        kprintf("Process %d is running...\n", i);
    }
}

