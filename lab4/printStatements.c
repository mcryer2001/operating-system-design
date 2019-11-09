/* printStatements.c - printStatements, a, b, printMsg, destroySems */

#include <xinu.h>
#include <stdio.h>

char * a1 = "My first statement appears before Bob’s second statement. (a1) ";
char * a2 = "This is Alice’s second statement. (a2) ";
char * b1 = "My first statement appears before Alices’s second statement. (b1) ";
char * b2 = "This is Bob’s second statement. (b2) ";

void a(), b(), printMsg(), destroySems();
int a1_printed, b1_printed;
unsigned long should_block;
sid32 sem;

void printStatements(int interations)
{
  int i;
  for(i = 0; i < interations; i++) {
    a1_printed = 0;
    b1_printed = 0;
    unsigned long priority_a = rand() % 2 + 50;
    unsigned long priority_b = rand() % 2 + 50;
    priority_b = (priority_b == priority_a) ? priority_b + 1 : priority_b;

    sem          = semcreate(0);
    should_block = rand() % 2;

    pid32 process_a = create(a, 1024, (int) priority_a, "process A", 0);
    pid32 process_b = create(b, 1024, (int) priority_b, "process B", 0);

    if(priority_a > priority_b) {
      resume(process_a);
      resume(process_b);
    } else {
      resume(process_b);
      resume(process_a);
    }
  }
}

void a()
{
  a1_printed = 1;
  printMsg(a1, 0);

  if(b1_printed == 0) {
    wait(sem);

    if(should_block == 1) {
      printMsg(a2, 0);
    } else {
      printMsg(a2, 1);
      destroySems();
    }
  } else {
    if(should_block == 1) {
      signal(sem);
      printMsg(a2, 1);
      destroySems();
    } else {
      printMsg(a2, 0);
      signal(sem);
    }
  }
}

void b(pid32 parent_pid)
{
  b1_printed = 1;
  printMsg(b1, 0);

  if(a1_printed == 0) {
    wait(sem);

    if(should_block == 1) {
      printMsg(b2, 0);
    } else {
      printMsg(b2, 1);
      destroySems();
    }
  } else {
    if(should_block == 1) {
      signal(sem);
      printMsg(b2, 1);
      destroySems();
    } else {
      printMsg(b2, 0);
      signal(sem);
    }
  }
}

void printMsg(char * msg, int newLine)
{
  kprintf("%s", msg);

  if(1 == 1 || newLine == 1) {
    kprintf("\n");
  }
}

void destroySems() {
  semdelete(sem);
  kprintf("\n");
}
