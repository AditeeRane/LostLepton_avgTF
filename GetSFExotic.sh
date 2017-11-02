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
	export ArgFour=TauHad2Multiple
	echo $Output
	if [ $type -eq 0 ]; then    
	    export Output_root_file=SFCR_0_Exotic_${ExStr}_${outStr}_${i}_00.root
	fi
	if [ $type -eq 1 ]; then    
	    export Output_root_file=SFSR_0_Exotic_${ExStr}_${outStr}_${i}_00.root
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
		    echo executable = submitScriptForSF.sh>> ${SubmitFile}
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
		echo Transfer_Input_Files = MakeSFs.C,SFMaker.h,SFMaker.C,SearchBins.h,LLTools.h,${SUBMIT_DIR}/${ArgTwoB},${SUBMIT_DIR}/SFs_ICHEP16,${SUBMIT_DIR}/SFs_Moriond17,${SUBMIT_DIR}/btag,${SUBMIT_DIR}/pu,${SUBMIT_DIR}/isr>> ${SubmitFile}
		if [ $type -eq 0 ]; then    
		    echo Transfer_Output_Files = SFCR_0_Exotic_${ExStr}_${outStr}_${i}_00.root>> ${SubmitFile}
		    echo transfer_output_remaps = '"'SFCR_0_Exotic_${ExStr}_${outStr}_${i}_00.root = TauHad2Multiple/SFCR_0_Exotic_${ExStr}_${outStr}_${i}_00.root'"'>> ${SubmitFile}
		fi
		if [ $type -eq 1 ]; then    
		    echo Transfer_Output_Files = SFSR_0_Exotic_${ExStr}_${outStr}_${i}_00.root>> ${SubmitFile}
		    echo transfer_output_remaps = '"'SFSR_0_Exotic_${ExStr}_${outStr}_${i}_00.root = TauHad2Multiple/SFSR_0_Exotic_${ExStr}_${outStr}_${i}_00.root'"'>> ${SubmitFile}
		fi
		echo queue>> ${SubmitFile}	
		
	    fi
    done
    
    #
    # Actual submission
    # 
    condor_submit ${SubmitFile}
    
done

