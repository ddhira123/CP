tc = int(input())

for t in range (1,tc + 1) :
	n = int(input())
	maks = -1
	mins = 1000000
	for x in input().split() :
		maks = max(maks,int(x))
		mins = min(mins,int(x))
	print ("Case #" + str(t) + ": " + str(maks - mins))	
