#include <xinu.h>

void foreverRun(void)
{
	kprintf("foreverRun is Running PID %d\n", getpid());

	while(1) {}
}