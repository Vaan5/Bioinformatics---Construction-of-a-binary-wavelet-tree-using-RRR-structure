#ifndef __SIMPLETEST_H
#define __SIMPLETEST_H

#include <cxxtest/TestSuite.h>
#include <cstdint>
#include "../WaveletTree/WaveletTree/RRR.h"
#include "../WaveletTree/WaveletTree/RRRTable.h"
#include "../WaveletTree/WaveletTree/WaveletTree.h"
#include "../WaveletTree/WaveletTree/WaveletNode.h"

#include <string>
#include <iostream>

//
// A simple test suite: Just inherit CxxTest::TestSuite and write tests!
//

using namespace std;

class SimpleTest : public CxxTest::TestSuite {
public:
    void testWaveletTreeAccess() {
		string input = "Hajro i Denis imaju 100 bodova!";
		WaveletTree tree(input);

		for (int i = 0; i < input.length(); i++)
		{
			TS_ASSERT_EQUALS((uint8_t)(input[i]), tree.access(i));
		}

		bool exceptionThrown = false;
		try
		{
			tree.access(-1);
		}
		catch (invalid_argument &e)
		{
			exceptionThrown = true;
		}
		TS_ASSERT(exceptionThrown);
		exceptionThrown = false;
    }
    
    void testRRRRank() {
    	string input = "001010011010101101000001001010011011000101101101011";
    	RRR rrr(input);
		TS_ASSERT_EQUALS((uint64_t)12, rrr.rank1(29));
		TS_ASSERT_EQUALS((uint64_t)0, rrr.rank1(0));
		TS_ASSERT_EQUALS((uint64_t)0, rrr.rank1(1));
		TS_ASSERT_EQUALS((uint64_t)24, rrr.rank1(50));
    }
};


#endif // __SIMPLETEST_H
