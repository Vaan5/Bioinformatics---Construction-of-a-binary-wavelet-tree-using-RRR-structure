#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdint>
#include "..\WaveletTree\RRR.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace UnitTests
{
	TEST_CLASS(UnitTestRRRSelect)
	{
	public:

		TEST_METHOD(Select1)
		{
			string input = "001010011010101101000001001010011011000101101101011";
			RRR rrr(input);
			Assert::AreEqual((uint64_t)14, rrr.select1(7), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)15, rrr.select1(8), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr.select1(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)4, rrr.select1(2), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)23, rrr.select1(10), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)26, rrr.select1(11), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)50, rrr.select1(24), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)49, rrr.select1(23), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)47, rrr.select1(22), L"Select", LINE_INFO());
		}

		TEST_METHOD(Select0)
		{
			string input = "001010011010101101000001001010011011000101101101011";
			RRR rrr(input);
			Assert::AreEqual((uint64_t)0, rrr.select0(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr.select0(2), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)3, rrr.select0(3), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)5, rrr.select0(4), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)48, rrr.select0(27), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)13, rrr.select0(8), L"Select", LINE_INFO());
		}

		TEST_METHOD(Select1Small)
		{
			string input = "10";
			RRR rrr3(input);
			Assert::AreEqual((uint64_t)0, rrr3.select1(1), L"Select", LINE_INFO());

			input = "01";
			RRR rrr4(input);
			Assert::AreEqual((uint64_t)1, rrr4.select1(1), L"Select", LINE_INFO());

			input = "11";
			RRR rrr5(input);
			Assert::AreEqual((uint64_t)0, rrr5.select1(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr5.select1(2), L"Select", LINE_INFO());
		}

		TEST_METHOD(Select0Small)
		{
			string input = "0";
			RRR rrr1(input);
			Assert::AreEqual((uint64_t)0, rrr1.select0(1), L"Select", LINE_INFO());

			input = "00";
			RRR rrr2(input);
			Assert::AreEqual((uint64_t)0, rrr2.select0(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr2.select0(2), L"Select", LINE_INFO());

			input = "10";
			RRR rrr3(input);
			Assert::AreEqual((uint64_t)1, rrr3.select0(1), L"Select", LINE_INFO());

			input = "01";
			RRR rrr4(input);
			Assert::AreEqual((uint64_t)0, rrr4.select0(1), L"Select", LINE_INFO());
		}

		TEST_METHOD(Select1Middle)
		{
			string input = "001";
			RRR rrr2(input);
			Assert::AreEqual((uint64_t)2, rrr2.select1(1), L"Select", LINE_INFO());
			
			input = "010";
			RRR rrr3(input);
			Assert::AreEqual((uint64_t)1, rrr3.select1(1), L"Select", LINE_INFO());
			
			input = "011";
			RRR rrr4(input);
			Assert::AreEqual((uint64_t)1, rrr4.select1(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr4.select1(2), L"Select", LINE_INFO());

			input = "111";
			RRR rrr5(input);
			Assert::AreEqual((uint64_t)0, rrr5.select1(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr5.select1(2), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr5.select1(3), L"Select", LINE_INFO());

			input = "1011";
			RRR rrr6(input);
			Assert::AreEqual((uint64_t)0, rrr6.select1(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr6.select1(2), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)3, rrr6.select1(3), L"Select", LINE_INFO());
		}

		TEST_METHOD(Select0Middle)
		{
			string input = "000";
			RRR rrr1(input);
			Assert::AreEqual((uint64_t)0, rrr1.select0(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr1.select0(2), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr1.select0(3), L"Select", LINE_INFO());

			input = "001";
			RRR rrr2(input);
			Assert::AreEqual((uint64_t)0, rrr2.select0(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)1, rrr2.select0(2), L"Select", LINE_INFO());

			input = "010";
			RRR rrr3(input);
			Assert::AreEqual((uint64_t)0, rrr3.select0(1), L"Select", LINE_INFO());
			Assert::AreEqual((uint64_t)2, rrr3.select0(2), L"Select", LINE_INFO());

			input = "011";
			RRR rrr4(input);
			Assert::AreEqual((uint64_t)0, rrr4.select0(1), L"Select", LINE_INFO());

			input = "1011";
			RRR rrr6(input);
			Assert::AreEqual((uint64_t)1, rrr6.select0(1), L"Select", LINE_INFO());
		}

	};
}