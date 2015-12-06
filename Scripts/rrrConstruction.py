import sys
import math
from scipy.special import binom

inputString = "001011100000000000010010000010000010000000000010000000001010110001000000000001001000010110000000010001110000000000100000000000010010000000011000001111010000010000000101001000010010010000010101000001000001010001000010110010000001000001010000010011000000001010110001000011001100001110001111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111010000000000000000011100000011000001000001000100001001000010111000010000000000000001001000100000000110010001110000000011001000000001000000110100000011000110000010000001000000000110000000000000100010000010010001010001001000101111100011000110001000000110000000101001000111000010001001010000001000000000000011000101000100001010011000000000100000000100000000010110000001000010000000010110000001111000000000001000000010011010101000100010001001110101010000101000110000010000000001000000000010000000010000000001010110000100000011000000000000000000001000000000001000110011100010001101000010001001001000100000"

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

