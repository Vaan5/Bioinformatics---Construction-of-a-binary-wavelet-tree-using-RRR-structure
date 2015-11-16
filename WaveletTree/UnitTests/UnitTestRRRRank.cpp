#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdint>
#include "..\WaveletTree\RRR.h"
#include "..\WaveletTree\RRRTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{		
	TEST_CLASS(UnitTestRRRRank)
	{
	public:
		
		TEST_METHOD(Rank1)
		{
			RRR rrr(string("001010011010101101000001001010011011000101101101011"));
			Assert::AreEqual((uint64_t)12, rrr.rank1(29), L"Rank 12 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr.rank1(0), L"Rank 0 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr.rank1(1), L"Rank 0 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)24, rrr.rank1(50), L"Rank 24 passed", LINE_INFO());
		}

		TEST_METHOD(Rank0)
		{
			RRR rrr(string("001010011010101101000001001010011011000101101101011"));
			Assert::AreEqual((uint64_t)18, rrr.rank0(29), L"Rank 18 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr.rank0(0), L"Rank 1 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr.rank0(1), L"Rank 2 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)27, rrr.rank0(50), L"Rank 27 passed", LINE_INFO());
		}

	};
}