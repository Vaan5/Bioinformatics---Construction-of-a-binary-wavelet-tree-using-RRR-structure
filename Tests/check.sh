#!/bin/bash

for i in $(ls Results/*.txt); do
	fileName="${i/Results\//}"
	# echo "Checking $fileName"

	python ../Scripts/diff.py $i "Tests/Results/$fileName" "Tests/Commands/$fileName"
done
