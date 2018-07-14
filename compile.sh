#!/bin/bash

g++ -o src/pharmacy_counting src/pharmacy_counting.cpp src/drug_data.cpp

if [ ! -d "./bin" ]; then
	mkdir bin
fi

cp src/pharmacy_counting bin/pharmacy_counting
