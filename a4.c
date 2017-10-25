/*
Thread synchronization using counting 
semaphores. Application to demonstrate: 
producer-consumer problem with counting semaphores and mutex.
*/

#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>

sem_t mutex,full,empty;

//Mutex ensures that only one process shares the resource
//Full is for the number of slots in the buffer which are full
//Empty is for the number of slots in the buffer which are empty

int *buffer,front=0,rear=0,count=1;
int sizeOfBuffer;

void *Producer(void *p);
void *consumer(void *p);


int main(int argc,char *argv[])
{

	
	int choice;

	//producer consumer loop iterator
	int gProduce=3;
	int gConsume=3;					
	
	//loop iterator
	int i; 			
	     	
	//Get size of buffer for dynamic memory allocation
	printf("\n Enter Size of Buffer:\n");			
	scanf("%d",&sizeOfBuffer);

	buffer = (int*) malloc(sizeOfBuffer*sizeof(int));
	
	//Initialize mutex to 1
	sem_init(&mutex,0,1);

	//Initialize full to 0					
	sem_init(&full,0,0);

	//Initialize empty to size					
	sem_init(&empty,0,sizeOfBuffer);   


	while(1)
	{
	     
		//Create an array of thread id which is the size of the goods to be produced
		pthread_t tid_p[gProduce];

		pthread_attr_t attr_p;
		pthread_attr_init(&attr_p);
	     
	    //Create threads for goods to be produced
		for(i=0;i<3;i++)
		{   
			void *p=i;

			//Creation of pthread
        		//Argument 1 is pointer to id of the thread
        		//Argument 2 are the default attributes
        		//Argument 3 is the name of the function 
        		//Argument 4 is the arguments of the function 
			pthread_create(&tid_p[i],&attr_p,Producer,p);

			
	    }
		
		//Create an array of thread id which is the size of the goods to be consumed
		pthread_t tid_c[gConsume];

		pthread_attr_t attr_c;
		pthread_attr_init(&attr_c);
	      	
	    
	    //Create threads for goods to be consumed
	    for(i=0;i<gConsume;i++)
	    {          
			void *c=i;
			pthread_create(&tid_c[i],&attr_c,consumer,c);
		}
		
		
	    printf("\n Do you want to continue?(1/0):\n");
	    scanf("%d",&choice);
	    if(choice == 0)
		break;
	}  
}

void *Producer(void *p)
{
	int t=p;
	 
	printf("\nProducer %d begins.\n",t);

	//Decrement empty after production
	sem_wait(&empty);

	//Decrement mutex so that mutex = 0
	sem_wait(&mutex);

	//Put the produced element in the buffer
	buffer[rear]=count;

	printf("\n\tProduced Element: %d \n",buffer[rear]);
	rear=(rear+1)%sizeOfBuffer;
	count++;
	
	sleep(4);

	//Increment mutex so mutex = 1
	sem_post(&mutex);

	//Increment full after production
	sem_post(&full);

	printf("\nProducer %d ends.\n",t); 

	printf("\n************************************************************\n");
 
	for(int i=0;i<sizeOfBuffer;i++)
			printf("\t %d",buffer[i]);

	printf("\n************************************************************\n");

	pthread_exit(0);
}

void *consumer(void *p)
{
	int t=p;

	printf("\nConsumer %d begins\n",t);

	//Decrement full after consumption
	sem_wait(&full);

	//Decrement mutex so that mutex = 0
	sem_wait(&mutex);
 
	printf("\n\tConsumed Element: %d \n",buffer[front]);
	//Remove the croduced element from the buffer
	buffer[front]=0;
	front=(front+1)%sizeOfBuffer;
    	
    sleep(4);

    //Increment mutex so mutex = 1
	sem_post(&mutex);

	 //Increment empty after production
	sem_post(&empty);

	printf("\nConsumer %d ends.\n",t);

	printf("\n************************************************************\n");
 
	for(int i=0;i<sizeOfBuffer;i++)
			printf("\t %d",buffer[i]);

	printf("\n************************************************************\n");

   	pthread_exit(0);
}

