import sys

"""
Calculates rank and select for given character and file
"""

if len(sys.argv) != 5:
	print "Invalid number of arguments. Example usage: python counter.py fastaFile rankIndex selectCount character"
	print "\t\tpython counter.py fasta.txt 20 20 A"
	exit(1)

with open(sys.argv[1], "r") as f:
	content = ""
	for line in f.readlines():
		line = line.strip()
		if line[0] == '>':
			continue
		content += line

input = content
rankLimit = int(sys.argv[2])
selectLimit = int(sys.argv[3])
character = chr(sys.argv[4])

counter = 0
for i in range(rankLimit + 1):
	if input[i] == character:
		counter += 1

print counter

index = 0
counter = 0
while True:
	if input[index] == character:
		counter += 1
	if counter == selectLimit:
		print index
		break
	index += 1
