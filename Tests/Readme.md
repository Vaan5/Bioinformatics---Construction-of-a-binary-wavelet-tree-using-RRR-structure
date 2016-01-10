Inputs contains FASTA input files
Tests/Commands contains command sequences
Tests/Results contains desired outputs for each command
Results should contain output from WaveletTreeBuild (outputFile)
Measurements contains time statistics and memory usage for every test file

run.sh -> runs the WaveletTreeBuild for all files in Inputs and for the corresponding commands in Tests/Commands.
check.sh -> Runs Scripts/diff.py for all results in Results generated with the previous call