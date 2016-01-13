all:
	@g++ -O2 WaveletTree/ConsoleApplication/main.cpp WaveletTree/WaveletTree/RRR.cpp WaveletTree/WaveletTree/RRRTable.cpp WaveletTree/WaveletTree/WaveletNode.cpp WaveletTree/WaveletTree/WaveletTree.cpp -o WaveletTreeBuild -std=c++11 -Wall
