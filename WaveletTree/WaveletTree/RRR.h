#pragma once
#include <string>
#include <vector>
#include "RRRTable.h"
#include <cmath>
#include <cstdint>
#include <algorithm>

typedef pair<uint64_t, uint64_t> superBlock;

using namespace std;

class RRR {
private:
	vector<uint64_t> content;
	vector<superBlock> superBlocks;
	uint32_t blockSize;
	uint32_t superBlockSize;
	uint32_t blocksPerSuperBlock;
	uint32_t bitsForClass;

	void addBlock(uint32_t class_, uint64_t offset_);
	static bool compareSuperBlock(superBlock a, superBlock b);
	bool compareSuperBlockZeroes(superBlock a, superBlock b);
public:
	RRR(string &bits);
	uint64_t rank1(uint64_t index);
	uint64_t rank0(uint64_t index);
	uint64_t select1(uint64_t count);
	uint64_t select0(uint64_t count);
	uint16_t access(uint64_t index);
};