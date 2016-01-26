import sys
import random

"""
Generates test and result files for given fasta file
"""

if len(sys.argv) != 2:
	print "Invalid number of arguments. Example usage: python inputFileStats.py fastaFile"
	print "\t\tpython testFileGenerator.py fasta.txt"
	exit(1)

fastaFile = sys.argv[1]

tests = []
results = []
ranks = {}
selects = {}
counter = 0;
with open(fastaFile, "r") as f:
	content = ""
	for line in f.readlines():
		line = line.strip()
		if len(line) == 0 or line[0] == '>':
			continue
		content += line

	for character in content:
		# add the character to the dictionary
		if character not in ranks:
			ranks[character] = 0

		ranks[character] += 1
		selects[character] = counter

		counter += 1

print ranks
print selects
