#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdint>
#include "../WaveletTree/WaveletTree.h"
#include "../WaveletTree/WaveletNode.h"
#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(UnitTestWaveletTreeSmall)
	{
	public:

		TEST_METHOD(WaveletTreeSmall)
		{
			string input = "AB";
			WaveletTree tree(input);

			for (int i = 0; i < input.length(); i++)
			{
				Assert::AreEqual((uint8_t)(input[i]), tree.access(i), L"Wavelet tree access test", LINE_INFO());
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
			Assert::IsTrue(exceptionThrown, L"Wavelet tree access test", LINE_INFO());
			exceptionThrown = false;

			Assert::AreEqual((uint64_t)0, tree.select('A', 1), L"Wavelet tree select test", LINE_INFO());
			Assert::AreEqual((uint64_t)1, tree.select('B', 1), L"Wavelet tree select test", LINE_INFO());
			try
			{
				tree.select('A', 4);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;
			try
			{
				tree.select('B', 0);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;

			Assert::AreEqual((uint64_t)1, tree.rank('A', 0), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)1, tree.rank('A', 1), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)0, tree.rank('B', 0), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)1, tree.rank('B', 1), L"Wavelet tree rank test", LINE_INFO());

			try
			{
				tree.rank('A', 32);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree rank test", LINE_INFO());
			exceptionThrown = false;

			try
			{
				tree.rank('B', -1);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree rank test", LINE_INFO());
			exceptionThrown = false;
		}
	};
}