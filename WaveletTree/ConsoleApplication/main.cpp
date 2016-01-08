#include <iostream>
#include <string>
#include "..\WaveletTree\RRR.h"
#include "../WaveletTree/WaveletTree.h"
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
#include <cstring>
#include "windows.h"
#include "psapi.h"

using namespace std;
using namespace std::chrono;

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

void printAverageTime(vector<uint64_t> &times, string operationName) {
	uint64_t sum = 0;
	for (int i = 0; i < times.size(); i++) {
		sum += times[i];
	}

	if (times.size() > 0) {
		uint64_t averageSum = sum / times.size();
		printf("Average %s time for %d queries: %d ms (%d us)\n", operationName.c_str(), times.size(), averageSum / 1000, averageSum);
	}
}

void printMemoryUsage() {
	PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	cout << "Memory usage: " << physMemUsedByMe / (1024.*1024) << " MB" << endl;
}

void openImage(char* fileName) {
	char buff[500] = { 0 };
	char pngName[500] = { 0 };
	strcpy(pngName, fileName);
	pngName[strlen(pngName) - 2] = 0;
	strcat(pngName, "png");
	sprintf(buff, "\"\"%s\" -Tpng \"%s\" > \"%s\"\"", getConfigValue("DOT_PATH").c_str(), fileName, pngName);
	system(buff);
	buff[0] = 0;
	string imgViewer = getConfigValue("IMAGE_VIEWER");
	if (imgViewer.length() == 0) {
		sprintf(buff, "\"%s\"", pngName);
	}
	else {
		sprintf(buff, "\"\"%s\" \"%s\"\"", imgViewer.c_str(), fileName, pngName);
	}
	system(buff);
}

int main(int argc, char** argv) {
	// check arguments
	if (argc > 4 || argc < 2) {
		fprintf(stderr, "Invalid number of arguments. Usage example: %s file [gt] [ < config]\n", argv[0]);
		fprintf(stderr, "file -> FASTA input file\n");
		fprintf(stderr, "g -> graphical display\n");
		fprintf(stderr, "t -> time statistics\n");
		fprintf(stderr, "config -> file containing test operations\n");
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

	// load FASTA file
	printf("Loading file %s\n", inputFile);

	// get number of bytes to allocate string memory
	FILE *handler = fopen(inputFile, "r");
	if (handler == NULL) {
		fprintf(stderr, "Couldn't open file %s\n", inputFile);
		exit(1);
	}
	fseek(handler, 0, SEEK_END);   // non-portable
	long size = ftell(handler);
	fclose(handler);

	ifstream inputStream(inputFile, ios::in);
	string line;
	char* buffer = new char[size];
	int index = 0;
	while (getline(inputStream, line)) {
		if (line[0] == '>' || line[0] == ';' || line.empty())
			continue;
		
		// read line
		memcpy(buffer + index, line.c_str(), line.length());
		index += line.length();
	}
	buffer[index] = '\0';
	string input(buffer);

	// deallocate buffer used for string construction
	delete[] buffer;
	printf("File loaded\n");

	printf("Building Wavelet tree\n");
	
	FILE *visualOutput = NULL;
	char fileName[200] = { 0 };
	if (graphicsMode) {
		time_t result = time(nullptr);
		sprintf(fileName, "graph%d.gv", localtime(&result));
		visualOutput = fopen(fileName, "w");
	}

	high_resolution_clock::time_point startTime = high_resolution_clock::now();
	WaveletTree tree(input, visualOutput);
	high_resolution_clock::time_point endTime = high_resolution_clock::now();

	printMemoryUsage();

	auto duration = duration_cast<milliseconds>(endTime - startTime).count();
	printf("Done building tree - %d ms\n", duration);

	vector<uint64_t> accessTimes;
	vector<uint64_t> rankTimes;
	vector<uint64_t> selectTimes;
	vector<uint64_t>* currentTimeVector;

	if (graphicsMode) {
		openImage(fileName);
	}

	// interactive mode
	printf("Input lines in format: operation params\nParameters are delimited by space\nPossible formats are:\n\trank character index\n\tselect character count\n\taccess index\n");
	printf("Enter EXIT for application termination\n");
	while (true) {
		try {
			string inputLine;
			getline(cin, inputLine);
			int firstSpaceIndex = inputLine.find(" ");
			int lastSpaceIndex = inputLine.rfind(" ");
			string operation = inputLine.substr(0, firstSpaceIndex);
			// cin >> operation;
			if (operation == "rank") {
				currentTimeVector = &rankTimes;
				uint64_t index;
				uint8_t character;
				character = inputLine.substr(firstSpaceIndex + 1, lastSpaceIndex)[0];
				istringstream bufferStream(inputLine.substr(lastSpaceIndex + 1));
				bufferStream >> index;
				//cin >> character >> index;

				startTime = high_resolution_clock::now();
				cout << tree.rank(character, index) << endl;
				endTime = high_resolution_clock::now();
			}
			else if (operation == "select") {
				currentTimeVector = &selectTimes;
				uint64_t count;
				uint8_t character;
				character = inputLine.substr(firstSpaceIndex + 1, lastSpaceIndex)[0];
				istringstream bufferStream(inputLine.substr(lastSpaceIndex + 1));
				bufferStream >> count;
				//cin >> character >> count;

				startTime = high_resolution_clock::now();
				cout << tree.select(character, count) << endl;
				endTime = high_resolution_clock::now();
			}
			else if (operation == "access") {
				currentTimeVector = &accessTimes;
				uint64_t index;
				istringstream bufferStream(inputLine.substr(firstSpaceIndex + 1));
				bufferStream >> index;
				//cin >> index;

				startTime = high_resolution_clock::now();
				cout << (char)tree.access(index) << endl;
				endTime = high_resolution_clock::now();
			}
			else if (operation == "EXIT") {
				break;
			}
			else if (operation == "MEM") {
				printMemoryUsage();
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
				printf("Elapsed time - %d ms (%d us)\n", duration / 1000, duration);
			}
		}
		catch (invalid_argument& e) {
			printf("%s\n", e.what());
		}
		catch (const runtime_error& error)
		{
			cout << error.what() << endl;
		}
		catch (exception& e) {
			printf("Exception: %s\n", e.what());
		}
	}

	printMemoryUsage();
	return 0;
}