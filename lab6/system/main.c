/* main.c - main */ 
#include <xinu.h> 
int ROUND_ROBIN = 0; 
void imaprocessyo(); 
pid32 pid; 
void main(void) 
	{ 
		// ready(create((void *)shell, INITSTK, INITPRIO, "SHELL0", 3, 
		// CONSOLE, CONSOLE, CONSOLE), 
		// RESCHED_NO); 
		pid = create(imaprocessyo, 1024, 21, "Process 2", 0); 
		resume(pid); 
		sendk(pid, "this "); 
		sendk(pid, "does "); 
		sendk(pid, "multiple "); 
		sendk(pid, "messages "); 
		sendk(pid, "last message possible"); 
		sendk(pid, "create error"); 
		// char test[] = "This works at least"; 
		// kprintf("%s\n", test); 
		} 
		void imaprocessyo() 
		{ 
			sleep(5); int i = 0; 
			for (i; i < 6; i++) { 
									umsg32 str = receivek(); 
									kprintf("%s", str); 
							} 
		}