#include<stdio.h>
//#include<pthread.h>
#include<stdlib.h>

int matrixA[10][10],matrixB[10][10],matrixResult[10][10];
int colA,rowA,rowB,colB;

//Parameters to be passed while creation of POSIX thread
struct pthreadParameters{
        int rowCount;
        int colCount;
};


//Thread
void *multiply(void *a)
{
      struct pthreadParameters *p = a;
      int count;
      
       matrixResult[p->rowCount][p->colCount]=0;
      for(count=0; count < colA; count++)
      {
       
        matrixResult[p->rowCount][p->colCount] += matrixA[p->rowCount][count] * matrixB[count][p->colCount];
      }
    
  pthread_exit(0);
}
int main(int argc,char* argv[])
{
	int rowCount,colCount;
	int threadNumber = 0;
	
	//Checks for equality of rowA and columnB(TEST CASE)
	do
        {
                printf("Enter rows and columns of matrix A\n");
                scanf("%d %d",&rowA,&colA);
        
                printf("Enter rows and columns of matrix B\n");
                scanf("%d %d",&rowB,&colB);
                
                if(rowB != colA)
                {
                        printf("Number of rows of matrix B should be equal to number of columns of matrix A\n");
                }
        }while(rowB != colA);
        
        //Read elements of matrix A
        printf("Enter the elements of matrix A row-wise\n");
         for(rowCount = 0; rowCount < rowA; rowCount++)
        {
                for(colCount = 0; colCount < colA; colCount++)
                {
                	scanf("%d",&matrixA[rowCount][colCount]);
                }
               
        } 
      
      	//Display elements of matrix A
        printf("The elements of matrix A are\n");
        
         for(rowCount = 0; rowCount < rowA; rowCount++)
        {
                for(colCount = 0; colCount < colA; colCount++)
                {
                	printf("%d\t",matrixA[rowCount][colCount]);
                }
                printf("\n");
               
        } 
        
         //Read elements of matrix B
        printf("Enter the elements of matrix B row-wise\n");
         for(rowCount = 0; rowCount < rowB; rowCount++)
        {
                for(colCount = 0; colCount < colB; colCount++)
                {
                	scanf("%d",&matrixB[rowCount][colCount]);
                }
               
        } 
	
	//Display elements of matrix B
	printf("The elements of matrix B are\n");
        for(rowCount = 0; rowCount < rowB; rowCount++)
        {
                for(colCount = 0; colCount < colB; colCount++)
                {
                	printf("%d\t",matrixB[rowCount][colCount]);
                }
                printf("\n");
               
        } 
        
        //Loop for creating threads
        for(rowCount = 0; rowCount < rowA; rowCount++)
        {
        	for(colCount = 0; colCount < colB; colCount++)
        	{
        		//Memory Allocation to the parameters 
        		struct pthreadParameters *arguments = (struct pthreadParameters*)malloc(sizeof(struct pthreadParameters));
        		//Integer used to identify thread
        		pthread_t tid;
        		
        		//Declare default attributes
        		pthread_attr_t attr;
        		
        		//Initialize with default attributes
        		pthread_attr_init(&attr);
        		
        		arguments->rowCount = rowCount;
        		arguments->colCount = colCount;
        		
        		threadNumber++;
        		printf("Thread number %d created\n",threadNumber); 
        		
        		//Creation of pthread
        		//Argument 1 is pointer to id of the thread
        		//Argument 2 are the default attributes
        		//Argument 3 is the name of the function 
        		//Argument 4 is the arguments of the function 
        		pthread_create(&tid,&attr,multiply,arguments);
        		
        		//Blocks the calling thread until the called thread terminates
        		//tid is the thread id of the called function
      			pthread_join(tid,NULL);
        	}
        }
        
        //Display elements of result matrix 
        for(rowCount = 0; rowCount < rowB; rowCount++)
        {
                for(colCount = 0; colCount < colB; colCount++)
                {
                	printf("%d\t",matrixResult[rowCount][colCount]);
                }
               printf("\n");
        } 
}


/*
shruti@shruti-HP-Notebook:~/Documents$ gcc matrix.c -o mt -lpthread
matrix.c: In function ‘multiply’:
matrix.c:50:3: warning: implicit declaration of function ‘pthread_exit’ [-Wimplicit-function-declaration]
   pthread_exit(0);
   ^
matrix.c: In function ‘main’:
matrix.c:130:11: warning: implicit declaration of function ‘pthread_attr_init’ [-Wimplicit-function-declaration]
           pthread_attr_init(&attr);
           ^
matrix.c:143:11: warning: implicit declaration of function ‘pthread_create’ [-Wimplicit-function-declaration]
           pthread_create(&tid,&attr,multiply,arguments);
           ^
matrix.c:147:10: warning: implicit declaration of function ‘pthread_join’ [-Wimplicit-function-declaration]
          pthread_join(tid,NULL);
          ^
shruti@shruti-HP-Notebook:~/Documents$ ./mt
Enter rows and columns of matrix A
2
2
Enter rows and columns of matrix B
3
3
Number of rows of matrix B should be equal to number of columns of matrix A
Enter rows and columns of matrix A
2
2
Enter rows and columns of matrix B
2
2
Enter the elements of matrix A row-wise
1
1
1
1
The elements of matrix A are
1	1	
1	1	
Enter the elements of matrix B row-wise
1
1
1
1
The elements of matrix B are
1	1	
1	1	
Thread number 1 created
Thread number 2 created
Thread number 3 created
Thread number 4 created
2	2	
2	2	

*/
        
        
        
        
        
