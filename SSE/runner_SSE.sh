#!/bin/bash

jobname="prime_SSE"

taskList_1=(1)
## FIXME -- here is where one can supply the arguments like so primeLimits=(20)
primeLimits=(25)

## location to store SLURM files
rm -rf ALL_SLURMS
mkdir ALL_SLURMS ## store all the SLURMs created to this location

## TAKES args in following order -- $1=tasks_per_node $2=compute_partition
func()
{
directive="#!/bin/bash\n\n#SBATCH --partition=$2\n#SBATCH --nodes=1\n#SBATCH --ntasks-per-node=$1\n#SBATCH --job-name=$jobname\n#SBATCH --time=10:00:0\n#SBATCH --mail-user=rajaramr@buffalo.edu\n#SBATCH --output=Result_primeSSE_"$1"_%j.out\n#SBATCH --error=Result_primeSSE_error_"$1"_%j.out\n
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

sbatch_omp_xtra="ulimit -s unlimited\n./primeSSE \$1\n\n#\necho \"All Dones!\"\n"

### make a SPLURM file with config --- 8,12,16 processes and partition debug
for tasks in "${taskList_1[@]}"
do
   :
	func $tasks "general-compute" > SLURM_SSE_$tasks
	echo -e $sbatch_omp_xtra >> SLURM_SSE_$tasks

	for primes in "${primeLimits[@]}"
	do
	   :

	sbatch SLURM_SSE_$tasks $primes
	done	

	mv SLURM_SSE_$tasks ALL_SLURMS/
done
