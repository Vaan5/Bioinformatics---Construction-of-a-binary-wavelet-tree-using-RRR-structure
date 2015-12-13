import sys
import math
from scipy.special import binom

inputString = "11111111111111111111111111111111111111111111111111111111111111111111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"

def element_0(c):
	"""Generates first permutation with a given amount
	   of set bits, which is used to generate the rest."""
	return (1 << c) - 1

def next_perm(v):
	"""
	Generates next permutation with a given amount of set bits,
	given the previous lexicographical value.
	Taken from http://graphics.stanford.edu/~seander/bithacks.html
	"""
	t = (v | ( v - 1)) + 1
	w = t | ((((t & -t) / (v & -v)) >> 1) - 1)
	return w

def gen_blocks(p, b):
	"""
	Generates all blocks of a given popcount and blocksize
	"""
	v = initial = element_0(p)
	block_mask = element_0(b)

	while (v >= initial):
		yield v
		v = next_perm(v) & block_mask

def numberOfBits(x, y):
	return int(math.ceil(math.log(binom(x,y), 2)))

currentIndex = 0
blockSize = 4
finalString = ""
bitsForClass = 3
while True:
	if currentIndex >= len(inputString):
		break
	block = inputString[currentIndex:currentIndex + blockSize]

	cls = 0
	for i in block:
		if i == '1':
			cls += 1

	finalString += str(bin(cls))[2:].zfill(bitsForClass)

	if cls == 4:
		finalString += str(bin(0))[2:]
		currentIndex+=blockSize
		continue

	if cls == 0:
		finalString += str(bin(0))[2:]
		currentIndex+=blockSize
		continue
		
	# add offset
	index = 0
	for x in gen_blocks(cls, blockSize):
		# print str(bin(x))[2:].zfill(blockSize), str(block),  str(bin(x))[2:].zfill(blockSize) == str(block)
		if str(block) == str(bin(x))[2:].zfill(blockSize):
			finalString += str(bin(index))[2:].zfill(numberOfBits(blockSize, cls))
		index+=1
	#print finalString
	currentIndex+=blockSize

index = 0
output = ""
count = 0
while index < len(finalString):
	output += hex(int(finalString[index: index + 4], 2))[2:]
	count+=1
	if count % 16 == 0:
		output += "\n"
	index += 4

print output

