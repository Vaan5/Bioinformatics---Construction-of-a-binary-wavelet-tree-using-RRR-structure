import sys

"""
Calculates differences between yourResults and realResults files.
Prints them to stdout. testCommands contains commands for which these outputs were generated
"""

if len(sys.argv) != 4:
	print "Invalid number of arguments. Example usage: python diff.py yourResults realResults testCommands"
	print "\t\tpython diff.py our_res.txt res.txt test.txt"
	exit(1)

correctCounter = 0
errorCounter = 0
with open(sys.argv[1], "r") as pred:
	with open(sys.argv[2], "r") as label:
		with open(sys.argv[3], "r") as commands:
			coms = commands.readlines()
			predictions = pred.readlines()
			labels = label.readlines()

			for i in range(len(labels)):
				if labels[i] == "\n":
					continue
				if labels[i] != predictions[i]:
					print "{} - Got {}, Should have gotten {}".format(coms[i+1].replace('\n', ' '), predictions[i].replace('\n', ' '), labels[i].replace('\n', ' '))
					errorCounter += 1
				else:
					correctCounter += 1

print "Finished file {}\nCorrect: {}\nIncorrect: {}".format(sys.argv[1], correctCounter, errorCounter)