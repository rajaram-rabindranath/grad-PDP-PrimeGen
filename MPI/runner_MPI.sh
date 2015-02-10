#!/bin/bash


if [ $# -eq 0 ]
then
	nodes=2
else
	nodes=$1
fi

echo "Number of nodes are" $nodes


## FIXME here is where one can set the number of processes /node like so --- taskList=(3 4 4)
taskList=(4)
## FIXME here is where one can set the limit for prime numbers like so --- primeLimits=(24)
primeLimits=(25)

job_name="prime_MPI"


rm -rf ALL_SLURMS
mkdir ALL_SLURMS ## store all the SLURMs created to this location

func()
{
directive="#!/bin/bash\n\n#SBATCH --partition=$2\n#SBATCH --nodes=$3\n#SBATCH --ntasks-per-node=$1\n#SBATCH --job-name=$job_name\n#SBATCH --time=00:50:00\n#SBATCH --mail-user=rajaramr@buffalo.edu\n#SBATCH --output=Result_MPI_"$1"_%j.out\n#SBATCH --error=Result_MPI_"$1"_%j.out\n
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

sbatch_omp_xtra="module load intel\nmodule load intel-mpi\nmodule list\nulimit -s unlimited\nexport I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so\nsrun ./primeMPI \$1\necho \"All Dones!\"\n"

### make a SPLURM file with config --- 8,12,16 processes and partition debug
for tasks in "${taskList[@]}"
do
   :

	func $tasks "general-compute" 2 > SLURM_OMP_$tasks
	echo -e $sbatch_omp_xtra >> SLURM_OMP_$tasks

	for primes in "${primeLimits[@]}"
	do
	   :

	sbatch SLURM_OMP_$tasks $primes
	done	

	mv SLURM_OMP_$tasks ALL_SLURMS/
done

### make slurm file with config --- 20,24,28,32
for tasks in "${taskList_2[@]}"
do
   :

	func $tasks "general-compute" $nodes > SLURM_OMP_$tasks
	echo -e $sbatch_omp_xtra >> SLURM_OMP_$tasks

	for primes in "${primeLimits[@]}"
	do
	   :
	sbatch SLURM_OMP_$tasks $primes
	done	

	mv SLURM_OMP_$tasks ALL_SLURMS/
done
