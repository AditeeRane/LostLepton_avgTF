#!/bin/sh

type=$1 # 0 control region, 1 signal region
outStr=$2

export SUBMIT_DIR=`pwd -P`

for ExStr in ZZZ ZZTo2L2Q WZZ WZTo1L3Nu WZTo1L1Nu2Q WWZ WWTo2L2Nu WWTo1L1Nu2Q TTZToQQ TTZToLLNuNu TTWJetsToQQ TTWJetsToLNu TTTT TTGJets ; do

    export SubmitFile=submitScriptExotic_${ExStr}.jdl
    if [ -e ${SubmitFile} ]; then
	rm ${SubmitFile}
    fi
    let a=1
    Njobs=`ls InputFiles_Exotic/filelist_Spring15_Exotic_${ExStr}_* | wc -l `
    #let njobs=Njobs - a
    njobs=`expr $Njobs - $a`

    echo number of jobs: $njobs
    mkdir -p qsub
    
    for i in `seq 0 $njobs`; do
	
	export filenum=$i
	export outStr=$outStr
	#echo $filenum
	#echo $code 
	export ExStr=$ExStr
	export Suffix=${ExStr}_${outStr}_$filenum
	if [ $filenum -lt 10 ]
	then
	    export ArgTwo=filelist_Spring15_Exotic_${ExStr}_00$filenum
	    export ArgTwoB=InputFiles_Exotic/${ArgTwo}
	elif [ $filenum -lt 100 ]
	then
	    export ArgTwo=filelist_Spring15_Exotic_${ExStr}_0$filenum
	    export ArgTwoB=InputFiles_Exotic/${ArgTwo}
	else
	    export ArgTwo=filelist_Spring15_Exotic_${ExStr}_$filenum
	    export ArgTwoB=InputFiles_Exotic/${ArgTwo}
	fi
	export ArgThree=Exotic_${Suffix}
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
	    echo $Output
	    if [ $type -eq 0 ]; then    
		export Output_root_file=TF_0_Exotic_${ExStr}_${outStr}_${i}_00.root
	    fi
	    if [ -e TauHad2Multiple/${Output_root_file} ]; then
		echo warning !
		echo exist TauHad2Multiple/${Output_root_file}
	    else
		echo submitting TauHad2Multiple/${Output_root_file}
		
                #
                # Creating the submit .jdl file
                #
		if [ $i -eq 0 ]; then
		    echo executable = submitScriptForTF.sh>> ${SubmitFile}
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
		echo Transfer_Input_Files = MakeTF.C,TFMaker.h,TFMaker.C,SFSR_0.root,SFCR_0.root,SFSR_1.root,SFCR_1.root,SFSR_2.root,SFCR_2.root,SFSR_3.root,SFCR_3.root,SearchBins.h,LLTools.h,${SUBMIT_DIR}/${ArgTwoB},${SUBMIT_DIR}/SFs_ICHEP16,${SUBMIT_DIR}/SFs_Moriond17,${SUBMIT_DIR}/btag,${SUBMIT_DIR}/pu,${SUBMIT_DIR}/isr>> ${SubmitFile}
		if [ $type -eq 0 ]; then    
		    echo Transfer_Output_Files = TF_0_Exotic_${ExStr}_${outStr}_${i}_00.root>> ${SubmitFile}
		    echo transfer_output_remaps = '"'TF_0_Exotic_${ExStr}_${outStr}_${i}_00.root = TauHad2Multiple/TF_0_Exotic_${ExStr}_${outStr}_${i}_00.root'"'>> ${SubmitFile}
		fi
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

