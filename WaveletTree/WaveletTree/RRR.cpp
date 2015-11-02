#include "RRR.h"

RRR::RRR(string &bits) {
	// number of bits in input string
	uint64_t n = bits.size();
	if (n > 3) {
		// bit number in each block
		this->blockSize = floor(log2(bits.size())) / 2;
	}
	else {
		this->blockSize = 1;
	}

	// bit number in super blocks
	this->superBlockSize = pow(floor(log2(n)), 2.);
	this->blocksPerSuperBlock = this->superBlockSize / this->blockSize;

	// initialize table
	RRRTable::getInstance();
	if (RRRTable::initialBlockLength == 0) {
		RRRTable::getInstance().createTable(blockSize);
	}

	uint32_t blockContent = 0;
	uint64_t currentBitInContent = 1 << 63;
	uint64_t currentContentElement = 0;
	uint64_t currentIndex = 0;
	uint64_t alignValue = 0;
	//vector<bool> blockContent(this->blockSize);
	uint64_t blockRank = 0;
	for (int i = 0; i < n; i++) {
		blockContent = (blockContent << 1);

		if (bits[i] == '1') {
			blockContent = (blockContent | 1);
			blockRank++;
		}

		if (i != 0 && ((i+1) % this->blockSize) == 0) {
			uint32_t blockOffset = RRRTable::getInstance().getOffset(blockRank, blockContent, blockSize);
			uint32_t classSize = RRRTable::getInstance().getClassSize(blockRank);
			uint32_t bitsForOffset = ceil(log2(classSize));
			uint32_t bitsForClass = ceil(log2(blockSize));

			uint64_t blockRankCopy = blockRank << (64 - bitsForClass - alignValue);
			for (int k = 0; k < bitsForClass; k++) {
				currentContentElement = currentContentElement | (currentBitInContent & blockRankCopy);
				currentBitInContent = currentBitInContent >> 1;
				alignValue++;
				currentIndex++;
				if (currentBitInContent == 0) {
					// i need to add another uint64_t into the content vector
					content.push_back(currentContentElement);
					currentContentElement = 0;
					currentBitInContent = 1 << 63;
					alignValue = 0;
					blockRankCopy = blockRank << (64 - bitsForClass + k + 1);
				}
			}

			uint64_t blockOffsetCopy = blockOffset << (64 - bitsForOffset - alignValue);
			for (int k = 0; k < bitsForOffset; k++) {
				currentContentElement = currentContentElement | (currentBitInContent & blockOffsetCopy);
				currentBitInContent = currentBitInContent >> 1;
				alignValue++;
				currentIndex++;
				if (currentBitInContent == 0) {
					// i need to add another uint64_t into the content vector
					content.push_back(currentContentElement);
					currentContentElement = 0;
					currentBitInContent = 1 << 63;
					alignValue = 0;
					blockOffsetCopy = blockOffset << (64 - bitsForOffset + k + 1);
				}
			}
			

			/// TU SMO STALI - DODATI ZA SUPERBLOKOVE
			

			blockRank = 0;
			blockContent = 0;
		}
	}
}