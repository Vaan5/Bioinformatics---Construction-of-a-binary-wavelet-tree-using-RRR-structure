#!/bin/bash

COUNTER=100
INTERVAL=8
while [  $COUNTER -le 100000000 ]; do
	echo $COUNTER
	python testFileGenerator.py 65 68 $COUNTER ../Tests/Inputs/65_68_$COUNTER.txt && python testCommandGenerator.py $INTERVAL ../Tests/Inputs/65_68_$COUNTER.txt ../Tests/Tests/Commands/65_68_$COUNTER.txt ../Tests/Tests/Results/65_68_$COUNTER.txt
	python testFileGenerator.py 65 80 $COUNTER ../Tests/Inputs/65_80_$COUNTER.txt && python testCommandGenerator.py $INTERVAL ../Tests/Inputs/65_80_$COUNTER.txt ../Tests/Tests/Commands/65_80_$COUNTER.txt ../Tests/Tests/Results/65_80_$COUNTER.txt
	python testFileGenerator.py 65 92 $COUNTER ../Tests/Inputs/65_92_$COUNTER.txt && python testCommandGenerator.py $INTERVAL ../Tests/Inputs/65_92_$COUNTER.txt ../Tests/Tests/Commands/65_92_$COUNTER.txt ../Tests/Tests/Results/65_92_$COUNTER.txt

	let COUNTER=COUNTER*10
	let INTERVAL=INTERVAL*2
done