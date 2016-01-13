#                                       Bioinformatics project
                            Construction of binary wavelet trees using RRR structure
                            
Library for the creation of binary wavelet trees based on RRR structure, created as part of the project assignment for Bioinformatics course (http://www.fer.unizg.hr/predmet/bio) on University of Zagreb, Faculty of Electrical Engineering and Computing (UNIZG FER) , academic year 2015/2016..

#Authors
- Denis Čaušević
- Hajrudin Ćoralić

#Instructions (Linux)
- Clone git repo

#Run instructions
- Go into cloned root folder
- make
- ./WaveletTreeBuild fastaFile [gt] [outputFile] [ < commands]
		fastaFile -> FASTA input file
		g -> graphical display
		t -> time statistics
		outputFile -> file in which operation output is being written
		commands -> file containing test operations
	Example usage:
		./WaveletTreeBuild WaveletTree/ConsoleApplication/Pig.txt


#Unit test instructions
- Go into LinuxUnitTest
- make			(this will build and run all unit tests)

#Instructions (Windows)
- Clone git repo

#Run instructions
- Go into Wavelet tree folder
- Open WaveletTree.sln
- Set Release x64 build definition in Visual Studio
- Go to x64/Release folder
- Run program from command line in the same way as for linux (last bullet) except the executable file is named ConsoleApplication.exe

#Unit test instructions
- Go into Wavelet tree folder
- Open WaveletTree.sln
- Set Debug x64 build definition in Visual Studio
- Set test environment to x64 in Visual Studio
- Run tests using Test Explorer

#FASTA input files
- WaveletTree/ConsoleApplication/Pig.txt
- WaveletTree/ConsoleApplication/Camelpox.txt
- WaveletTree/ConsoleApplication/HIV.txt
- WaveletTree/ConsoleApplication/HajroDenis.txt
- Tests/Inputs/*

This git repo contains only small test files.
All test files are located (here) [http://1drv.ms/1JKOceX]
(including larger ones not uploaded to git repo).

All test files must have UNIX line ending ("\n")

Tests/Tests/Commands contains command sequences
Tests/Tests/Results contains desired outputs for each command
Tests/Results should contain output from WaveletTreeBuild (outputFile)
