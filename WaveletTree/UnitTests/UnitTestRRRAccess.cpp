#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdint>
#include <string>
#include "..\WaveletTree\RRR.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(UnitTestRRRAccess)
	{
	public:

		TEST_METHOD(Access)
		{
			string testString("001010011010101101000001001010011011000101101101011");
			RRR rrr(testString);
			Assert::AreEqual(((uint8_t)0), rrr.access(0), L"Access", LINE_INFO());
			for (unsigned int i = 0; i < testString.length(); i++) {
				uint8_t compareValue = (uint8_t)(testString[i] - '0');
				Assert::AreEqual(compareValue, rrr.access((uint64_t)i), L"Access", LINE_INFO());
			}
		}

		TEST_METHOD(AccessSmall)
		{
			vector<string> cmp;
			cmp.push_back("0");
			cmp.push_back("1");
			cmp.push_back("00");
			cmp.push_back("01");
			cmp.push_back("10");
			cmp.push_back("11");
			cmp.push_back("000");
			cmp.push_back("001");
			cmp.push_back("110");
			cmp.push_back("111");
			for (int s = 0; s < cmp.size(); s++)
			{
				string testString = cmp[s];
				RRR rrr(testString);
				for (unsigned int i = 0; i < testString.length(); i++) {
					uint8_t compareValue = (uint8_t)(testString[i] - '0');
					Assert::AreEqual(compareValue, rrr.access((uint64_t)i), L"Access", LINE_INFO());
				}
			}
		}

	};
}