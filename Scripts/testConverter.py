import sys,re
import os

"""
Transforms VS unit tests into cxxunit test format. Headers and class name have to be specified manually.
"""

if len(sys.argv) != 3:
	print "Invalid number of arguments. Example usage: python testConverter.py inputDirectory outputFile"
	exit(1)


inputDir = sys.argv[1]

files = os.listdir(inputDir)

def helperFunction(x):
	return 'void test{}()'.format(x.group(1))

outputContent = []
with open(sys.argv[2], "w") as out:
	for file in files:
		if not file.endswith(".cpp"):
			continue
		if not file.startswith("UnitTest"):
			continue
		with open(inputDir + "/" + file, "r") as f:
			print file
			tempOutput = ""
			content = f.read()
			while "TEST_METHOD" in content:
				startIndex = content.find("TEST_METHOD")
				counter = 0
				firstFound = False
				i = startIndex
				while counter != 0 or not firstFound:
					if content[i] == '{':
						counter += 1
						firstFound = True
					elif content[i] == '}':
						counter -= 1

					i += 1

				changedFunction = content[startIndex:i]
				changedFunction = re.sub(r'TEST_METHOD[\s]*\(([A-Za-z0-9_]+)\)', helperFunction, changedFunction)
				changedFunction = re.sub(r'Assert::AreEqual', "TS_ASSERT_EQUALS", changedFunction)
				changedFunction = re.sub(r'Assert::IsTrue', "TS_ASSERT", changedFunction)
				changedFunction = re.sub(r',\s*L\".+?LINE_INFO\(\)', "", changedFunction)
				outputContent.append(changedFunction)

				content = content[i:]

	out.write("""
#ifndef _TESTS_H
#define __TESTS_H

#include <cxxtest/TestSuite.h>
#include <cstdint>
#include "../WaveletTree/WaveletTree/RRR.h"
#include "../WaveletTree/WaveletTree/RRRTable.h"
#include "../WaveletTree/WaveletTree/WaveletTree.h"
#include "../WaveletTree/WaveletTree/WaveletNode.h"

#include <string>
#include <iostream>

using namespace std;

class Tests : public CxxTest::TestSuite {
public:
		void setUp() {
			RRRTable::initialBlockLength = 0;
		}
	""")
	for c in outputContent:
		out.write(c + "\n\n")

	out.write("""
};


#endif // __TESTS_H
		""")

