#pragma once

#include "RRR.h"
#include "RRRTable.h"
#include <string>
#include <vector>
#include <cstdint>
#include "WaveletNode.h"
#include "common.h"
#include <stdexcept>

using namespace std;

class WaveletTree {
private:
	alphabet alphabetIndices;
	WaveletNode* root;
	uint8_t alphabetSize;

public:
	WaveletNode* getRoot() const;
	WaveletTree(string input);
	virtual ~WaveletTree();
	uint64_t rank(uint8_t character, uint64_t index);

};