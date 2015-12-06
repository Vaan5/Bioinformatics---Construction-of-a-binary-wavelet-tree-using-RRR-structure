#include "RRR.h"

RRR::RRR(string &bits) {
	// number of bits in input string
	uint64_t n = bits.size();
	this->inputVectorLength = n;
	if (n > 3) {
		// bit number in each block
		this->blockSize = (uint32_t)(floor(log2(bits.size())) / 2);
	}
	else {
		this->blockSize = 1;
	}
	this->bitsForClass = (uint32_t)ceil(log2(this->blockSize + 1));
	this->bitsForClass = this->bitsForClass == 0 ? 1 : this->bitsForClass;

	// bit number in super blocks
	this->superBlockSize = (uint32_t)(pow(floor(log2(n)), 2.));
	if (this->superBlockSize == 0)
	{
		this->superBlockSize = 1;
	}
	this->blocksPerSuperBlock = this->superBlockSize / this->blockSize;

	// initialize table
	RRRTable::getInstance();
	if (RRRTable::initialBlockLength == 0) {
		RRRTable::getInstance().createTable(this->blockSize);
	}

	uint64_t blockContent = 0;
	uint64_t currentBitInContent = ((uint64_t)1) << 63;
	uint64_t currentContentElement = 0;
	//uint64_t currentIndex = 0;
	uint64_t alignValue = 0;

	uint64_t blockRank = 0;
	uint64_t superBlockRank = 0;

	superBlock superBlock(0, 0);
	uint64_t blockIndex = 0;
	uint64_t superBlockOffset = 0;

	this->maxIndexInLastContentElement = 0;

	for (uint64_t i = 0; i < n; i++) {
		blockContent = (blockContent << 1);

		if (bits[(unsigned int)i] == '1') {
			blockContent = (blockContent | 1);
			blockRank++;
		}

		if ((i != 0 && ((i + 1) % this->blockSize) == 0) || (i + 1 == this->blockSize) || (i + 1 == n)) {
			blockIndex++;
			uint32_t currentBlockSize = this->blockSize;
			if (i + 1 == n && ((i + 1) % this->blockSize)) {
				blockContent = blockContent << (this->blockSize - ((i + 1) % this->blockSize));
			}
			// blockSize used for bits alignment for table search
			uint32_t blockOffset = RRRTable::getInstance().getOffset((uint32_t)blockRank, (uint32_t)blockContent, this->blockSize);
			uint32_t bitsForOffset = RRRTable::getInstance().getBitsForOffset(blockRank);

			superBlockOffset += (bitsForOffset + this->bitsForClass);

			uint64_t blockRankCopy = blockRank << (64 - this->bitsForClass - alignValue);
			for (uint32_t k = 0; k < this->bitsForClass; k++) {
				currentContentElement = currentContentElement | (currentBitInContent & blockRankCopy);
				currentBitInContent = currentBitInContent >> 1;
				this->maxIndexInLastContentElement++;
				alignValue++;
				//currentIndex++;
				if (currentBitInContent == 0) {
					// i need to add another uint64_t into the content vector
					content.push_back(currentContentElement);
					currentContentElement = 0;
					currentBitInContent = ((uint64_t)1) << 63;
					alignValue = 0;
					int overFlowBits = this->bitsForClass - k - 1;
					if (overFlowBits > 0) {
						blockRankCopy = blockRank << (64 - overFlowBits);
						currentContentElement = currentContentElement | (currentBitInContent & blockRankCopy);
						currentBitInContent = currentBitInContent >> 1;
						//this->maxIndexInLastContentElement++;
						alignValue++;
						k++;
					}
					//blockRankCopy = blockRank << (64 - this->bitsForClass + k + 1);
					//currentContentElement = currentContentElement | (currentBitInContent & blockRankCopy);
					//currentBitInContent = currentBitInContent >> 1;
					////this->maxIndexInLastContentElement++;
					//alignValue++;
					//k++;
				}
			}

			uint64_t blockOffsetCopy = ((uint64_t)blockOffset) << (64 - bitsForOffset - alignValue);
			for (uint32_t k = 0; k < bitsForOffset; k++) {
				currentContentElement = currentContentElement | (currentBitInContent & blockOffsetCopy);
				currentBitInContent = currentBitInContent >> 1;
				this->maxIndexInLastContentElement++;
				alignValue++;
				//currentIndex++;
				if (currentBitInContent == 0 || (i + 1) == n) {
					// i need to add another uint64_t into the content vector
					content.push_back(currentContentElement);
					currentContentElement = 0;
					currentBitInContent = ((uint64_t)1) << 63;
					alignValue = 0;
					int overflowExtraBits = bitsForOffset - k - 1;
					if (overflowExtraBits > 0) {
						blockOffsetCopy = blockOffset << (64 - overflowExtraBits);
						currentContentElement = currentContentElement | (currentBitInContent & blockOffsetCopy);
						currentBitInContent = currentBitInContent >> 1;
						//this->maxIndexInLastContentElement++;
						alignValue++;
						k++;
					}
					//blockOffsetCopy = blockOffset << (64 - bitsForOffset + k + 1);
					//currentContentElement = currentContentElement | (currentBitInContent & blockOffsetCopy);
					//currentBitInContent = currentBitInContent >> 1;
					////this->maxIndexInLastContentElement++;
					//alignValue++;
					//k++;
				}
			}

			superBlockRank += blockRank;
			if ((blockIndex % this->blocksPerSuperBlock == 0) || (i + 1 == n)) {
				superBlocks.push_back(superBlock);

				superBlock.second = superBlockOffset;
				superBlock.first = superBlockRank;
			}

			blockRank = 0;
			blockContent = 0;
		}
	}

	this->maxIndexInLastContentElement = this->maxIndexInLastContentElement % 64;
}

uint64_t RRR::getInputVectorLength() const
{
	return this->inputVectorLength;
}

uint64_t RRR::rank1(uint64_t index) {
	// index checks
	if (index >= this->inputVectorLength)
	{
		throw invalid_argument("RRR > Rank index too large");
	}

	// calculate block index
	uint64_t ib = index / this->blockSize;

	// calculate which superblock the ib-th block resides in
	uint32_t is = (uint32_t) (ib / this->blocksPerSuperBlock);

	// set rankSum to the rank contained in the current superblock
	uint64_t rankSum = this->superBlocks[is].first;

	// used to know in which block we current are in order to add the current block rank to the rankSum
	uint64_t currentBlockIndex = this->blocksPerSuperBlock * is;
	uint64_t currentIndex = this->superBlocks[is].second;
	uint64_t contentIndex = currentIndex / 64;
	uint64_t currentIndexInContentElement = currentIndex % 64;
	uint64_t currentContentElement = this->content[(uint32_t)contentIndex];
	uint64_t mask = (((uint64_t)1) << this->bitsForClass) - 1;

	//currentIndexInContentElement - this->bitsForClass < 0

	// sum up block ranks up to the ib-th block
	while (currentBlockIndex <= ib) {
		uint64_t tempRank = currentContentElement >> (64 - this->bitsForClass - currentIndexInContentElement);
		uint64_t leftOverBits = currentIndexInContentElement + this->bitsForClass;
		if (leftOverBits >= 64) {
			// we have overflow
			contentIndex++;
			currentContentElement = this->content[(uint32_t)contentIndex];
			currentIndexInContentElement = leftOverBits % 64;
			if (currentIndexInContentElement > 0) {
				uint64_t tempMask = UINT64_MAX ^ (((uint64_t)1 << currentIndexInContentElement) - 1);
				tempRank = tempRank & tempMask | (currentContentElement >> (64 - currentIndexInContentElement));
			}
			/*uint64_t tempMask = UINT64_MAX ^ (((uint64_t)1 << currentIndexInContentElement) - 1);
			tempRank = tempRank & tempMask | (currentContentElement >> (64 - currentIndexInContentElement));*/
		}
		else {
			currentIndexInContentElement += this->bitsForClass;
		}
		tempRank = tempRank & mask;
		if (currentBlockIndex != ib) {
			rankSum += tempRank;
		}

		uint32_t bitsForOffset = RRRTable::getInstance().getBitsForOffset(tempRank);
		if (currentBlockIndex != ib) {
			currentIndexInContentElement += bitsForOffset;
			if (currentIndexInContentElement >= 64) {
				// we have overflow
				contentIndex++;
				currentContentElement = this->content[(uint32_t)contentIndex];
				currentIndexInContentElement = currentIndexInContentElement % 64;
			}
		}
		else {
			uint64_t maskForOffset = (((uint64_t)1) << bitsForOffset) - 1;
			uint64_t tempOffset = currentContentElement >> (64 - bitsForOffset - currentIndexInContentElement);
			leftOverBits = currentIndexInContentElement + bitsForOffset;
			if (leftOverBits >= 64) {
				// we have overflow
				contentIndex++;
				currentContentElement = this->content[(uint32_t)contentIndex];
				currentIndexInContentElement = leftOverBits % 64;
				if (currentIndexInContentElement > 0) {
					uint64_t tempMask = UINT64_MAX ^ (((uint64_t)1 << currentIndexInContentElement) - 1);
					tempOffset = tempOffset & tempMask | (currentContentElement >> (64 - currentIndexInContentElement));
				}
			}

			tempOffset = tempOffset & maskForOffset;
			// We are in the ib-th block; read the appropriate rank from RRRTable
			uint64_t j = index % ((uint64_t)this->blockSize);
			rankSum += RRRTable::getInstance().getRankForBlockAtPosition(tempRank, tempOffset, (uint32_t)j);
			// get out of while loop
		}
		currentBlockIndex++;
	}
	return rankSum;
}

uint64_t RRR::rank0(uint64_t index) {
	return index + 1 - this->rank1(index);
}

uint64_t RRR::select1(uint64_t count) {
	if (count > this->inputVectorLength)
	{
		throw invalid_argument("RRR > Select count value too large");
	}
	if(count == 0)
	{
		throw invalid_argument("RRR > Select count value must be positive");
	}

	superBlock countBlock(count, 36);
	vector<superBlock>::iterator supBlockIterator = lower_bound(this->superBlocks.begin(), this->superBlocks.end(), countBlock, RRR::compareSuperBlock);
	superBlock supBlock = *(--supBlockIterator);
	uint64_t superBlockIndex = supBlockIterator - this->superBlocks.begin();

	// set rankSum to the rank contained in the current superblock
	uint64_t rankSum = supBlock.first;

	// used to know in which block we current are in order to add the current block rank to the rankSum
	uint64_t currentBlockIndex = 0;
	uint64_t currentIndex = supBlock.second;
	uint64_t contentIndex = currentIndex / 64;
	uint64_t currentIndexInContentElement = currentIndex % 64;
	uint64_t currentContentElement = this->content[(uint32_t)contentIndex];
	uint64_t mask = (((uint64_t)1) << this->bitsForClass) - 1;

	// add the index of the first element in found superblock
	uint64_t indexOfith1 = this->blocksPerSuperBlock * this->blockSize * superBlockIndex;

	// sum up block ranks up to the ib-th block
	uint64_t lastContentIndex = this->content.size() - 1;
	while (rankSum < count && (contentIndex < lastContentIndex || (contentIndex == lastContentIndex && currentIndexInContentElement < this->maxIndexInLastContentElement))) {
		uint64_t tempRank = currentContentElement >> (64 - this->bitsForClass - currentIndexInContentElement);
		uint64_t leftOverBits = currentIndexInContentElement + this->bitsForClass;
		if (leftOverBits >= 64) {
			// we have overflow
			contentIndex++;
			currentContentElement = this->content[(uint32_t)contentIndex];
			currentIndexInContentElement = leftOverBits % 64;
			if (currentIndexInContentElement > 0) {
				uint64_t tempMask = UINT64_MAX ^ (((uint64_t)1 << currentIndexInContentElement) - 1);
				tempRank = tempRank & tempMask | (currentContentElement >> (64 - currentIndexInContentElement));
			}
		}
		else {
			currentIndexInContentElement += this->bitsForClass;
		}
		tempRank = tempRank & mask;
		uint64_t tempRankSum = rankSum + tempRank;

		uint32_t bitsForOffset = RRRTable::getInstance().getBitsForOffset(tempRank);

		if (tempRankSum < count) {
			rankSum = tempRankSum;
		}
		else {
			uint64_t maskForOffset = (((uint64_t)1) << bitsForOffset) - 1;
			uint64_t tempOffset = currentContentElement >> (64 - bitsForOffset - currentIndexInContentElement);
			leftOverBits = currentIndexInContentElement + bitsForOffset;
			if (leftOverBits >= 64) {
				// we have overflow
				contentIndex++;
				currentContentElement = this->content[(uint32_t)contentIndex];
				currentIndexInContentElement = leftOverBits % 64;
				if (currentIndexInContentElement > 0) {
					uint64_t tempMask = UINT64_MAX ^ (((uint64_t)1 << currentIndexInContentElement) - 1);
					tempOffset = tempOffset & tempMask | (currentContentElement >> (64 - currentIndexInContentElement));
				}
			}

			tempOffset = tempOffset & maskForOffset;

			indexOfith1 += RRRTable::getInstance().getIndexForRank(tempRank, tempOffset, (uint32_t)(count-rankSum));
			// get out of while loop}
			break;
		}
		currentIndexInContentElement += bitsForOffset;
		if (currentIndexInContentElement >= 64) {
			// we have overflow
			contentIndex++;
			currentContentElement = this->content[(uint32_t)contentIndex];
			currentIndexInContentElement = currentIndexInContentElement % 64;
		}
		currentBlockIndex++;
		indexOfith1 += this->blockSize;
	}

	if (indexOfith1 == this->inputVectorLength)
	{
		throw invalid_argument("RRR > Select count-th 1 not found");
	}
	return indexOfith1;
}

uint64_t RRR::select0(uint64_t count) {
	if (count > this->inputVectorLength)
	{
		throw invalid_argument("RRR > Select count value too large");
	}
	if (count == 0)
	{
		throw invalid_argument("RRR > Select count value must be positive");
	}

	superBlock countBlock(count, 36);
	//vector<superBlock>::iterator supBlockIterator = lower_bound(this->superBlocks.begin(), this->superBlocks.end(), countBlock, &RRR::compareSuperBlockZeroes);
	vector<superBlock>::iterator supBlockIterator = this->getIteratorForSelectZero(count);
	superBlock supBlock = *(--supBlockIterator);
	uint64_t superBlockIndex = supBlockIterator - this->superBlocks.begin();

	// used to know in which block we current are in order to add the current block rank to the rankSum
	uint64_t currentBlockIndex = 0;
	uint64_t currentIndex = supBlock.second;
	uint64_t contentIndex = currentIndex / 64;
	uint64_t currentIndexInContentElement = currentIndex % 64;
	uint64_t currentContentElement = this->content[(uint32_t)contentIndex];
	uint64_t mask = (((uint64_t)1) << this->bitsForClass) - 1;

	// add the index of the first element in found superblock
	uint64_t indexOfith0 = this->blocksPerSuperBlock * this->blockSize * superBlockIndex;
	// set rankSum to the rank contained in the current superblock
	uint64_t rankSum = indexOfith0 - supBlock.first;

	// sum up block ranks up to the ib-th block
	uint64_t lastContentIndex = this->content.size() - 1;
	while (rankSum < count && (contentIndex < lastContentIndex || (contentIndex == lastContentIndex && currentIndexInContentElement < this->maxIndexInLastContentElement))) {
		uint64_t tempRank = currentContentElement >> (64 - this->bitsForClass - currentIndexInContentElement);
		uint64_t leftOverBits = currentIndexInContentElement + this->bitsForClass;
		if (leftOverBits >= 64) {
			// we have overflow
			contentIndex++;
			currentContentElement = this->content[(uint32_t)contentIndex];
			currentIndexInContentElement = leftOverBits % 64;
			if (currentIndexInContentElement > 0) {
				uint64_t tempMask = UINT64_MAX ^ (((uint64_t)1 << currentIndexInContentElement) - 1);
				tempRank = tempRank & tempMask | (currentContentElement >> (64 - currentIndexInContentElement));
			}
		}
		else {
			currentIndexInContentElement += this->bitsForClass;
		}
		tempRank = tempRank & mask;
		uint64_t tempRankSum = rankSum + this->blockSize - tempRank;

		uint32_t bitsForOffset = RRRTable::getInstance().getBitsForOffset(tempRank);

		if (tempRankSum < count) {
			rankSum = tempRankSum;
		}
		else {
			uint64_t maskForOffset = (((uint64_t)1) << bitsForOffset) - 1;
			uint64_t tempOffset = currentContentElement >> (64 - bitsForOffset - currentIndexInContentElement);
			leftOverBits = currentIndexInContentElement + bitsForOffset;
			if (leftOverBits >= 64) {
				// we have overflow
				contentIndex++;
				currentContentElement = this->content[(uint32_t)contentIndex];
				currentIndexInContentElement = leftOverBits % 64;
				if (currentIndexInContentElement > 0) {
					uint64_t tempMask = UINT64_MAX ^ (((uint64_t)1 << currentIndexInContentElement) - 1);
					tempOffset = tempOffset & tempMask | (currentContentElement >> (64 - currentIndexInContentElement));
				}
			}

			tempOffset = tempOffset & maskForOffset;

			indexOfith0 += RRRTable::getInstance().getIndexForRankZero(tempRank, tempOffset, (uint32_t)(count - rankSum), this->blockSize);
			// get out of while loop}
			break;
		}
		currentIndexInContentElement += bitsForOffset;
		if (currentIndexInContentElement >= 64) {
			// we have overflow
			contentIndex++;
			currentContentElement = this->content[(uint32_t)contentIndex];
			currentIndexInContentElement = currentIndexInContentElement % 64;
		}
		currentBlockIndex++;
		indexOfith0 += this->blockSize;
	}

	if (indexOfith0 == this->inputVectorLength)
	{
		throw invalid_argument("RRR > Select count-th 0 not found");
	}
	return indexOfith0;
}

uint8_t RRR::access(uint64_t index) {
	if (index >= this->inputVectorLength)
	{
		throw invalid_argument("RRR > Access index too large");
	}

	if (index == 0) {
		return (uint8_t)this->rank1(index);
	}

	// get 1 or 0 in constant time by using rank
	return (uint8_t)(this->rank1(index) - this->rank1(index - 1));
}

bool RRR::compareSuperBlock(superBlock a, superBlock b) {
	return a.first < b.first;
}

/*bool RRR::compareSuperBlockZeroes(superBlock a, superBlock b) {
	uint64_t superBlockLength = this->blocksPerSuperBlock * this->blockSize;
	return (superBlockLength - a.first) < (superBlockLength - b.first);
}*/

vector<superBlock>::iterator RRR::getIteratorForSelectZero(uint64_t count_) {
	uint64_t superBlockLength = this->blocksPerSuperBlock * this->blockSize;
	vector<superBlock>::iterator first = this->superBlocks.begin();
	++first;
	vector<superBlock>::iterator last = this->superBlocks.end();
	vector<superBlock>::iterator it = this->superBlocks.begin();
	iterator_traits<vector<uint32_t>::iterator>::difference_type count, step;
	count = distance(first, last);
	while (count > 0)
	{
		it = first; step = count / 2; advance(it, step);

		if (((it - this->superBlocks.begin()) * superBlockLength - (*it).first) + 1 < count_) {
			first = ++it;
			count -= step + 1;
		}
		else count = step;
	}
	return first;
}