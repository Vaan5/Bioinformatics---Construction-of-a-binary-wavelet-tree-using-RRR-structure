#include "WaveletNode.h"

// Returns left child node
WaveletNode* WaveletNode::getLeftChild() const {
	return this->leftChild;
}

// Returns right child node
WaveletNode* WaveletNode::getRightChild() const {
	return this->rightChild;
}

// Returns parent node
WaveletNode* WaveletNode::getParent() const {
	return this->parent;
}

// Creates a new wavelet tree node
//		content_			content to be stored in the node
//		parent_				parent node in the wavelet tree
//		start_				first index of the alphabet subset stored in the node
//		end_				last index of the alphabet subset stored in the node
//		alphabetIndices_	symbol -> index alphabet mapping calculated when constructing the wavelet tree
//		isLeftChild_		flag to know if the current node is a left child
//		visualOutput		file handler used to generate graphviz data
WaveletNode::WaveletNode(string content_, WaveletNode *parent_, uint8_t start_, uint8_t end_, alphabet &alphabetIndices_, bool isLeftChild_, FILE* visualOutput) : parent(parent_), start(start_), end(end_), isLeftChild(isLeftChild_) {
	this->id = idGenerator++;

	if (visualOutput != NULL) {
		if (this->parent != NULL) {
			fprintf(visualOutput, "\t%d -> %d;\n", this->parent->id, this->id);
		}
		fprintf(visualOutput, "\t%d [ label = \"%s\\n", this->id, content_.c_str());
	}
	// Alphabet subrange division
	// start and end are inclusive indices
	// Current node children will get alphabet intervals [start, threshold] and [threshold + 1, end]
	this->threshold = (uint8_t)(start / 2. + end / 2.);

	uint64_t zeroIndex = 0;
	uint64_t oneIndex = 0;
	uint64_t contentSize = content_.length();

	// Substring from original string that contains only the 0 encoded content part
	char* contentZeroes = (char*)malloc(sizeof(char) * (contentSize + 1));
	// Substring from original string that contains only the 1 encoded content part
	char* contentOnes = (char*)malloc(sizeof(char) * (contentSize + 1));

	// Create binary string for RRR input
	for (uint64_t i = 0; i < contentSize; i++) {
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

	if (visualOutput != NULL) {
		fprintf(visualOutput, "%s\"];\n", content_.c_str());
	}

	// Create RRR
	this->content = new RRR(content_);

	// Denote the end of substrings
	contentOnes[oneIndex] = '\0';
	contentZeroes[zeroIndex] = '\0';

	// Create children only if content has more than two characters
	if ((this->end - this->start) > 1) {
		this->leftChild = new WaveletNode((string)contentZeroes, this, this->start, this->threshold, alphabetIndices_, true, visualOutput);
		if (this->threshold + 1 != this->end) this->rightChild = new WaveletNode((string)contentOnes, this, this->threshold + 1, this->end, alphabetIndices_, false, visualOutput);
	}

	// Free aliocated memory
	free(contentOnes);
	free(contentZeroes);
}

// Free memory
WaveletNode::~WaveletNode() {
	delete this->leftChild;
	delete this->rightChild;
	delete this->content;
}

// Returns RRR in which the content is stored
RRR* WaveletNode::getContent() const {
	return content;
}

// Returns threshold used to define left and right child alhpabet subsets
uint8_t WaveletNode::getThreshold() {
	return this->threshold;
}

// Returns true if the current child is it's parent's left child,
// false otherwise
bool WaveletNode::getIsLeftChild() {
	return this->isLeftChild;
}

// Returns first index of the node's alphabet subset
uint8_t WaveletNode::getStart() {
	return this->start;
}

// Returns last index of the node's alphabet subset
uint8_t WaveletNode::getEnd() {
	return this->end;
}

// Identifier counter used for naming nodes when creating graphviz data
int WaveletNode::idGenerator = 0;
