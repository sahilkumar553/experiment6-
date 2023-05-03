#include<stdio.h>
#include<pthread.h>
int shared=5;
sem_t s; /*mutex variable l*/
void *func1()
{
int local;
/*critical section */
sem_wait(&s) /*applying lock using l(initally false)*/
local=shared;
local=local+1;
sleep(5); /* causes a context switch */
shared=local;
sem_post(&s) /*releasing lock using l*/
/*critical section */
printf(“shared in func1: %d \n",shared);
pthread_exit(NULL);
}
void *func2()
{
int local;
/*critical section */
sem_wait(&s) /*If acquired by func1 l will return true*/
local=shared;
local=local-1;
shared=local;
sem_post(&s); /*releasing lock using l*/
/*critical section */
printf(“shared in func2: %d \n", shared);
pthread_exit(NULL);
}
int main()
{
pthread_t t1, t2;
sem_init(&s,0,1); /*initializing semaphore*/
pthread_create(&t1,NULL,func1,NULL);
pthread_create(&t2,NULL,func2,NULL);
  pthread_join(t1,NULL);
pthread_join(t2,NULL);
}
