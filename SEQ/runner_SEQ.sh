#!/bin/bash

jobname="prime_seq"
### SET ARGUMENTS HERE --- the prime limits like this --- primeLimits=(20) below is an example
primeLimits=(20);

## location to store SLURM files
rm -rf ALL_SLURMS
mkdir ALL_SLURMS ## store all the SLURMs created to this location

func()
{
directive="#!/bin/bash\n\n#SBATCH --partition=$1\n#SBATCH --nodes=1\n#SBATCH --ntasks-per-node=1\n#SBATCH --job-name=$jobname\n#SBATCH --time=2:00:0\n#SBATCH --mail-user=rajaramr@buffalo.edu\n#SBATCH --output=Result_primeSEQ_%j.out\n#SBATCH --error=Result_primeSEQ_error_%j.out\n
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

sbatch_xtra="ulimit -s unlimited\n./primeSEQ \$1\n\n#\necho \"All Dones!\"\n"

### make a SPLURM file with config --- 8,12,16 processes and partition debug
func "general-compute" > SLURM_SEQ
echo -e $sbatch_xtra >> SLURM_SEQ

for primes in "${primeLimits[@]}"
do
   :

sbatch SLURM_SEQ $primes
done	

mv SLURM_SEQ ALL_SLURMS/

