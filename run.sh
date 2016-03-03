#!/bin/bash

rm -rf result_mcc.txt
rm -rf results_tasa.txt
for ((i=0;i<=54;i++)); do
	./Scheduling $i 0 > res.txt
	length_mcc=`cat res.txt | grep "SF" | awk '{print $3}'`
	channel_mcc=`cat res.txt | grep "CH" | awk '{print $3}'`
	time_mcc=
	rm -rf res.txt
	echo $i $length_mcc $channel_mcc $time_mcc >> result_mcc.txt

	./Scheduling $i 1 > res.txt
	length_tasa=`cat res.txt | grep "SF" | awk '{print $3}'`
	channel_tasa=`cat res.txt | grep "CH" | awk '{print $3}'`
	time_tasa=
	rm -rf res.txt
	echo $i $length_tasa $channel_tasa $time_tasa >> result_tasa.txt
done
