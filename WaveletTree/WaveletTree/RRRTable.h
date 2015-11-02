#pragma once
#include <vector>
#include <cstdint>

using namespace std;

typedef vector<vector<pair<uint32_t, vector<uint32_t> > > > table_t;
typedef pair<uint32_t, vector<uint32_t> > element_t;
typedef vector<pair<uint32_t, vector<uint32_t> > > class_t;

class RRRTable {
public:
	static RRRTable& getInstance();

	void createTable(uint32_t blockLengthInBits);

	uint32_t getOffset(uint32_t classIndex, uint32_t block, uint32_t blockLength);
	
	uint32_t getClassSize(uint32_t class_);
	table_t& getTable() { return table_; }
	static uint32_t initialBlockLength;

private:
	table_t table_;
	RRRTable(){};
	RRRTable(RRRTable const&);
	void operator=(RRRTable const&);
	uint32_t nextPermutation(uint32_t v);
	uint32_t firstElement(uint32_t c);
};