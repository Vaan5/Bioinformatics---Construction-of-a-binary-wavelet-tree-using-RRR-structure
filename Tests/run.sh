#!/bin/bash

for i in $(ls Inputs/*.txt); do
	fileName="${i/Inputs\//}"
	echo "Running $fileName"

	.././WaveletTreeBuild $i t "Results/$fileName" < "Tests/Commands/$fileName" > "Measurements/$fileName"
done