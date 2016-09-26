#!/bin/bash 
#SBATCH -J raytracer
#SBATCH --mail-type=end
#SBATCH --mail-type=fail
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=16
#SBATCH --time=1:00:00
#SBATCH --mem=4000
#SBATCH --partition=debug
#SBATCH --mail-type=begin
#SBATCH --mail-user=gautier.manquat@epfl.ch

INFILE=

SCRATCH_TMP_FOLDER=/scratch/manquat/${SLURM_JOBID}.raytracer

./raytracer
joberror=$?

exit $joberror
