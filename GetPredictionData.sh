#!/bin/sh

sample=$1 # 0 control region, 1 signal region
outStr=$2

export SUBMIT_DIR=`pwd -P`

for DataStr in MET ; do
    export SubmitFile=submitScriptData_${DataStr}.jdl
    if [ -e ${SubmitFile} ]; then
	rm ${SubmitFile}
    fi
    
    let a=1
    Njobs=`ls InputFiles_Data/filelist_data_${DataStr}_${sample}_* | wc -l `
    #let njobs=Njobs - a
    njobs=`expr $Njobs - $a`

    echo number of jobs: $njobs
    mkdir -p qsub
    
    for i in `seq 0 $njobs`; do
	
	export filenum=$i
	export outStr=$outStr
	#echo $filenum
	#echo $code 
	export DataStr=$DataStr
	export Suffix=${DataStr}_${outStr}_$filenum
	if [ $filenum -lt 10 ]
	then
	    export ArgTwo=filelist_data_${DataStr}_${sample}_00$filenum
	    export ArgTwoB=InputFiles_Data/${ArgTwo}
	elif [ $filenum -lt 100 ]
	then
	    export ArgTwo=filelist_data_${DataStr}_${sample}_0$filenum
	    export ArgTwoB=InputFiles_Data/${ArgTwo}
	else
	    export ArgTwo=filelist_data_${DataStr}_${sample}_$filenum
	    export ArgTwoB=InputFiles_Data/${ArgTwo}
	fi
	export ArgThree=Data_${Suffix}
	export ArgFive=00
	export ArgSix=0
	export ArgSeven=$SUBMIT_DIR
	export Output=qsub/condor_${Suffix}.out
	export Error=qsub/condor_${Suffix}.err
	export Log=qsub/condor_${Suffix}.log
	export Proxy=\$ENV\(X509_USER_PROXY\)
	
	
	cd $SUBMIT_DIR
	source /cvmfs/cms.cern.ch/cmsset_default.sh
	eval `scram runtime -sh`
	#echo "ROOTSYS"  ${ROOTSYS}
	
	#
	# Prediction
	#
	    #echo $filenum
	    export ArgFour=TauHad2Multiple
#	    export ArgOne=MakeSFs.C    
	    #echo $ArgOne
	    #echo $ArgTwo
	    #echo $ArgThree
	    #echo $ArgFour
	    #echo $ArgFive
	    #echo $ArgSix
	    echo $Output
	    #echo $Error
	    #echo $Log
	    #echo $Proxy
	    export Output_root_file=Prediction_0_Data_${DataStr}_${outStr}_${i}_00.root
	    if [ -e TauHad2Multiple/${Output_root_file} ]; then
		echo warning !
		echo exist TauHad2Multiple/${Output_root_file}
	    else
		echo submitting TauHad2Multiple/${Output_root_file}
		
                #
                # Creating the submit .jdl file
                #
		if [ $i -eq 0 ]; then
		    echo executable = submitScriptForDataPrediction.sh>> ${SubmitFile}
		    echo universe =vanilla>> ${SubmitFile}
		    echo x509userproxy = ${Proxy}>> ${SubmitFile}
		    echo notification = never>> ${SubmitFile}
		    echo should_transfer_files = YES>> ${SubmitFile}
		    echo WhenToTransferOutput = ON_EXIT>> ${SubmitFile}
		fi
		
		echo "">> ${SubmitFile}
		echo Arguments =${ArgTwo} ${ArgThree} ${ArgFour} ${ArgFive} ${ArgSix} ${ArgSeven}>> ${SubmitFile} 
		echo Output = ${Output}>> ${SubmitFile}
		echo Error = ${Error}>> ${SubmitFile}
		echo Log = ${Log}>> ${SubmitFile}
		echo Transfer_Input_Files = Prediction.h,Prediction.C,MakePrediction_Data.C,TF.root,SearchBins.h,LLTools.h,${SUBMIT_DIR}/${ArgTwoB},${SUBMIT_DIR}/SFs_ICHEP16,${SUBMIT_DIR}/SFs_Moriond17,${SUBMIT_DIR}/btag,${SUBMIT_DIR}/pu,${SUBMIT_DIR}/isr>> ${SubmitFile}
		echo Transfer_Output_Files = Prediction_0_Data_${DataStr}_${outStr}_${i}_00.root>> ${SubmitFile}
		#echo Transfer_Output_Files = MuJetMatchRate_Data_${DataStr}_${outStr}_${i}_00.root>> ${SubmitFile}        
		echo transfer_output_remaps = '"'Prediction_0_Data_${DataStr}_${outStr}_${i}_00.root = TauHad2Multiple/Prediction_0_Data_${DataStr}_${outStr}_${i}_00.root'"'>> ${SubmitFile}
		
#		echo transfer_output_remaps = '"'MuJetMatchRate_Data_${DataStr}_${outStr}_${i}_00.root = TauHad2Multiple/MuJetMatchRate_Data_${DataStr}_${outStr}_${i}_00.root'"'>> ${SubmitFile}
		
		echo queue>> ${SubmitFile}	
		
	    fi # if [ -e TauHad2Multiple/${Output_root_file} ]; then
	    
	

	#
	# Expectation
	#
	
	#sleep 1
	
    done
    
    #
    # Actual submission
    # 
    condor_submit ${SubmitFile}
    
done

