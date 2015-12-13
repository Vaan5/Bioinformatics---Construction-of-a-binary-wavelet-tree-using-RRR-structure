with open("HIV.txt", "r") as f:
	with open("testHIV.txt", "w") as out:
		index = 0
		rank = 0
		for l in f:
			if l[0] == '>':
				continue
			l = l.strip()
			for s in l:
				if s == 'T':
					rank += 1
				# out.write("{}\n".format(rank))
				out.write('Assert::AreEqual((uint64_t){}, tree.rank(\'T\', {}), L"Wavelet tree rank test", LINE_INFO());\n'.format(rank, index))
				index += 1