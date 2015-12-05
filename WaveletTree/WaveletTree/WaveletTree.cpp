#include "WaveletTree.h"

WaveletNode* WaveletTree::getRoot() const
{
	return root;
}

WaveletTree::WaveletTree(string content) {
	this->alphabetIndices = alphabet(256, -1);
	this->alphabetCharacters = inverseAlphabet(256, 0);
	for (int i = 0; i < content.length(); i++) {
		if (this->alphabetIndices[content[i]] == -1) {
			this->alphabetIndices[content[i]] = 1;
		}
	}
	
	int cumSum = 0;
	for (int i = 0; i < this->alphabetIndices.size(); i++) {
		if (this->alphabetIndices[i] == 1) {
			this->alphabetIndices[i] = cumSum;
			this->alphabetCharacters[cumSum] = i;
			cumSum++;
		}
	}
	this->alphabetSize = cumSum;

	// build the binary tree
	this->root = new WaveletNode(content, NULL, 0, this->alphabetSize - 1, this->alphabetIndices, true);
}

WaveletTree::~WaveletTree() {
	delete this->root;
}

uint64_t WaveletTree::rank(uint8_t character, uint64_t index)
{
	WaveletNode* v = root;
	uint64_t r = index;
	int16_t characterIndex = this->alphabetIndices[character];

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

		if (r == 0) return 0;
	}
	return r;
}

uint64_t WaveletTree::select(uint8_t character, uint64_t count)
{
	int16_t characterIndex = this->alphabetIndices[character];

	if (characterIndex == -1)
	{
		throw invalid_argument("Stored string doesn't contain the requested character...");
	}

	WaveletNode* v = NULL;
	WaveletNode* temp = root;
	uint64_t r = count;
	while (temp != NULL)
	{
		// first go to the child node
		uint8_t threshold = temp->getThreshold();
		v = temp;

		if (characterIndex <= threshold)
		{
			temp = temp->getLeftChild();
		}
		else
		{
			temp = temp->getRightChild();
		}
	}
	// v is leaf

	// handle leaf; and the case when the tree has only one node
	uint8_t threshold = v->getThreshold();
	if (characterIndex <= threshold)
	{
		r = v->getContent()->select0(r);
	}
	else
	{
		r = v->getContent()->select1(r);
	}

	// go up the tree
	while (v != root)
	{
		r++;
		WaveletNode* p = v->getParent();
		if (v->getIsLeftChild())
		{
			r = p->getContent()->select0(r);
		}
		else
		{
			r = p->getContent()->select1(r);
		}

		v = p;
	}

	return r;
}

uint8_t WaveletTree::access(uint64_t index)
{
	WaveletNode* v = root;
	uint64_t r = index;

	bool isRoot = true;

	while (v != NULL)
	{
		if (!isRoot)
		{
			r--;
		}
		else
		{
			isRoot = false;
		}

		if (v->getContent()->access(r) == 0)
		{
			r = v->getContent()->rank0(r);
			if (v->getLeftChild() == NULL)
			{
				return this->alphabetCharacters[v->getStart()];
			}
			v = v->getLeftChild();
		}
		else
		{
			r = v->getContent()->rank1(r);
			if (v->getRightChild() == NULL)
			{
				return this->alphabetCharacters[v->getEnd()];
			}
			v = v->getRightChild();
		}
	}
	return 0;
}
