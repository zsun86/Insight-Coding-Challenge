#!/bin/bash
#
# Use this shell script to compile (if necessary) your code and then execute it. Below is an example of what might be found in this file if your program was written in Python
#
#python ./src/pharmacy_counting.py ./input/itcont.txt ./output/top_cost_drug.txt

#g++ -o src/pharmacy_counting src/pharmacy_counting.cpp src/drug_data.cpp
g++ -o src/pharmacy_counting src/pharmacy_counting.cpp src/drug_data.cpp

if [ ! -d "./bin" ]; then
	mkdir bin
fi

cp src/pharmacy_counting bin/pharmacy_counting


bin/pharmacy_counting input/itcont.txt output/top_cost_drug.txt

#bin/pharmacy_counting input/de_cc_data.txt output/de_cc_drug_cost.txt