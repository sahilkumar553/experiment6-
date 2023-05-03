#include<stdio.h> 

#include<stdlib.h>
#include <unistd.h>
#include<sys/shm.h> 
#include<string.h> 
int main()
{
void *shm;
char buf[200];

int shmid;
shmid-shmget((key_t)123, 2048, 0666|IPC_CREAT);
printf("The Key value of shared memory is %d\n",shmid);
shm-shmat(shmid,NULL,0); 
printf("process attached to the address of %d p\n",shm);
printf("write theb data to shared memory ");
read(0,buff,100);
strcpy(shm,buf);

printf("The stored data in shared memory is : %s\n",(char *)shm);
}
