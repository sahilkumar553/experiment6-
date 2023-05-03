#include<stdio.h>
#include<pthread.h>
int shared=5;
pthread_mutex_t l; /*mutex variable l*/
void *func1()
{
int local;
/*critical section */
pthread_mutex_lock(&l); /*applying lock using l(initally false)*/
local=shared;
local=local+1;
sleep(5); /* causes a context switch */
shared=local;
pthread_mutex_unlock(&l) /*releasing lock using l*/
/*critical section */
printf(“shared in func1: %d \n", shared);
pthread_exit(NULL);
}
void *func2()
{
int local;
/*critical section */
pthread_mutex_lock(&l); /*If acquired by func1 l will return true*/
local=shared;
local=local-1;
shared=local;
pthread_mutex_unlock(&l);
printf(“shared in func2: %d \n", shared);
pthread_exit(NULL);
}
int main()
{
pthread_t t1,t2;
pthread_create(&t1,NULL,func1,NULL);
pthread_create(&t2,NULL,func2,NULL);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
}
