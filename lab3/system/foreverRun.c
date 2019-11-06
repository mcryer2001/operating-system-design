#include <xinu.h>

void foreverRun(pri16 p)
{
	pid32 currpid;

	currpid = getpid();

	kprintf("foreverRun is Running PID %d with Priority %d\n", currpid, p);
	chprio(currpid, p);
	while(1) {}
}