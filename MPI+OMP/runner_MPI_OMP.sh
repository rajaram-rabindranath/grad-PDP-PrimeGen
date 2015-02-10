#!/bin/bash


## By DEFAULT WILL RUN WITH 2 NODES
if [ $# -eq 0 ]
then
	echo "You need to pass the num of nodes, going ahead with defaul i.e 2 nodes"
	nodes=2
else
	nodes=$1
fi

echo "Number of nodes are" $nodes

## FIXME here is where one can set the number of tasks per node like so -- taskList(8)
taskList=(2)
## FIXME here is where one can se the limits of prime number searching like so -- primeLimits=(20)
primeLimits=(20)
job_name="OMP_MPI"


rm -rf ALL_SLURMS
mkdir ALL_SLURMS ## store all the SLURMs created to this location

func()
{
directive="#!/bin/bash\n\n#SBATCH --partition=$1\n#SBATCH --nodes=$2\n#SBATCH --ntasks-per-node=$3\n#SBATCH --job-name=$job_name\n#SBATCH --time=00:50:00\n#SBATCH --mail-user=rajaramr@buffalo.edu\n#SBATCH --output=Result_MPI_nodes"$2"_tasks"$3"_%j.out\n#SBATCH --error=Result_MPI_error_nodes"$2"_tasks"$3"_%j.out\n
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

sbatch_omp_xtra="module load intel\nmodule load intel-mpi\nmodule list\nulimit -s unlimited\nNPROCS=\`srun --nodes=\${SLURM_NNODES} bash -c 'hostname' | wc -l\`\necho \"NPROCS=\"\$NPROCS\nexport OMP_NUM_THREADS=\$NPROCS\nexport | grep OMP\nexport I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so\nsrun --cpu_bind=rank_ldom ./primeMPI_OMP \$1\necho \"All Dones!\"\n"

### make a SPLURM file with config --- 8,12,16 processes and partition debug
for tasks in "${taskList[@]}"
do
   :
	# cores partition nodes tasks_per_node mpi_tasks
	func "general-compute" $nodes $tasks > SLURM_MPI_OMP_$tasks
	echo -e $sbatch_omp_xtra >> SLURM_MPI_OMP_$tasks

	for primes in "${primeLimits[@]}"
	do
	   :

	# cores == tasks
	sbatch SLURM_MPI_OMP_$tasks $primes
	done	

	mv SLURM_MPI_OMP_$tasks ALL_SLURMS/
done
