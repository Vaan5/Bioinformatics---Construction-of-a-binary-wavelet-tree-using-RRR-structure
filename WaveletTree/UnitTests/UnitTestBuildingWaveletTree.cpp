#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdint>
#include "../WaveletTree/WaveletTree.h"
#include "../WaveletTree/WaveletNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(UnitTestBuildingWaveletTree)
	{
	public:

		TEST_METHOD(AccessWholeTree)
		{
			string input = "Hajro i Denis imaju 100 bodova!";
			string outputForRoot = "0011101000111011011000000101100";
			WaveletTree tree(input);
			WaveletNode* root = tree.getRoot();

			RRR* rrr = root->getContent();

			string generatedOutput = "";
			for (int i = 0; i < input.length(); i++)
			{
				generatedOutput += rrr->access(i) + '0';
			}

			Assert::AreEqual(outputForRoot, generatedOutput, L"Root test", LINE_INFO());

			WaveletNode* leftChild = root->getLeftChild();

			rrr = leftChild->getContent();

			generatedOutput = "";
			string outputForLeftChild = "11000101000001110";
			for (int i = 0; i < outputForLeftChild.length(); i++)
			{
				generatedOutput += rrr->access(i) + '0';
			}
			Assert::AreEqual(outputForLeftChild, generatedOutput, L"Root test", LINE_INFO());

			WaveletNode* rightChild = root->getRightChild();

			rrr = rightChild->getContent();

			generatedOutput = "";
			string outputForRightChild = "01000010001001";
			for (int i = 0; i < outputForRightChild.length(); i++)
			{
				generatedOutput += rrr->access(i) + '0';
			}
			Assert::AreEqual(outputForRightChild, generatedOutput, L"Root test", LINE_INFO());
		}
	};
}