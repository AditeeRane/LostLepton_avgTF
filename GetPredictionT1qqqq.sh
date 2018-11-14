#!/bin/sh

type=$1 # 0 control region, 1 signal region
outStr=$2

export SUBMIT_DIR=`pwd -P`
export SubmitFile=submitScriptT1qqqqSignal.jdl

if [ -e ${SubmitFile} ]; then
    rm ${SubmitFile}
fi

let a=-1
i=`expr $a + 1`


for m in 600 650 700 750 800 850 900 950 1000 1050 1100 1150 1200 1250 1300 1350 1400 1450 1500 1550 1600 1650 1700 1750 1800 1850 1900 1950 2000 2050 2100 2150 2200 2250 2300; do

#for m in 600; do
    
#    for d in 1; do
    for d in 1 100 200 300 400 500 550 575 600 625 650 675 700 725 750 775 800 825 850 875 900 925 950 975 1000 1025 1050 1075 1100 1125 1150 1175 1200 1225 1250 1275 1300 1325 1350 1375 1400 1425 1450 1475 1500 1525 1550 1575 1600; do 
	
	
 	if [ "$d" -gt "$m" ] ; then
	    break
	fi
	
	mkdir -p qsub
	
	export filename=RA2bin_T1qqqq_${m}_${d}_fast 
	export ArgTwo=$filename
	export ArgTwoB=InputFiles_Signal/${filename} #input file
	
	if [ -e $ArgTwoB ]; then
	    i=`expr $i + 1`
	    echo $i    
	    
#	    export skmFile=tree_T1qqqq_${m}_${d}_fast.root
#	    export btagOne=CSVv2_ichep.csv
#	    export btagOneB=btag/${btagOne}    
#	    export btagTwo=CSV_13TEV_Combined_14_7_2016.csv
#	    export btagTwoB=btag/${btagTwo}
	    export motherM=${m}
	    export lspM=${d}
	    export outStr=$outStr
	    export Suffix=${filename}_${outStr}
	    export ArgThree=$Suffix
	    echo $filename
	    export ArgFive=00
	    export ArgSix=0
	    export ArgSeven=$SUBMIT_DIR
	    export Output=qsub/condor_T1qqqq_${m}_${d}.out
	    export Error=qsub/condor_T1qqqq_${m}_${d}.err
	    export Log=qsub/condor_T1qqqq_${m}_${d}.log
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
	    if [ $type -eq 0 ]; then    
		export Output_root_file=Prediction_0_${filename}_${outStr}_00.root
	    fi
	    if [ -e TauHad2Multiple/${Output_root_file} ]; then
		echo warning !
		echo exist TauHad2Multiple/${Output_root_file}
	    else
		echo submitting TauHad2Multiple/${Output_root_file}
		
                #
                # Creating the submit .jdl file
                #
		if [ $i -eq 1 ]; then
		    echo executable = submitScriptForSignalPrediction.sh>> ${SubmitFile}
		    echo universe =vanilla>> ${SubmitFile}
		    echo x509userproxy = ${Proxy}>> ${SubmitFile}
		    echo notification = never>> ${SubmitFile}
		    echo should_transfer_files = YES>> ${SubmitFile}
		    echo WhenToTransferOutput = ON_EXIT>> ${SubmitFile}
		fi
		
		echo "">> ${SubmitFile}
		echo Arguments =${ArgTwo} ${ArgThree} ${ArgFour} ${ArgFive} ${ArgSix} ${ArgSeven} >> ${SubmitFile} 
		echo Output = ${Output}>> ${SubmitFile}
		echo Error = ${Error}>> ${SubmitFile}
		echo Log = ${Log}>> ${SubmitFile}
		echo Transfer_Input_Files = Prediction.h,Prediction.C,MakePrediction_Signal.C,TF.root,SearchBins.h,LLTools.h,${SUBMIT_DIR}/${ArgTwoB},${SUBMIT_DIR}/SFs_ICHEP16,${SUBMIT_DIR}/SFs_Moriond17,${SUBMIT_DIR}/btag,${SUBMIT_DIR}/pu,${SUBMIT_DIR}/isr,${SUBMIT_DIR}/xsec>> ${SubmitFile}
		if [ $type -eq 0 ]; then    
		    echo Transfer_Output_Files = Prediction_0_${filename}_${outStr}_00.root>> ${SubmitFile}
		#echo Transfer_Output_Files = MuJetMatchRate_TTbar_${TTbarStr}_${outStr}_${i}_00.root>> ${SubmitFile}        
		    echo transfer_output_remaps = '"'Prediction_0_${filename}_${outStr}_00.root = TauHad2Multiple/Prediction_0_${filename}_${outStr}_00.root'"'>> ${SubmitFile}
		fi
		
#		echo transfer_output_remaps = '"'MuJetMatchRate_TTbar_${TTbarStr}_${outStr}_${i}_00.root = TauHad2Multiple/MuJetMatchRate_TTbar_${TTbarStr}_${outStr}_${i}_00.root'"'>> ${SubmitFile}
		
		echo queue>> ${SubmitFile}	
		
	    fi # if [ -e TauHad2Multiple/${Output_root_file} ]; then
	    
	else
	    continue
	fi	    
	
	#
	# Expectation
	#
	
	#sleep 1
	
    done
done

    #
    # Actual submission
    # 
condor_submit ${SubmitFile}

