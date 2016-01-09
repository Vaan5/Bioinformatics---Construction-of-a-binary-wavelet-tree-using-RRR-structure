#pragma once
#include "RRR.h"
#include <string>
#include <vector>
#include "Common.h"
#include <cstdint>
#include <cstdlib>

// Class representing a node in the wavelet tree
// Example usage:
//		WaveletNode* root = new WaveletNode("Example text", NULL, 0, alphabetSize - 1, alphabetIndices, false, NULL);
//		RRR* rrr = root->getContent();
class WaveletNode {
public:
	// Creates a new wavelet tree node
	//		content_			content to be stored in the node
	//		parent_				parent node in the wavelet tree
	//		start_				first index of the alphabet subset stored in the node
	//		end_				last index of the alphabet subset stored in the node
	//		alphabetIndices_	symbol -> index alphabet mapping calculated when constructing the wavelet tree
	//		isLeftChild_		flag to know if the current node is a left child
	//		visualOutput		file handler used to generate graphviz data
	WaveletNode(string content_, WaveletNode *parent_, uint8_t start_, uint8_t end_, alphabet &alphabetIndices_, bool isLeftChild_, FILE* visualOutput = NULL);

	// Destructor
	virtual ~WaveletNode();

	// Returns left child node
	WaveletNode* getLeftChild() const;

	// Returns right child node
	WaveletNode* getRightChild() const;

	// Returns parent node
	WaveletNode* getParent() const;

	// Returns RRR in which the content is stored
	RRR* getContent() const;

	// Returns threshold used to define left and right child alhpabet subsets
	uint8_t getThreshold();

	// Returns true if the current child is it's parent's left child,
	// false otherwise
	bool getIsLeftChild();

	// Returns first index of the node's alphabet subset
	uint8_t getStart();

	// Returns last index of the node's alphabet subset
	uint8_t getEnd();

private:
	// Identifier counter used for naming nodes when creating graphviz data
	static int idGenerator;

	// Current node identifier used for generating graphviz data
	int id;

	// Parent node
	WaveletNode *parent = NULL;

	// Left child node
	WaveletNode *leftChild = NULL;

	// Right child node
	WaveletNode *rightChild = NULL;

	// First index of the node's alphabet subset
	uint8_t start;

	// Last index of the node's alphabet subset
	uint8_t end;

	// Threshold used to define left and right child alhpabet subsets
	uint8_t threshold;

	// Flag to know if the current node is a left child
	bool isLeftChild;

	// RRR that stores this node's content
	RRR *content;
};