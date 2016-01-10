#include <iostream>
#include <string>
#include "../WaveletTree/RRR.h"
#include "../WaveletTree/WaveletTree.h"
#include <cstdint>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstring>
#ifdef __linux__ 
	#include "stdlib.h"
	#include "stdio.h"
#else
	#include "windows.h"
	#include "psapi.h"
#endif

using namespace std;
using namespace std::chrono;

// Graphviz configuration loader
string getConfigValue(string key) {
	ifstream inputStream("config.txt");
	string line;
	while (getline(inputStream, line)) {
		if (line.find(key) == 0) {
			int ind = line.find("=");
			return line.substr(ind + 1);
		}
	}
	return "";
}

// Print average times
void printAverageTime(vector<uint64_t> &times, string operationName) {
	uint64_t sum = 0;
	for (unsigned int i = 0; i < times.size(); i++) {
		sum += times[i];
	}

	if (times.size() > 0) {
		uint64_t averageSum = sum / times.size();
		printf("Average %s time for %lu queries: %lu ms (%lu us)\n", operationName.c_str(), times.size(), averageSum / 1000, averageSum);
	}
}

// Used for parsing proces memory files in bio linux
int parseLine(char* line) {
	int i = strlen(line);
	while (*line < '0' || *line > '9') line++;
	line[i-3] = '\0';
	i = atoi(line);
	return i;
}

// Print memory usage
double getAndPrintMemoryUsage(double startMemory) {
	double currentMemory = 0;
	#ifdef __linux__ 
		FILE* file = fopen("/proc/self/status", "r");
		int result = -1;
		char line[128];
	

		while (fgets(line, 128, file) != NULL){
			if (strncmp(line, "VmRSS:", 6) == 0){
				result = parseLine(line);
				break;
			}
		}
		fclose(file);
		currentMemory = result / 1024.;
	#else
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		currentMemory = physMemUsedByMe / (1024. * 1024);
	#endif
	if (startMemory > 0) {
		cout << "Current memory usage: " << currentMemory << " MB" << endl;
		cout << "Actual memory usage: " << currentMemory - startMemory << " MB" << endl;
	}
	else {
		cout << "Memory before wavelet tree construction: " << currentMemory << " MB" << endl;
	}
	return currentMemory;
}

// Open graphviz generated image using configured image viewer
void openImage(char* fileName) {
	char buff[500] = { 0 };
	char pngName[500] = { 0 };
	strcpy(pngName, fileName);
	pngName[strlen(pngName) - 2] = 0;
	strcat(pngName, "png");
	#ifdef __linux__ 
		sprintf(buff, "\"%s\" -Tpng \"%s\" -o \"%s\"", getConfigValue("DOT_PATH").c_str(), fileName, pngName);
	#else
		sprintf(buff, "\"\"%s\" -Tpng \"%s\" -o \"%s\"\"", getConfigValue("DOT_PATH").c_str(), fileName, pngName);
	#endif
	system(buff);
	buff[0] = 0;
	string imgViewer = getConfigValue("IMAGE_VIEWER");
	if (imgViewer.length() == 0) {
		#ifdef __linux__ 
			sprintf(buff, "%s", pngName);
		#else
			sprintf(buff, "\"%s\"", pngName);
		#endif
	}
	else {
		#ifdef __linux__ 
			sprintf(buff, "\"%s\" \"%s\"", imgViewer.c_str(), pngName);
		#else
			sprintf(buff, "\"\"%s\" \"%s\"\"", imgViewer.c_str(), pngName);
		#endif
	}
	system(buff);
}

int main(int argc, char** argv) {
	// check arguments
	if (argc > 4 || argc < 2) {
		fprintf(stderr, "Invalid number of arguments. Usage example: %s file [gt] [outputFile] [ < commands]\n", argv[0]);
		fprintf(stderr, "file -> FASTA input file\n");
		fprintf(stderr, "g -> graphical display\n");
		fprintf(stderr, "t -> time statistics\n");
		fprintf(stderr, "outputFile -> file in which operation output is being written\n");
		fprintf(stderr, "commands -> file containing test operations\n");
		exit(1);
	}

	char* inputFile = argv[1];
	bool graphicsMode = false;
	bool timeMode = false;
	if (argc >= 3) {
		string s = string(argv[2]);
		if (s.find("g") < s.length()) graphicsMode = true;
		if (s.find("t") < s.length()) timeMode = true;
	}

	// open file in which operation outputs will be written
	ofstream out;
	if (argc == 4) {
		out.open(argv[3]);
	}

	// Load FASTA file
	printf("Loading file %s\n", inputFile);

	// Get number of bytes to allocate string memory
	FILE *handler = fopen(inputFile, "r");
	if (handler == NULL) {
		fprintf(stderr, "Couldn't open file %s\n", inputFile);
		exit(1);
	}
	fseek(handler, 0, SEEK_END);
	long size = ftell(handler);
	fclose(handler);

	// Read data
	ifstream inputStream(inputFile, ios::in);
	string line;
	char* buffer = new char[size];
	int index = 0;
	while (getline(inputStream, line)) {
		if (line[0] == '>' || line[0] == ';' || line.empty())
			continue;
		
		// Read line
		memcpy(buffer + index, line.c_str(), line.length());
		index += line.length();
	}
	buffer[index] = '\0';
	string input(buffer);

	// Deallocate buffer used for string construction
	delete[] buffer;
	printf("File loaded\n");

	printf("Building Wavelet tree\n");
	
	FILE *visualOutput = NULL;
	char fileName[200] = { 0 };
	if (graphicsMode) {
		sprintf(fileName, "graph.gv");
		visualOutput = fopen(fileName, "w");
	}

	double startMemory = getAndPrintMemoryUsage(0);

	high_resolution_clock::time_point startTime = high_resolution_clock::now();
	WaveletTree tree(input, visualOutput);
	high_resolution_clock::time_point endTime = high_resolution_clock::now();

	getAndPrintMemoryUsage(startMemory);

	auto duration = duration_cast<milliseconds>(endTime - startTime).count();
	printf("Done building tree - %ld ms\n", duration);

	vector<uint64_t> accessTimes;
	vector<uint64_t> rankTimes;
	vector<uint64_t> selectTimes;
	vector<uint64_t>* currentTimeVector;

	if (graphicsMode) {
		openImage(fileName);
	}

	// Interactive mode
	printf("Input lines in format: operation params\nParameters are delimited by space\nPossible formats are:\n\trank character index\n\tselect character count\n\taccess index\n");
	printf("Enter EXIT for application termination\n");
	printf("Enter STAT for time statistics\n");
	printf("Enter MEM for application memory usage\n");
	while (true) {
		try {
			string inputLine;
			getline(cin, inputLine);
			int firstSpaceIndex = inputLine.find(" ");
			int lastSpaceIndex = inputLine.rfind(" ");
			string operation = inputLine.substr(0, firstSpaceIndex);

			if (operation == "rank") {
				currentTimeVector = &rankTimes;
				uint64_t index;
				uint8_t character;
				character = inputLine.substr(firstSpaceIndex + 1, lastSpaceIndex)[0];
				istringstream bufferStream(inputLine.substr(lastSpaceIndex + 1));
				bufferStream >> index;

				uint64_t result;
				startTime = high_resolution_clock::now();
				result = tree.rank(character, index);
				endTime = high_resolution_clock::now();
				if (argc == 4)
					out << result << endl;
				else
					cout << result << endl;
			}
			else if (operation == "select") {
				currentTimeVector = &selectTimes;
				uint64_t count;
				uint8_t character;
				character = inputLine.substr(firstSpaceIndex + 1, lastSpaceIndex)[0];
				istringstream bufferStream(inputLine.substr(lastSpaceIndex + 1));
				bufferStream >> count;

				uint64_t result;
				startTime = high_resolution_clock::now();
				result = tree.select(character, count);
				endTime = high_resolution_clock::now();
				if (argc == 4)
					out << result << endl;
				else
					cout << result << endl;
			}
			else if (operation == "access") {
				currentTimeVector = &accessTimes;
				uint64_t index;
				istringstream bufferStream(inputLine.substr(firstSpaceIndex + 1));
				bufferStream >> index;

				uint8_t result;
				startTime = high_resolution_clock::now();
				result = tree.access(index);
				endTime = high_resolution_clock::now();
				if (argc == 4)
					out << (char)result << endl;
				else
					cout << (char)result << endl;
			}
			else if (operation == "EXIT") {
				break;
			}
			else if (operation == "MEM") {
				getAndPrintMemoryUsage(startMemory);
				continue;
			}
			else if (operation == "STAT") {
				printAverageTime(rankTimes, "rank");
				printAverageTime(selectTimes, "select");
				printAverageTime(accessTimes, "access");
				continue;
			}
			else {
				printf("Invalid operation\n");
				continue;
			}

			duration = duration_cast<microseconds>(endTime - startTime).count();
			(*currentTimeVector).push_back(duration);
			if (!timeMode) {
				printf("Elapsed time - %ld ms (%ld us)\n", duration / 1000, duration);
			}
		}
		catch (invalid_argument& e) {
			cout << e.what() << endl;
		}
		catch (const runtime_error& e) {
			cout << e.what() << endl;
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}

	getAndPrintMemoryUsage(startMemory);
	return 0;
}
