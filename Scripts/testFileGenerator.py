import sys
import random

"""
Generates a file in FASTA format whose content contains characters from range
[alphabetStartIndex, alphabetEndIndex] of size numberOfBytes.
"""

if len(sys.argv) != 5:
	print "Invalid number of arguments. Example usage: python testFileGenerator.py alphabetStartIndex alphabetEndIndex numberOfBytes outputFile"
	print "\t\tpython testFileGenerator.py 48 50 4096 output.txt"
	exit(1)

lowerBound = int(sys.argv[1])
upperBound = int(sys.argv[2])

if lowerBound < 32 or upperBound > 126:
	print "Alphabet indices must be in range [32,126]"
	exit(1)

numberOfBytes = int(sys.argv[3])

counter = 0;
with open(sys.argv[4], "w") as f:
	f.write(">Generated test file\n")
	content = ""
	while counter < numberOfBytes:
		character = random.randint(lowerBound, upperBound)
		content += chr(character)
		counter += 1
		if counter != 0 and counter % 70 == 0 or counter == numberOfBytes:
			content += "\n"
			f.write(content)
			content = ""

