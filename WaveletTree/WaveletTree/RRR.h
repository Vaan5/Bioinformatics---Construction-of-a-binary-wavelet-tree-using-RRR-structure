#pragma once
#include <string>
#include <vector>
#include "RRRTable.h"
#include <cmath>
#include <cstdint>

using namespace std;

class RRR {
private:
	vector<uint64_t> content;
	vector<pair<uint32_t, uint64_t> > superBlocks;
	unsigned int blockSize;
	unsigned int superBlockSize;
	unsigned int blocksPerSuperBlock;

	void addBlock(uint32_t class_, uint64_t offset_);
public:
	RRR(string &bits);
	uint64_t rank1(uint64_t index);
	uint64_t rank0(uint64_t index);
	uint64_t select1(uint64_t index);
	uint64_t select0(uint64_t index);
	int access(uint64_t index);
};