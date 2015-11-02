#include "RRRTable.h"

uint32_t RRRTable::initialBlockLength = 0;

RRRTable& RRRTable::getInstance() {
	static RRRTable instance;
	return instance;
}

void RRRTable::createTable(uint32_t b) {
	if (RRRTable::initialBlockLength == 0) {
		RRRTable::initialBlockLength = b;
	}
	// when popcount equals 0
	vector<uint32_t> cumulativeZeroRank(b, 0);
	element_t elZero(0, cumulativeZeroRank);
	class_t subtableZero;
	subtableZero.push_back(elZero);
	this->table_.push_back(subtableZero);

	// for all other popcount values generate appropriate table elements
	for (int p = 1; p <= b; p++) {
		class_t subtable;
		uint32_t  v, initial;
		v = initial = firstElement(p);
		uint32_t block_mask = firstElement(b);

		while (v >= initial) {
			vector<uint32_t> cumulativeRank;
			uint32_t mask = 1 << (b - 1);
			//uint32_t mask = (uint32_t) pow(2, b - 1);
			uint32_t rankCounter = 0;

			while (mask) {
				if (v & mask) {
					rankCounter++;
				}
				cumulativeRank.push_back(rankCounter);
				mask /= 2;
			}
			element_t el(v, cumulativeRank);
			subtable.push_back(el);
			v = nextPermutation(v) & block_mask;
		}

		this->table_.push_back(subtable);
	}
}

uint32_t RRRTable::nextPermutation(uint32_t v) {
	uint32_t t = (v | (v - 1)) + 1;
	uint32_t w = t | ((((t & (~t+1)) / (v & (~v + 1))) >> 1) - 1);
	return w;
}

uint32_t RRRTable::firstElement(uint32_t c) {
	return (1 << c) - 1;
}

uint32_t RRRTable::getOffset(uint32_t classIndex, uint32_t block, uint32_t blockLength) {
	uint32_t blockOffset = initialBlockLength - blockLength;
	class_t cls = table_[classIndex];
	uint32_t upper = cls.size();
	uint32_t lower = 0;
	uint32_t middle = (upper + lower) / 2;

	block = (block << blockOffset);

	while (true) {
		uint32_t value = cls[middle].first;
		if (value < block) {
			lower = middle;
		}
		else if (value > block) {
			upper = middle;
		}
		else {
			return middle;
		}
		middle = (lower + upper) / 2;
	}
}

uint32_t RRRTable::getClassSize(uint32_t class_) {
	return table_[class_].size();
}