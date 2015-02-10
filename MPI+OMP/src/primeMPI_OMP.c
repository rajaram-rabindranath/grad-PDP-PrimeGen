/*
 * pimeMPI.c
 *
 *  Created on: Oct 2, 2014
 *      Author: Rajaram Rabindranath
 */


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

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
	MPI_Init(&argc, &argv );

	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &my_rank );
	MPI_Get_processor_name(procname,&len);


	// error handling
	if(argc != ARGS_COUNT)
	{
		if(my_rank==0)
			printUsage(argv[ARGS_APP_NAME]);
		MPI_Finalize();
		return FAILURE;
	}


	int primeLimit=atoi (argv[ARGS_PRIME_LIMIT]);
	double Tstart, Tend;
	int isPrime=TRUE;
	/** gen prime numbers **/
	int th_id=0;
	int np=0;
	MPI_Barrier(MPI_COMM_WORLD);
	if(my_rank==0)
	{
		Tstart = MPI_Wtime();
	}

//omp_set_num_threads(5);
	//printf(omp_get_num_procs());
	#pragma omp parallel private(th_id)
	{
		
		np = omp_get_num_threads();
		th_id = omp_get_thread_num();
		//printf("num threads %d\n",np);
		/*for(int i=(1+(iam+1)*2);i<35;i=i+(2*np))
		{	

		    printf("%d out of %d from omp_threasd %d out of %d fro index %d\n",rank,numprocs,iam,np,i);
		}*/
		int i=(my_rank+1)*2+1;
//printf("Thread id is %d from rank %d\n",th_id,my_rank);
		for(i+=th_id*(2*size);i<=primeLimit;i+=(2*size*np))
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
				//printf("%d : %d =%d\n",my_rank,th_id,i);
				printf("%d\n",i);
			}
			isPrime=TRUE;
		}

	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(my_rank==0)
	{
		Tend=MPI_Wtime();
		printf("%d Time taken to compute primes till %d using %d processes with %d procs on each is %f seconds\n",primeLimit+1,primeLimit,size,np,Tend-Tstart);
	}

	MPI_Finalize();
	return SUCCESS;


}
void printUsage(char* appName)
{
	printf("---------------- Wrong number of arguments ---------------\n");
	printf("%s <-p procs> -n prime_limit\n",appName);
	printf("\t(or)\n");
	printf("%s prime_limit\n",appName);
	printf("---------------- Wrong number of arguments ---------------\n");
}
