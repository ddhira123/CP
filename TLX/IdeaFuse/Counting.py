tc = int(input())

for t in range (1,tc + 1) :
	n, m = map(int,input().split())
	diff = m - n
	if (diff % 12 == 0) & (diff >= 0) :
		print ("Case #" + str(t) + ": " + str(n + 7 * diff // 12)) 
	else :
		print ("Case #" + str(t) + ": impossible")	
