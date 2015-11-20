#include "WaveletNode.h"

WaveletNode* WaveletNode::getLeftChild() const
{
	return leftChild;
}

WaveletNode* WaveletNode::getRightChild() const
{
	return rightChild;
}

WaveletNode::WaveletNode(string content_, WaveletNode *parent_, uint8_t start_, uint8_t end_, alphabet &alphabetIndices_) : parent(parent_), start(start_), end(end_) {

	// alphabet subrange division
	// start and end are inclusive indices
	// current node children will get alphabet intervals [start, threshold] and [threshold + 1, end]
	this->threshold = (uint8_t)(start / 2. + end / 2.);

	uint64_t zeroIndex = 0;
	uint64_t oneIndex = 0;
	uint64_t contentSize = content_.length();

	// substring from original string that contains only the 0 encoded content part
	char* contentZeroes = (char*)malloc(sizeof(char) * (contentSize + 1));
	// substring from original string that contains only the 1 encoded content part
	char* contentOnes = (char*)malloc(sizeof(char) * (contentSize + 1));

	// create binary string for RRR input
	for (uint64_t i = 0; i < contentSize; i++)
	{
		char c = content_[i];
		if (alphabetIndices_[c] <= threshold) {
			contentZeroes[zeroIndex] = c;
			zeroIndex++;
			content_[i] = '0';
		}
		else {
			contentOnes[oneIndex] = c;
			oneIndex++;
			content_[i] = '1';
		}
	}

	// create RRR
	this->content = new RRR(content_);

	// denote the end of substrings
	contentOnes[oneIndex] = '\0';
	contentZeroes[zeroIndex] = '\0';

	// create children only if content has more then one character
	if ((this->end - this->start) > 1) {
		this->leftChild = new WaveletNode(contentZeroes, this, this->start, this->threshold, alphabetIndices_);
		this->rightChild = new WaveletNode(contentOnes, this, this->threshold + 1, this->end, alphabetIndices_);
	}

	// free aliocated memory
	free(contentOnes);
	free(contentZeroes);
}

WaveletNode::~WaveletNode() {
	// delete RRR
	delete this->leftChild;
	delete this->rightChild;
	delete this->content;
}

RRR* WaveletNode::getContent() const
{
	return content;
}

uint8_t WaveletNode::getThreshold()
{
	return this->threshold;
}
