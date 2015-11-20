#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdint>
#include "../WaveletTree/WaveletTree.h"
#include "../WaveletTree/WaveletNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(UnitTestWaveletTreeRank)
	{
	public:

		TEST_METHOD(WaveletTreeRank)
		{
			string input = "Hajro i Denis imaju 100 bodova!";
			WaveletTree tree(input);
			Assert::AreEqual((uint64_t)2, tree.rank('a', 20), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)3, tree.rank('a', 29), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)2, tree.rank('a', 28), L"Wavelet tree rank test", LINE_INFO());

			Assert::AreEqual((uint64_t)1, tree.rank('!', 30), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)0, tree.rank('!', 29), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)0, tree.rank('!', 5), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)0, tree.rank('!', 0), L"Wavelet tree rank test", LINE_INFO());

			Assert::AreEqual((uint64_t)1, tree.rank('H', 0), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)1, tree.rank('H', 1), L"Wavelet tree rank test", LINE_INFO());
			Assert::AreEqual((uint64_t)1, tree.rank('H', 30), L"Wavelet tree rank test", LINE_INFO());
		}
	};
}