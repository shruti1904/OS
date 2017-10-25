#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define SHMSZ 25
int main()
{
	int shmid;
	key_t key;
	char *shm, *s;
	key=5678;										//get segment 5678 created by server
	if((shmid=shmget(key,SHMSZ,0666))<0)			//locate segment
	{
		perror("shmget");
		exit(1);
	}
	if((shm=shmat(shmid,NULL,0))==(char *)-1)		//attach segment to database
	{
		perror("shmat");
		exit(1);
	}
	printf("Client reading data from Server : \n");
	for(s=shm;*s!='\0';s++)							//read
	{
		putchar(*s);
	}
	printf("\n");
	shmdt(shm);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
/*

OUTPUT :

Client reading data from Server : 
Hello Client ! I am a Server.

*/
