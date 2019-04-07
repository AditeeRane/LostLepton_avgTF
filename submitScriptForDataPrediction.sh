#!/bin/sh

#ArgOne=$1   # 
ArgTwo=$1   # 
ArgThree=$2 # 
ArgFour=$3  # 
ArgFive=$4  # 
ArgSix=$5  # 
ArgSeven=$6 #  

#
# first go to the submission dir, and set up the environment
#
#cd $ArgSeven 
#source /cvmfs/cms.cern.ch/cmsset_default.sh
#eval `scram runtime -sh`

#
# now go to the condor's scratch area, where we copied the contents of New_RA2b_2015
#
cd ${_CONDOR_SCRATCH_DIR} 
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc6_amd64_gcc530
eval `scramv1 project CMSSW CMSSW_10_2_11_patch1`
cd CMSSW_10_2_11_patch1/src/
eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers
echo "CMSSW: "$CMSSW_BASE
cd -  #goes back one directory; equivalent to cd ${_CONDOR_SCRATCH_DIR}
#mkdir -p TauHadMultiple
mkdir -p TauHad2Multiple
pwd
ls -l
#mkdir -p HadTauMultiple
#mkdir -p HadTau2Multiple

#
# run the job
#
echo $ArgOne $ArgTwo $ArgThree "." $ArgFive $ArgSix
#$ArgOne $ArgTwo $ArgThree "." $ArgFive $ArgSix
root -l -b -q 'MakePrediction_Data.C+("'$ArgTwo'","'$ArgThree'",".","'$ArgFive'","'$ArgSix'")'
