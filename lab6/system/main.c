/* main.c - main */ 
#include <xinu.h> 
int ROUND_ROBIN = 0; 
void receivemessageprocess(); 
pid32 pid; 
void main(void) 
	{ 
		// ready(create((void *)shell, INITSTK, INITPRIO, "SHELL0", 3, 
		// CONSOLE, CONSOLE, CONSOLE), 
		// RESCHED_NO); 
		pid = create(receivemessageprocess, 1024, 21, "Process 2", 0); 
		resume(pid); 
		sendk(pid, "this \n"); 
		sendk(pid, "does \n"); 
		sendk(pid, "multiple \n"); 
		sendk(pid, "messages \n"); 
		sendk(pid, "last message possible \n"); 
		sendk(pid, "message 6 \n"); 
		sendk(pid, "message 7 \n"); 
		sendk(pid, "message 8 \n"); 
		sendk(pid, "message 9 \n"); 
		sendk(pid, "message 10 \n"); 
		// char test[] = "This works at least"; 
		// kprintf("%s\n", test); 
		} 
		void receivemessageprocess() 
		{ 
			sleep(5); int i = 0; 
			for (i; i < NMSG; i++) { 
				umsg32 str = receivek(); 
				kprintf("%s", str); 
			} 
		}