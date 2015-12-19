#pragma once
#include "RRR.h"
#include <string>
#include <vector>
#include "common.h"
#include <cstdint>
#include <cstdlib>

class WaveletNode {
public:
	WaveletNode(string content_, WaveletNode *parent_, uint8_t start_, uint8_t end_, alphabet &alphabetIndices_, bool isLeftChild_, FILE* visualOutput = NULL);
	virtual ~WaveletNode();
	WaveletNode* getLeftChild() const;
	WaveletNode* getRightChild() const;
	WaveletNode* getParent() const;
	RRR* getContent() const;
	uint8_t getThreshold();
	bool getIsLeftChild();
	uint8_t getStart();
	uint8_t getEnd();

private:
	static int idGenerator;
	int id;
	WaveletNode *parent;
	WaveletNode *leftChild;
	WaveletNode *rightChild;
	uint8_t start;
	uint8_t end;
	uint8_t threshold;
	bool isLeftChild;
	RRR *content;
};