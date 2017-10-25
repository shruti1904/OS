#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define SHMSZ 25
int main()
{
	int shmid,cnt=0;
	key_t key;
	char *shm,*s;
	char *str;
	str=(char *)malloc(sizeof(char)*15);
	key=5678;	

		/*
		shm_id = shmget(
               key_t     k,        - the key for the segment         
               int       size,     - the size of the segment         
               int       flag);    - create/use flag                 
	 */

	if((shmid=shmget(key,SHMSZ,IPC_CREAT|0666))<0)		//creating segment
	{
		perror("shmget");
		exit(1);
	}

	/*shm_ptr = shmat(
               int       shm_id,        - shared memory ID    
               char      *ptr,          - a character pointer 
               int       flag);         - access flag   
	*/

	if((shm=shmat(shmid,NULL,0))==(char *)-1)			//attaching segment to database
	{
		perror("shmat");
		exit(1);
	}

	//s is a pointer for traversal.
	//shm is the points to the start of the shared memory segment

	s=shm;												//writing things to memory
	printf("\nEnter message from Server to Client : ");
	scanf("%[^\n]s",str);
	for(cnt=0;str[cnt]!='\0';cnt++)
	{
		*s++=str[cnt];
	}
	//Put a \0 at the end of the message
	*s='\0';

	//shmdt(shm_ptr);
	shmdt(shm);
	return 0;
}

/*

OUTPUT :

Enter message from Server to Client : Hello Client ! I am a Server.

*/
