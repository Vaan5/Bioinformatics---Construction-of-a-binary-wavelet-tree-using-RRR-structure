#pragma once
#include "RRR.h"
#include <string>
#include <vector>
#include "WaveletTree.h"
#include <cstdint>
#include <cstdlib>

class WaveletNode {
public:
	WaveletNode(string content_, WaveletNode *parent_, uint8_t start_, uint8_t end_, alphabet &alphabetIndices_);
	virtual ~WaveletNode();
private:
	WaveletNode *parent;
	WaveletNode *leftChild;
	WaveletNode *rightChild;
	uint8_t start;
	uint8_t end;
	RRR *content;
};