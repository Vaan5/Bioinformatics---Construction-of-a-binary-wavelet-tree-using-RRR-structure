#include <iostream>
#include <string>
#include "..\WaveletTree\RRR.h"
#include "../WaveletTree/WaveletTree.h"
#include <cstdint>
#include <fstream>
#include <string>
#include <chrono>
#include <cstdint>
using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
	// check arguments
	if (argc > 4 || argc < 2) {
		fprintf(stderr, "Invalid number of arguments. Usage example: %s file [mode] [config]\n", argv[0]);
		fprintf(stderr, "file -> FASTA input file\n");
		fprintf(stderr, "mode -> i (interactive) | t (time analysis) | g (graphical display)\n");
		fprintf(stderr, "config -> TODO\n");
		exit(1);
	}

	char* inputFile = argv[1];
	string mode = "i";
	if (argc >= 3)
		mode = string(argv[2]);

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
	high_resolution_clock::time_point startTime = high_resolution_clock::now();
	WaveletTree tree(input);
	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(endTime - startTime).count();
	printf("Done building tree - %d ms\n", duration);

	if (mode == "i") {
		// interactive mode
		printf("Input lines in format: operation params\nParameters are delimited by space\nPossible formats are:\n\trank character index\n\tselect character count\n\taccess index\n");
		printf("Enter EXIT for application termination\n");
		while (true) {
			try {
				string operation;
				cin >> operation;
				if (operation == "rank") {
					uint64_t index;
					uint8_t character;
					cin >> character >> index;

					startTime = high_resolution_clock::now();
					cout << tree.rank(character, index) << endl;
					endTime = high_resolution_clock::now();
				}
				else if (operation == "select") {
					uint64_t count;
					uint8_t character;
					cin >> character >> count;

					startTime = high_resolution_clock::now();
					cout << tree.select(character, count) << endl;
					endTime = high_resolution_clock::now();
				}
				else if (operation == "access") {
					uint64_t index;
					cin >> index;

					startTime = high_resolution_clock::now();
					cout << (char)tree.access(index) << endl;
					endTime = high_resolution_clock::now();
				}
				else if (operation == "EXIT") {
					break;
				}
				else {
					printf("Invalid operation\n");
					continue;
				}
				duration = duration_cast<milliseconds>(endTime - startTime).count();
				printf("Elapsed time - %d ms\n", duration);
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
	}
	else if (mode == "g") {

	}
	else if (mode == "t") {

	}
	else {
		fprintf(stderr, "Invalid mode. Acceptable values: i (interactive) | t (time analysis) | g (graphical display)\n");
	}

	return 0;
}