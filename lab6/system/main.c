/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

sid32 sem, mutex;
pid32 sender, receiver;

int main(int argc, char **argv)
{
        int send_msg(),receive_msg();

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

      int i;
      umsg32 msg[30];

      for(i=0;i<NMSG*2-1;i++) 
      {
           wait(mutex);
           sprintf(msg,"Message #%d is being processed\n", i);
           sendk(receiver, msg);
           signal(sem);
      }

}

receive_msg()
{

      int i;
      umsg32 msg;

      for(i=0;i<NMSG*2-1;i++) 
      {
           wait(sem);
           msg = receivek();
           kprintf("%s", msg);
           signal(mutex);

      }
}

