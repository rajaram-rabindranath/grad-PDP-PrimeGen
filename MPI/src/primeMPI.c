/*
 * pimeMPI.c
 *
 *  Created on: Oct 2, 2014
 *      Author: dev
 */


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#define FAILURE 1
#define SUCCESS 0
#define ARGS_COUNT 2
#define ARGS_APP_NAME 0
#define ARGS_PRIME_LIMIT 1
#define TRUE 1
#define FALSE 0

void printUsage(char*);

int main(int argc,char** argv )
{
	int my_rank, size;
	int len;
	char procname[MPI_MAX_PROCESSOR_NAME];

	/** start MPI code **/
	MPI_Init( &argc, &argv );
	
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &my_rank );
	MPI_Get_processor_name(procname,&len);

	int largestPrime=0;
	// error handling
	if(argc != ARGS_COUNT)
	{
		if(my_rank==0)
			printUsage(argv[ARGS_APP_NAME]);
		MPI_Finalize();
		return FAILURE;
	}

	double Tstart, Tend;
	int primeLimit=atoi (argv[ARGS_PRIME_LIMIT]);
	/*int chunkSize=primeLimit/size;

	int start= (my_rank*chunkSize)+1;
	int end= (my_rank+1 == size) ? primeLimit:(my_rank+1)*chunkSize;
	int isPrime=TRUE;
*/	/** gen prime numbers **/
//	if(start%2==0)start++;
	int isPrime=TRUE;
	struct timeval begin, end;
	
	MPI_Barrier(MPI_COMM_WORLD);
	if(my_rank ==0)
	{
		Tstart=MPI_Wtime();
		gettimeofday(&begin, NULL);
	}


	for(int i=(my_rank+1)*2+1;i<=primeLimit;i+=2*size)
	{
		for(int j=3;j<=sqrt(i);j+=2)
		{
			if(i%j==0)
			{
				isPrime=FALSE;
				break;
			}
		}
		if(isPrime)
		{
			//largestPrime =i;
			printf("%d\n",i);
		}
		isPrime=TRUE;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(my_rank==0)
	{
		Tend=MPI_Wtime();
		gettimeofday(&end, NULL);	
		
		double elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
		
		printf("%d Time taken using getTimeofday %f seconds\n",primeLimit+1,elapsed);
		printf("%d Time taken to compute primes till %d is %f seconds\n",primeLimit+1,primeLimit,Tend-Tstart);
                printf("%d Time taken to compute primes till %d with %d procs is %f seconds\n",primeLimit+1,primeLimit,size,Tend-Tstart);
	}
	//printf("i am %d and largest prime %d\n",my_rank,largestPrime);
	
	MPI_Finalize();
	return SUCCESS;
}


void printUsage(char* appName)
{
	printf("---------------- Wrong number of arguments ---------------\n");
	printf("%s prime_limit\n",appName);
	printf("---------------- Wrong number of arguments ---------------\n");
}
