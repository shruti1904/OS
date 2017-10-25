#include<stdio.h>
#include<unistd.h>
#include<string.h>


/*Main Function*/
int main(int argc , char **argv)
{
	int first, last, middle, n ,key, array[100], i, sum=0;
	
	printf("\n Inputs count = %d",argc);

	for(i=0;i<argc;i++)
	{
		
		array[i]=atoi(argv[i]);/*atoi for conversion of string to int*/
		printf("\n %d",array[i]);
	}

	printf("\n Enter value to find : \n");
	scanf("%d",&key);

	/*Binary Search*/
	n=argc;
	first=0;
	last=n-1;
	middle=(first+last)/2;
	
	while( first <= last)
	{
		if(array[middle] < key)
			first=middle + 1;
		else if(array[middle] == key)
		{
			printf("\n%d found at location %d.\n",key,middle+1);	
			break;
		}
		else
			last = middle - 1;
			middle = (first + last )/2;
	}
	if( first > last)
	{
		printf("\n The element [%d] does not exist in the list.\n",key);
	}
	return 0;
}

