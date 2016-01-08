import sys
import random

"""
Generates test and result files for given fasta file
"""

if len(sys.argv) != 5:
	print "Invalid number of arguments. Example usage: python testCommandGenerator.py randIntervalSize fastaFile testOutput resultOutputs"
	print "\t\tpython testFileGenerator.py 20 fasta.txt test.txt res.txt"
	exit(1)

fastaFile = sys.argv[2]
randIntervalSize = int(sys.argv[1])
testOutput = sys.argv[3]
resultOutputs = sys.argv[4]

tests = []
results = []
ranks = {}
selects = {}
counter = 0;
with open(fastaFile, "r") as f:
	content = ""
	for line in f.readlines():
		line = line.strip()
		if line[0] == '>':
			continue
		content += line

	rankInd = 0
	selectInd = 0
	accessInd = 0
	for character in content:
		if counter % randIntervalSize == 0:
			rankInd = counter + random.randint(0,randIntervalSize)
			selectInd = counter + random.randint(0,randIntervalSize)
			accessInd = counter + random.randint(0,randIntervalSize)
		# add the character to the dictionary
		if character not in ranks:
			ranks[character] = 0
		ranks[character] += 1

		selects[character] = counter

		if rankInd == counter:
			char = ranks.keys()[random.randint(0, len(ranks) - 1)]
			tests.append("rank {} {}".format(char, counter))
			results.append("{}".format(ranks[char]))
		if selectInd == counter:
			char = selects.keys()[random.randint(0, len(selects) - 1)]
			tests.append("select {} {}".format(char, ranks[char]))
			results.append("{}".format(selects[char]))
		if accessInd == counter:
			tests.append("access {}".format(counter))
			results.append("{}".format(character))

		counter += 1

zipped = zip(tests, results)
random.shuffle(zipped)

with open(testOutput, "w") as output:
	with open(resultOutputs, "w") as res:
		for (t,r) in zipped:
			output.write(t + "\n")
			res.write(r + "\n")
	output.write("STAT\n")
	output.write("EXIT\n")