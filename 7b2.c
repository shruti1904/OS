#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>		/*Included for O_WRONLY and O_RDONLY*/
#include <errno.h>		/*Included for EEXIST*/

int main()
{
	int f1=0, f2=0;
	
	char ReadSentence[100];
	char Buffer[300];
	
	int NoCharacters = 0;
	int NoWords = 0;
	int NoLines = 0;
	int ret;	
	FILE *fptr;
	
	ret = mkfifo("/tmp/Fifo2", 0666);//creating Fifo2

	if((ret < 0) && (errno != EEXIST))//Error in creating the FIFO
	{
		printf("Error in creating the FIFO.\n");
		return;
	}

	if(errno == EEXIST)
		printf("FIFO already exists. \n");
	
	printf("Waiting for output from FIFO1....\n\n");
	sleep(5);

	f1 = open("/tmp/Fifo1", O_RDONLY);//opening Fifo1 in Read mode	
	
	read(f1, ReadSentence, 100);
	
	int i = 0;
	for(i=0;ReadSentence[i] != '\0';i++)//Calculating No. of lines and Words
	{
		if((ReadSentence[i] == '.') || (ReadSentence[i] == '?'))
			NoLines++;
		if((ReadSentence[i] == ' ') || (ReadSentence[i] == ','))
			NoWords++;
	}

	NoCharacters = i-1;//Calculating no. of character

	fptr = fopen("file", "w");//opening "file" in Write mode	
	//printing no. of characters and words
	fprintf(fptr, "No. of Characters = %d\n", NoCharacters);
	fprintf(fptr, "No. of Words = %d\n", NoWords + 1);
	fprintf(fptr, "No. of Lines = %d\n", NoLines);
	fprintf(fptr, "%c", EOF);
	fclose(fptr);
	
	i = 0;

	fptr = fopen("file", "r");//opening "file" in Read mode

	while(fscanf(fptr, "%c", &Buffer[i++]) != EOF)
	Buffer[i] = '\0';

	fclose(fptr); 
	
	printf("Writing the output to FIFO2....\n\n");
	f2 = open("/tmp/Fifo2", O_WRONLY);//opening Fifo2 in Write mode
	write(f2, Buffer, (strlen(Buffer)+1));//writing output on fifo2

	sleep(5);
	unlink("/tmp/Fifo2");//unlinking fifo2
	return 0;
}

