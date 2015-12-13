with open("Pig.txt", "r") as f:
	size = 0
	rank = 0
	for l in f:
		if l[0] == '>':
			continue
		l = l.strip()
		for s in l:
			if s == 'A':
				rank += 1
			if size == 4800:
				print rank
				exit(1)
			size += 1
	#print size