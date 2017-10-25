/*Process control system calls: The demonstration of FORK, EXECVE and WAIT system calls along with zombie 
and orphan states.

a.
Implement the C program in which main program accepts the integers to be sorted. Main 
program uses the 
FORK
system call to create a new process called a child process. Parent process 
sorts the integers using sorting algorithm and waits for child process using 
WAIT
system call to 
sort the integers using any sorting algorithm. Also demonstrate zombie and orph
an states. 
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define max 10

void swap(int *a, int *b)
{
	
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int Partiton(int array[max],int start,int end)
{
	
	int partitionIndex, pivot, count;
	pivot = array[end];
	partitionIndex = start;

	for(count = start; count < end; count++)
	{
		if(array[count] <= pivot)
		{
			swap(&array[count], &array[partitionIndex]);
			partitionIndex ++;
		}
	}

	swap(&array[partitionIndex], &array[end]);
	return partitionIndex;

}


void Quicksort(int array[max], int start, int end)
{
	
	int partitionIndex;
	if(start < end)
	{
		partitionIndex = Partiton(array,start,end);
		Quicksort(array,start,partitionIndex-1);
		Quicksort(array,partitionIndex+1,end);
	}
}

void readArray(int array[max], int totalElements)
{
	int count;
	printf("Enter the array elements.\n");
	for (count = 0; count <= totalElements; count++)
	{
		scanf(" %d",&array[count]);
		
	}
	printf("Exitind read\n");

}

void displayArray(int array[max], int totalElements)
{
	int count;
	for (count = 0; count <= totalElements; count++)
	{
		printf("%d\t",array[count]);
	}
}

void Bubblesort(int array[max], int end)
{
	for(int i = 0; i < end-1; i++)
	{
		for(int j = 0; j < end-i-1; j++)
		{
			if(array[j] > array[j+1])
			{
				swap(&array[j], &array[j+1]);
			}
		}
	}
}
int main()
{
	int pid;
	int array[max], totalElements;
	printf("Enter number of elements in array\n");
	scanf(" %d",&totalElements);

	readArray(array,totalElements-1);

	pid = fork();

	if(pid < 0)
	{
		printf("Child process was not created\n");
	}

	else if(pid == 0)
	{
		printf("In Child Process\n");
		Quicksort(array,0,totalElements-1);
		printf("The elements sorted by Quicksort are\n");
		displayArray(array,totalElements-1);
	}

	else if(pid > 0)
	{
		wait(NULL);
		printf("In Parent Process\n");
		Bubblesort(array,totalElements);
		printf("The elements sorted by Bubblesort are\n");
		displayArray(array,totalElements-1);
	}
	

	
}

