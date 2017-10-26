/*
FIFOs: Full duplex communication between two independent processes. First process accepts 
sentences and writes on 
one pipe to be read by second process and second process counts 
number of characters, number of words and number of lines in accepted sentences, writes this 
output in a text file and writes the contents of the file on second pipe to be read by first proces
s 
and displays on standard output.

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>		/*Included for O_WRONLY and O_RDONLY*/
#include <errno.h>		/*Included for EEXIST*/

extern int errno;

int main()
{
	int f1 = 0, f2 = 0;	
	char Sentence[100];
	char ReadSentence[300];
	int ret = 0;
	printf("\n***********IPC USING NAMED PIPES*************");
	printf("\nCREATING NAMED PIPE 1(fifo1)...");
	
	ret = mkfifo("/tmp/Fifo1", 0666);//creating Fifo1


	if((ret < 0) && (errno != EEXIST))//Error in creating the FIFO
	{
		printf("Error in creating the FIFO.\n");
		return;
	}

	if(errno == EEXIST)
		printf("FIFO already exists. \n");

	printf("Enter a sentence : ");//Accepting Strings
	fgets(Sentence, 100, stdin);

	printf("Writing the sentence to FIFO1...\n\n");
	f1 = open("/tmp/Fifo1", O_WRONLY);//opening Fifo1 in Write mode	

	write(f1, Sentence, (strlen(Sentence)+1));//Writing the sentence to FIFO1
	
	printf("Waiting for output from FIFO2...\n\n");
	sleep(5);
	f2 = open("/tmp/Fifo2", O_RDONLY);//opening Fifo2 in Read mode	
	read(f2, ReadSentence, 300);

	printf("The output is : \n");
	printf("%s", ReadSentence);//Displaying Output

	unlink("/tmp/Fifo1");//unlink Fifo1

	return 0;
}