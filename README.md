
FOLDER STRUCTURE:
MPI 	-- contains MPI code in "src" folder along with Makefile and a runner script.
OMP 	-- contains OpenMP code in "src" folder along with Makefile and a runner script.
SEQ 	-- contains Sequential code in "src" folder along with Makefile and a runner script.
SSE 	-- contains Intel intrinsic code in "src" folder along with Makefile and a runner script.
MPI+OMP -- contains MPI+OMP code in "src" folder along with Makefile and a runner script.


HOW - TO:

-- Please do load the following modules:

$ module load intel
$ module load intel-mpi

Inside each of the aforementioned folders is a runner script to submit the program 
in SBATCH and here are their names, what they do and how to run them.

------------------------------------------------ SEQ FOLDER ---------------------------------------------------
runner_SEQ.sh -- the runner script for Sequential code
e.g
	$ ./runner_SEQ.sh


The runner file has to be modified to change problem size as follows
(The things to be modified are right at the top of the file and have FIXME tags)

// to set the problem size fill the primeLimits array like so 
## FIXME here is where one can set the limit for prime numbers like so --- primeLimits=(24)
primeLimits=(25)


--- to run in non batch and to execute on local machine do the following:

	./primeSEQ <primeLimit> like so

 $ make
 $ ./primeSEQ 45


----------------------------------------------MPI------------------------------------------------------
runner_MPI.sh -- the runner script for MPI and requires an argument for Nodes
e.g

	$ ./runner_MPI.sh 4 // if no args are passes node count is defaulted to "2"

The runner file has to be modified to change problem size and the number of cores as follows
The things to be modified are right at the top of the file and have FIXME tags

// To set num cores fill the taskList array
## FIXME here is where one can set the number of processes /node like so --- taskList=(3 4 4)
taskList=(4)

// to set the problem size fill the primeLimits array like so 
## FIXME here is where one can set the limit for prime numbers like so --- primeLimits=(24)
primeLimits=(25)


--- to run in non batch and to execute local machine do the following:

	$ mpirun -n <nodes> ./primeMPI <primeLimit> like so

 $ make
 $ mpirun -n 4 ./primeMPI 45


------------------------------------------------OMP---------------------------------------------------
runner_OMP.sh -- the runner script for OMP

	$ ./runner_OMP.sh

The runner file has to be modified to change problem size and the number of cores as follows
The things to be modified are right at the top of the file and have FIXME tags

--- EXAMPLE
// To set num cores fill the taskList array
## FIXME here is where one can set the number of processes /node like so --- taskList=(3 4 4)
taskList=(4)

// to set the problem size fill the primeLimits array like so 
## FIXME here is where one can set the limit for prime numbers like so --- primeLimits=(24)
primeLimits=(25)



--- to run in non batch and to execute local machine do the following:

	./primeOMP -p <procs> -n <primeLimit> like so

 $ make
 $ ./primeOMP -p 2 -n 45
	(or)
 $ make
 $ ./primeOMP -n 45
	(or)
 $ make
 $ ./primeOMP 45

------------------------------------------------SEE---------------------------------------------------
runner_SSE.sh -- the runner script for Intel Intrinsic code

	$ ./runner_SEQ.sh

The runner file has to be modified to change problem size as follows
The things to be modified are right at the top of the file and have FIXME tags

// to set the problem size fill the primeLimits array like so 
## FIXME here is where one can set the limit for prime numbers like so --- primeLimits=(24)
primeLimits=(25)

--- to run in non batch and to execute local machine do the following:

	./primeSSE <primeLimit> like so

 $ make
 $ ./primeSSE 45
 
------------------------------------------------MPI+OMP---------------------------------------------------
runner_MPI_OMP.sh -- the runner script for MPI+OMP and requires an argument for Nodes 
e.g

	$ ./runner_MPI_OMP.sh 4 // if no args are passes nodes are defaulted to "2"

The runner file has to be modified to change problem size and the number of cores as follows
The things to be modified are right at the top of the file and have FIXME tags

// To set num cores fill the taskList array
## FIXME here is where one can set the number of processes /node like so --- taskList=(3 4 4)
taskList=(4)

// to set the problem size fill the primeLimits array like so 
## FIXME here is where one can set the limit for prime numbers like so --- primeLimits=(24)
primeLimits=(25)

--- to run in non batch and to execute local machine do the following:

	./primeMPI_OMP

 $ make
 $ mpirun -n 4 ./primeMPI_OMP 34
 
