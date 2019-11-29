/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

sid32 sem, mutex;
pid32 sender, receiver;
int send_msg(),receive_msg(),print_msg();


int main(int argc, char **argv)
{
        sem = semcreate(0);
        mutex = semcreate(1);

        sender = create(send_msg, 1024, 30, "send_msg", 0);
        receiver = create(receive_msg, 1024, 20, "receive_msg", 0);

        resume(sender);
        resume(receiver);

	return OK;
}

send_msg()
{

      int i, status;
      umsg32 msg[30];

      for(i=0;i<NMSG*2;i++) 
      {
           wait(mutex);

           sprintf(msg,"Message #%d is being processed\n", i);

           status = sendk(receiver, msg);
           if (status == SYSERR)
           {
           	sprintf(msg,"Error processing message #%d\n", i);
                print_msg(msg);
           }

           signal(sem);
      }

}

receive_msg()
{

      int i;
      umsg32 msg;

      for(i=0;i<NMSG*2;i++) 
      {
           wait(sem);
           msg = receivek();
           print_msg(msg);
      }
}


print_msg(umsg32 msg)
{
      kprintf("%s", msg);
      signal(mutex);
}

