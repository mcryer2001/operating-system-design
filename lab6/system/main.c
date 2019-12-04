/*main.c - main */ 
#include <xinu.h>

void receive_msg();
pid32 pid;

void main(void)
{
	pid = create(receive_msg, 1024, 21, "Process 2", 0);

	resume(pid);

	sendk(pid, "this");
	sendk(pid, "does");
	sendk(pid, "multiple");
	sendk(pid, "messages");
	sendk(pid, "last message possible");
	sendk(pid, "message 6");
	sendk(pid, "message 7");
	sendk(pid, "message 8");
	sendk(pid, "message 9");
	sendk(pid, "message 10");
}

void receive_msg()
{
	sleep(5);
	int i = 0;
	for (i; i < NMSG; i++)
	{
		umsg32 str = receivek();
		kprintf("%s\n", str);
	}
}
