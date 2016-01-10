#!/bin/bash

for i in $(ls Results/*.txt); do
	fileName="${i/Results\//}"
	echo "Checking $fileName"

	python diff.py $i "Tests/Results/$fileName" "Tests/Commands/$fileName"
done