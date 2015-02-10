#!/bin/bash

jobname="prime_OMP"


### FIXME -- here is where one can set the number of processor (the count) like so taskList=(2 4) 
taskList=(2)
## FIXME -- here is where one can set the limit for the prime number searching like so primeLimits=(25)
primeLimits=(25)


rm -rf ALL_SLURMS
mkdir ALL_SLURMS ## store all the SLURMs created to this location

func()
{
directive="#!/bin/bash\n\n
#SBATCH --partition=$2\n#SBATCH --nodes=1\n#SBATCH --ntasks-per-node=$1\n#SBATCH --job-name=$jobname\n#SBATCH --time=10:00:00\n#SBATCH --mail-user=rajaramr@buffalo.edu\n#SBATCH --output=Result_primeOMP_"$1"_%j.out\n#SBATCH --error=Result_primeOMP_error_"$1"_%j.out\n
echo \"SLURM Enviroment Variables:\"\n
echo \"Job ID = \"\$SLURM_JOB_ID\n
echo \"Job Name = \"\$SLURM_JOB_NAME\n
echo \"Job Node List = \"\$SLURM_JOB_NODELIST\n
echo \"Number of Nodes = \"\$SLURM_NNODES\n
echo \"Tasks per Nodes = \"\$SLURM_NTASKS_PER_NODE\n
echo \"CPUs per task = \"\$SLURM_CPUS_PER_TASK\n
echo \"/scratch/jobid = \"\$SLURMTMPDIR\n
echo \"submit Host = \"\$SLURM_SUBMIT_HOST\n
echo \"Subimt Directory = \"\$SLURM_SUBMIT_DIR\n
echo \n"
echo -e $directive
}

sbatch_omp_xtra="ulimit -s unlimited\nmodule load intel\nmodule list\n\nNPROCS=\`srun --nodes=\${SLURM_NNODES} bash -c 'hostname' | wc -l\`\necho \"NPROCS=\"\$NPROCS\nexport OMP_NUM_THREADS=\$NPROCS\nexport | grep OMP\n
#\n\n./primeOMP \$1\n\n#\necho \"All Dones!\"\n"

### make a SPLURM file with config --- 8,12,16 processes and partition debug
for tasks in "${taskList[@]}"
do
   :

	func $tasks "general-compute" > SLURM_OMP_$tasks
	echo -e $sbatch_omp_xtra >> SLURM_OMP_$tasks

	for primes in "${primeLimits[@]}"
	do
	   :

	sbatch SLURM_OMP_$tasks $primes
	done	

	mv SLURM_OMP_$tasks ALL_SLURMS/
done
