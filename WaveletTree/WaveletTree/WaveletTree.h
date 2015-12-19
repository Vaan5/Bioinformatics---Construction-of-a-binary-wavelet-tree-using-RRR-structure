#pragma once

#include "RRR.h"
#include "RRRTable.h"
#include <string>
#include <vector>
#include <cstdint>
#include "WaveletNode.h"
#include "common.h"

using namespace std;

class WaveletTree {
private:
	alphabet alphabetIndices;
	inverseAlphabet alphabetCharacters;
	WaveletNode* root;
	uint8_t alphabetSize;

public:
	WaveletNode* getRoot() const;
	WaveletTree(string input, FILE* visualOutput = NULL);
	virtual ~WaveletTree();
	uint64_t rank(uint8_t character, uint64_t index);
	uint64_t select(uint8_t character, uint64_t count);
	uint8_t access(uint64_t index);

};