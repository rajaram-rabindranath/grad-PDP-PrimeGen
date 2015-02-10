/*=============================================================================
* File Name : primSSE.c
 * Project  : PDP Assignment 1
 * Version  : 0.1V
 * Author   : Rajaram Rabindranath (50097815)
 * Created  : October 6 2014
 ============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <emmintrin.h>
#include <time.h>
#include <sys/time.h>

#define ARGS_PRIME_LIMIT 1
#define FALSE 0
#define TRUE 1
#define USE_DIV
#define SUCCESS 0
#define FAILURE 1
#define ARGS_COUNT 2
#define APP_NAME 0

/** template **/
void printUsage(char* appName);

void main(int argc, char** argv)
{
	if(argc != ARGS_COUNT)
	{
		printUsage(argv[APP_NAME]);
		return;
	}
	int isPrime=TRUE; // a number is a candidate prime until proven otherwise
	int primeLimit=0;
	primeLimit=atoi(argv[ARGS_PRIME_LIMIT]);

	if(primeLimit==0)
	{
		printf("Please enter a valid number for primeLimit\n");
		return;
	}
	double candidate;

	/** time the run **/
	struct timeval begin, end;
	double elapsed;
	__m128d candidatePrime;
	__m128d recognizerPrime;
	// 8,388,608 is the max limit of float so can't go beyond that
	double* a = _mm_malloc(2*sizeof(double), 64);
	gettimeofday(&begin, NULL); // timing

	for(int i=3;i<=primeLimit;i+=2)
	{
		candidatePrime = _mm_set_pd((double)i,(double)i);
		for(int j=3;j<=sqrt(i);j+=2)
		{
			recognizerPrime = _mm_set_pd((double)j+2,(double)j);
			j+=2;
			__m128d jim = _mm_div_pd(candidatePrime,recognizerPrime);
			_mm_store_pd(a,jim);
			if(a[0] ==floor(a[0]) || a[1] == floor(a[1]))
			{
				isPrime=FALSE;
				break;
			}
			
		}
		if(isPrime)
		{
			printf("%d\n",i);
		}
		isPrime=TRUE;
	}
	gettimeofday(&end, NULL);
elapsed = (end.tv_sec - begin.tv_sec) + 
              ((end.tv_usec - begin.tv_usec)/1000000.0);
	printf("%d Total time taken in secs to find all primes till %d is %f\n",primeLimit+1,primeLimit,elapsed);
}

void printUsage(char* appName)
{
	printf("---------------- Wrong number of arguments ---------------\n");
	printf("%s <primeLimit> \n",appName);
	printf("---------------- Wrong number of arguments ---------------\n");
}
