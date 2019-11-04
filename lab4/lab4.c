/* sync_lab4.c - main, a, b */

#include <xinu.h>
#include <stdio.h>

char * a1 = "a1 ";
char * a2 = "a2 ";
char * b1 = "b1 ";
char * b2 = "b2 ";

void a(), b(), printMsg();

int a1_printed = 0;
int b1_printed = 0;

sid32 sem, mutex;

int main(void)
{
  unsigned long priority_a = rand() % 2 + 50;
  unsigned long priority_b = rand() % 2 + 50;
  sem   = semcreate(0);
  mutex = semcreate(1);

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

void a(void)
{
  wait(mutex);
  a1_printed = 1;
  printMsg(a1);
  signal(mutex);

  unsigned long should_block = rand() % 2;
  if(b1_printed == 0) {
    wait(sem);
    printMsg(a2);
  } else {
    if(should_block == 1) {
      signal(sem);
      printMsg(a2);
    } else {
      printMsg(a2);
      signal(sem);
    }
  }
}

void b(void)
{
 wait(mutex);
 b1_printed = 1;
 printMsg(b1);
 signal(mutex);

 unsigned long should_block = rand() % 2;
 if(a1_printed == 0) {
  wait(sem);
  printMsg(b2);
 } else {
  if(should_block == 1) {
    signal(sem);
    printMsg(b2);
  } else {
    printMsg(b2);
    signal(sem);
  }
 }
}

void printMsg(char * msg)
{
  kprintf("%s", msg);
  sleepms(500);
}