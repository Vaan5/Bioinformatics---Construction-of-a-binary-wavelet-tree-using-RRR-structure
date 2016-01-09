all:
	@echo "Generated tests.cpp"
	@bin/cxxtestgen --error-printer -o tests.cpp tests.h
	@echo "Compiling tests"
	@g++ -I /home/manager/Desktop/BioInf/LinuxUnitTest/ ../WaveletTree/WaveletTree/RRR.cpp ../WaveletTree/WaveletTree/RRRTable.cpp ../WaveletTree/WaveletTree/WaveletNode.cpp ../WaveletTree/WaveletTree/WaveletTree.cpp -o main tests.cpp -std=c++11
	@echo "Running tests"
	@./main
