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
	TEST_CLASS(UnitTestWaveletTreeSelect)
	{
	public:

		TEST_METHOD(WaveletTreeSelect)
		{
			string input = "Hajro i Denis imaju 100 bodova!";
			WaveletTree tree(input);
			Assert::AreEqual((uint64_t)2, tree.select('j', 1), L"Wavelet tree select test", LINE_INFO());
			Assert::AreEqual((uint64_t)17, tree.select('j', 2), L"Wavelet tree select test", LINE_INFO());
			bool exceptionThrown = false;
			try
			{
				tree.select('j', 0);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;
			try
			{
				tree.select('j', 3);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;

			try
			{
				tree.select('j', -1);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;

			exceptionThrown = false;

			try
			{
				tree.select('F', 1);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;

			exceptionThrown = false;

			try
			{
				tree.select('F', -1);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;

			exceptionThrown = false;

			try
			{
				tree.select('F', 0);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;
			
			Assert::AreEqual((uint64_t)0, tree.select('H', 1), L"Wavelet tree select test", LINE_INFO());
			try
			{
				tree.select('H', 558);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;


			Assert::AreEqual((uint64_t)1, tree.select('a', 1), L"Wavelet tree select test", LINE_INFO());
			Assert::AreEqual((uint64_t)16, tree.select('a', 2), L"Wavelet tree select test", LINE_INFO());
			Assert::AreEqual((uint64_t)29, tree.select('a', 3), L"Wavelet tree select test", LINE_INFO());
			try
			{
				tree.select('a', 4);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;

			Assert::AreEqual((uint64_t)20, tree.select('1', 1), L"Wavelet tree select test", LINE_INFO());
			Assert::AreEqual((uint64_t)21, tree.select('0', 1), L"Wavelet tree select test", LINE_INFO());
			Assert::AreEqual((uint64_t)22, tree.select('0', 2), L"Wavelet tree select test", LINE_INFO());

			try
			{
				tree.select('0', 4);
			}
			catch (invalid_argument &e)
			{
				exceptionThrown = true;
			}
			Assert::IsTrue(exceptionThrown, L"Wavelet tree select test", LINE_INFO());
			exceptionThrown = false;

			Assert::AreEqual((uint64_t)30, tree.select('!', 1), L"Wavelet tree select test", LINE_INFO());
		}
	};
}