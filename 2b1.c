/*
Implement the C program in which main program accepts an integer array. Main program uses 
the 
FORK
system call to create a new process called a child process. Parent process sorts an 
integer array and passes the sorted array to child process through the command line arguments 
of 
EXECVE
system call. The child process uses 
EXECVE
system call to load new 
program that uses 
this sorted array for performing the binary search to search the particular item in the array.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define max 10

void Merge(int Arr[max],int First, int mid, int Last)
{
	int cnt,cnt1, cnt2, Temp[max];
	cnt=0;
	cnt1 = First;
	cnt2=mid+1;
	while( (cnt1 <= mid) && (cnt2 <= Last))
	{
		if(Arr[cnt1] < Arr[cnt2])
		{
		Temp[cnt++] = Arr[cnt1];
		cnt1++;
		}
		else
		{
		Temp[cnt++] = Arr[cnt2];
		cnt2++;
		}
	}
	while(cnt1 <=mid )
	{
		Temp[cnt++] = Arr[cnt1];
		cnt1++;
	}
	while(cnt2 <= Last)
	{
		Temp[cnt++] = Arr[cnt2];
		cnt2++;
	}
	for(cnt1 =0; cnt1 < cnt; cnt1++)
	{
		Arr[First + cnt1] = Temp[cnt1];
	}
}

void MergeSort(int Arr[],int First, int Last)
{
	if(First < Last)
	{
		int mid,cnt;
		mid= (First + Last)/2;
		MergeSort(Arr, First,mid);
		MergeSort(Arr, mid+1 , Last);
		Merge(Arr, First, mid, Last);
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
	

}

void displayArray(int array[max], int totalElements)
{
	int count;
	for (count = 0; count <= totalElements; count++)
	{
		printf("%d\t",array[count]);
	}
}

int main()
{
	int pid;
	int count,Arr[max],totalElements;
	char **buffer = NULL;

	printf("Enter total elements of array\n");
	scanf("%d",&totalElements);

	readArray(Arr,totalElements-1);
	

	buffer = malloc(totalElements*sizeof(char*));

	for(count = 0; count < totalElements; count++)
	{
		buffer[count] = malloc(totalElements*sizeof(char*)); 
	}

	pid = fork();

	printf("Parent Process = %d", getppid());
	

	MergeSort(Arr,0,totalElements-1);
	displayArray(Arr,totalElements-1);
	
	
	for(count = 0; count < totalElements; count++)
	{

		sprintf(buffer[count],"%d",Arr[count]);
		// int sprintf(char *str, const char *format, ...) sends formatted output to a string pointed to, by str
		//Where str is pointer to an array of char elements where the resulting C string is stored.
		//format is the format specifier of the text to be written 
		// '...' is the data to be written to the str
		
	}
	
		buffer[count]='\0';
	
	execve("2b2",buffer,NULL);
	

	/*executes an existing file
	Syntax:
	int execve(const char *filename, char *const argv[], 
           char *const envp[]); 
    */

	
	return 0;
}

/*
OUTPUT

shruti@shruti-HP-Notebook:~/Documents/OSprep$ gcc 2b2.c -o 2b2
2b2.c: In function ‘main’:
2b2.c:16:12: warning: implicit declaration of function ‘atoi’ [-Wimplicit-function-declaration]
   array[i]=atoi(argv[i]);
            ^
shruti@shruti-HP-Notebook:~/Documents/OSprep$ gcc 2b1.c
shruti@shruti-HP-Notebook:~/Documents/OSprep$ ./a.out
Enter total elements of array
5
Enter the array elements.
4
7
1
2
8

 Inputs count = 5
 1
 2
 4
 7
 8
 Enter value to find : 

 Inputs count = 5
 1
 2
 4
 7
 8
 Enter value to find : 
7

7 found at location 4.
*/