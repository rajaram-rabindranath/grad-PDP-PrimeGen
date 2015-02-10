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
#include <time.h>
#include <sys/time.h>

void main(int argc, char** argv)
{
	if(argc != ARGS_COUNT)
	{
		printf("ERROR: Wrong number of arguments furnished\n");
		return;
	}

	if(DEBUG)
	{
		printf("arg count, %d",argc);
		printf("arg 1 ,%s",argv[ARGS_APP_NAME]);
		printf("arg 2 ,%s",argv[ARGS_PRIME_UPPER_LIMIT]);
	}

	/** time the run **/
	//clock_t begin, end;

	/** make a mem pool to hold prime numbers **/
	int primeLimit = atoi(argv[ARGS_PRIME_UPPER_LIMIT]);
	int* primeNums = NULL;
	int primesCnt = primeLimit/2 < 3 ? 3:primeLimit/2;
	primeNums= (int*) calloc(primesCnt,sizeof(int));

	/** we already know that 1,2,3 are prime numbers **/
	primeNums[0]=1;
	primeNums[1]=2;
	primeNums[2]=3;

	int addPrimeAt=3;
	int isPrime=TRUE; // a number is a candidate prime until proven otherwise
	struct timeval begin, end;
	gettimeofday(&begin, NULL);

	//begin = clock(); // timing starts
	for(int i=3;i<=primeLimit;i+=2)
	{
		for(int j=3;j<=sqrt(i);j+=2)
		{
			//if(j >= primesCnt || primeNums[j] == 0) break;
			if(i%j==0)
			{
				isPrime=FALSE;
				break;
			}
		}
		if(isPrime)
		{
			printf("%d\n",i);
			//primeNums[addPrimeAt] = i;
			//addPrimeAt++;
		}
		isPrime=TRUE;

	}

gettimeofday(&end, NULL);
double elapsed = (end.tv_sec - begin.tv_sec) + 
              ((end.tv_usec - begin.tv_usec)/1000000.0);

	//end = clock(); // timing ends
	printf("Total time taken in secs to find all primes till %d is %f\n",primeLimit,elapsed); //(double)(end - begin) / CLOCKS_PER_SEC);
}

