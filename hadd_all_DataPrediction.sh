#! /bin/bash

#
# for prediction
#-----------------

cd TauHad2Multiple

for i in SingleElectron SingleMuon ; do 
    rm Prediction_0_Data_${i}_.root
    hadd Prediction_0_Data_${i}_.root `ls Prediction_0_Data_${i}_*00.root`
done

cd ..

