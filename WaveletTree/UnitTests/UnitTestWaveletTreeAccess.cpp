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
	TEST_CLASS(UnitTestWaveletTreeAccess)
	{
	public:

		TEST_METHOD(WaveletTreeAccess)
		{
			string input = "Hajro i Denis imaju 100 bodova!";
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
		}
	};
}