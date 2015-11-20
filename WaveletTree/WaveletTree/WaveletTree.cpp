#include "WaveletTree.h"

WaveletNode* WaveletTree::getRoot() const
{
	return root;
}

WaveletTree::WaveletTree(string content) {
	this->alphabetIndices = alphabet(256, -1);
	for (int i = 0; i < content.length(); i++) {
		if (this->alphabetIndices[content[i]] == -1) {
			this->alphabetIndices[content[i]] = 1;
		}
	}
	
	int cumSum = 0;
	for (int i = 0; i < this->alphabetIndices.size(); i++) {
		if (this->alphabetIndices[i] == 1) {
			this->alphabetIndices[i] = cumSum;
			cumSum++;
		}
	}
	this->alphabetSize = cumSum;

	// build the binary tree
	this->root = new WaveletNode(content, NULL, 0, this->alphabetSize - 1, this->alphabetIndices);
}

WaveletTree::~WaveletTree() {
	delete this->root;
}

uint64_t WaveletTree::rank(uint8_t character, uint64_t index)
{
	WaveletNode* v = root;
	uint64_t r = index;
	uint8_t characterIndex = this->alphabetIndices[character];

	if (characterIndex == -1)
	{
		throw invalid_argument("Stored string doesn't contain the requested character...");
	}

	bool isRoot = true;

	while (v != NULL)
	{
		uint8_t threshold = v->getThreshold();

		if (!isRoot)
		{
			r--;
		}
		else
		{
			isRoot = false;
		}

		if (characterIndex <= threshold)
		{
			r = v->getContent()->rank0(r);
			v = v->getLeftChild();
		}
		else
		{
			r = v->getContent()->rank1(r);
			v = v->getRightChild();
		}
	}
	return r;
}
