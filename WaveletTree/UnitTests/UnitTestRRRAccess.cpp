#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdint>
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
			RRR rrr(string("001010011010101101000001001010011011000101101101011"));
			// change to access - TODO
			Assert::AreEqual((uint64_t)14, rrr.select1(7), L"Select1 passed", LINE_INFO());
		}

	};
}