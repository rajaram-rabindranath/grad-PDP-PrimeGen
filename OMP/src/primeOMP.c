/*=============================================================================
* File Name: primGen.c
 * Project  : PDP Assignment 1
 * Version  : 0.1V
 * Author   : Rajaram Rabindranath (50097815)
 * Created  : November 30 2014
 ============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <appMacros.h>
#include <math.h>
#include <omp.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

/** function declarations **/
void printUsage(char* appName);
int parseArgs(int argc,char** argv, int*,int*);

void main(int argc, char** argv)
{

	// error handling
	if(argc ==1 || argc>ARGS_COUNT)
	{
		printUsage(argv[ARGS_APP_NAME]);
		return;
	}

	int th_id = 0;
	int primeLimit=0;
	int numProcs=0;
	clock_t tstart,tend;
	if(parseArgs(argc,argv,&numProcs,&primeLimit) == FAILURE)
	{
		printUsage(argv[ARGS_APP_NAME]);
		return;
	}

	if(DEBUG)
	{
		printf("procs %d primelimit %d\n",numProcs,primeLimit);
	}

	/**
	 *  OpenMP setup
	 *  --- set thread
	 *  --- workload allocation
	 **/
	if(numProcs != 0)
		omp_set_num_threads(numProcs);
	int largestPrime=0;
	//tstart = omp_get_wtime();
	struct timeval begin, end;
	gettimeofday(&begin, NULL);
	//tstart = clock();
	#pragma omp parallel private(th_id)
	{


		numProcs=omp_get_num_threads();
/*		int chunkSize=primeLimit/numProcs;
		int remainder=primeLimit%numProcs;


		int start= (th_id*chunkSize)+1;
		int end= (th_id+1 == numProcs) ? primeLimit:(th_id+1)*chunkSize;
		if(DEBUG)
		{
			printf("%d deals with %d to %d\n",th_id,start,end);
		}
*/
		th_id = omp_get_thread_num();
		int isPrime=TRUE;
		for(int i=(th_id+1)*2+1;i<=primeLimit;i+=(2*numProcs))
		{
			if(i%2==0) continue;
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
				//largestPrime=i;
				printf("%d\n",i);
			}
			isPrime=TRUE;
		}

#if DEBUG_OMP
		#pragma omp barrier
		if (th_id == 0)
		{
			printf("The number of threads is %d",omp_get_num_threads());
		}
#endif

	}

	gettimeofday(&end, NULL);
	double elapsed = (end.tv_sec - begin.tv_sec) + 
              ((end.tv_usec - begin.tv_usec)/1000000.0);

	//tend = clock();
	//printf("largest prime is %d\n",largestPrime);
	printf("%d :Time taken to find prime till %d using %d processors is %f seconds.\n",primeLimit+1,primeLimit,omp_get_num_procs(),elapsed);
	printf("%d :the threads count is %d\n",primeLimit+1,numProcs);
	return;
}



void printUsage(char* appName)
{
	printf("---------------- Wrong number of arguments ---------------\n");
	printf("%s <-p procs> -n prime_limit\n",appName);
	printf("\t(or)\n");
	printf("%s prime_limit\n",appName);
	printf("---------------- Wrong number of arguments ---------------\n");
}

int parseArgs(int argc,char** argv,int* numProcs,int* primeLimit)
{
	int index=1;
	if(!strcmp(argv[index],"-p"))
	{
		index++;
		if(index >= argc) return FAILURE;
		*numProcs = atoi(argv[index]);
		if(*numProcs == 0) return FAILURE;
		index++;

		if(index >= argc) return FAILURE;
		if(!strcmp(argv[index],"-n"))
		{
			index++;
			if(index >= argc) return FAILURE;
			*primeLimit=atoi(argv[index]);
		}
	}
	else if(!strcmp(argv[index],"-n"))
	{
		index++;
		if(index >= argc) return FAILURE;
		*primeLimit=atoi(argv[index]);
	}
	else
	{
		*primeLimit=atoi(argv[index]);
		if(*primeLimit == 0) return FAILURE;
	}
	return SUCCESS;
}
