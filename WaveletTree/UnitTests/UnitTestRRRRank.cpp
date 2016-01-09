#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdint>
#include "..\WaveletTree\RRR.h"
#include "..\WaveletTree\RRRTable.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{		
	TEST_CLASS(UnitTestRRRRank)
	{
	public:
		
		TEST_METHOD(Rank1)
		{
			string input = "001010011010101101000001001010011011000101101101011";
			RRR rrr(input);
			Assert::AreEqual((uint64_t)12, rrr.rank1(29), L"Rank 12 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr.rank1(0), L"Rank 0 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr.rank1(1), L"Rank 0 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)24, rrr.rank1(50), L"Rank 24 passed", LINE_INFO());
		}

		TEST_METHOD(Rank0)
		{
			string input = "001010011010101101000001001010011011000101101101011";
			RRR rrr(input);
			Assert::AreEqual((uint64_t)18, rrr.rank0(29), L"Rank 18 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr.rank0(0), L"Rank 1 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr.rank0(1), L"Rank 2 passed", LINE_INFO());
			Assert::AreEqual((uint64_t)27, rrr.rank0(50), L"Rank 27 passed", LINE_INFO());
		}

		TEST_METHOD(Rank1Small)
		{
			string input = "0";
			RRR rrr1(input);
			Assert::AreEqual((uint64_t)0, rrr1.rank1(0), L"Rank passed", LINE_INFO());
			input = "00";
			RRR rrr2(input);
			Assert::AreEqual((uint64_t)0, rrr2.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr2.rank1(1), L"Rank passed", LINE_INFO());
			input = "10";
			RRR rrr3(input);
			Assert::AreEqual((uint64_t)1, rrr3.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr3.rank1(1), L"Rank passed", LINE_INFO());
			input = "01";
			RRR rrr4(input);
			Assert::AreEqual((uint64_t)0, rrr4.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr4.rank1(1), L"Rank passed", LINE_INFO());
			input = "11";
			RRR rrr5(input);
			Assert::AreEqual((uint64_t)1, rrr5.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr5.rank1(1), L"Rank passed", LINE_INFO());
		}

		TEST_METHOD(Rank0Small)
		{
			string input = "0";
			RRR rrr1(input);
			Assert::AreEqual((uint64_t)1, rrr1.rank0(0), L"Rank passed", LINE_INFO());
			input = "00";
			RRR rrr2(input);
			Assert::AreEqual((uint64_t)1, rrr2.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr2.rank0(1), L"Rank passed", LINE_INFO());
			input = "10";
			RRR rrr3(input);
			Assert::AreEqual((uint64_t)0, rrr3.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr3.rank0(1), L"Rank passed", LINE_INFO());
			input = "01";
			RRR rrr4(input);
			Assert::AreEqual((uint64_t)1, rrr4.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr4.rank0(1), L"Rank passed", LINE_INFO());
			input = "11";
			RRR rrr5(input);
			Assert::AreEqual((uint64_t)0, rrr5.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr5.rank0(1), L"Rank passed", LINE_INFO());
		}

		TEST_METHOD(Rank1Middle)
		{
			string input = "000";
			RRR rrr1(input);
			Assert::AreEqual((uint64_t)0, rrr1.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr1.rank1(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr1.rank1(2), L"Rank passed", LINE_INFO());
			input = "001";
			RRR rrr2(input);
			Assert::AreEqual((uint64_t)0, rrr2.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr2.rank1(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr2.rank1(2), L"Rank passed", LINE_INFO());
			input = "010";
			RRR rrr3(input);
			Assert::AreEqual((uint64_t)0, rrr3.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr3.rank1(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr3.rank1(2), L"Rank passed", LINE_INFO());
			input = "011";
			RRR rrr4(input);
			Assert::AreEqual((uint64_t)0, rrr4.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr4.rank1(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr4.rank1(2), L"Rank passed", LINE_INFO());
			input = "111";
			RRR rrr5(input);
			Assert::AreEqual((uint64_t)1, rrr5.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr5.rank1(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)3, rrr5.rank1(2), L"Rank passed", LINE_INFO());

			input = "1011";
			RRR rrr6(input);
			Assert::AreEqual((uint64_t)1, rrr6.rank1(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr6.rank1(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr6.rank1(2), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)3, rrr6.rank1(3), L"Rank passed", LINE_INFO());
		}

		TEST_METHOD(Rank0Middle)
		{
			string input = "000";
			RRR rrr1(input);
			Assert::AreEqual((uint64_t)1, rrr1.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr1.rank0(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)3, rrr1.rank0(2), L"Rank passed", LINE_INFO());
			input = "001";
			RRR rrr2(input);
			Assert::AreEqual((uint64_t)1, rrr2.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr2.rank0(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr2.rank0(2), L"Rank passed", LINE_INFO());
			input = "010";
			RRR rrr3(input);
			Assert::AreEqual((uint64_t)1, rrr3.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr3.rank0(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr3.rank0(2), L"Rank passed", LINE_INFO());
			input = "011";
			RRR rrr4(input);
			Assert::AreEqual((uint64_t)1, rrr4.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr4.rank0(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr4.rank0(2), L"Rank passed", LINE_INFO());
			input = "111";
			RRR rrr5(input);
			Assert::AreEqual((uint64_t)0, rrr5.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr5.rank0(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)0, rrr5.rank0(2), L"Rank passed", LINE_INFO());

			input = "1011";
			RRR rrr6(input);
			Assert::AreEqual((uint64_t)0, rrr6.rank0(0), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr6.rank0(1), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr6.rank0(2), L"Rank passed", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr6.rank0(3), L"Rank passed", LINE_INFO());
		}

	};
}