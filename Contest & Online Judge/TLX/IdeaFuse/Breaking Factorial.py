def get(a,x) :
	lo = 0
	hi = len(a) - 1
	while lo < hi :
		mid = (lo + hi) // 2
		if a[mid] > x :
			hi = mid
		else :
			lo = mid + 1
	#print (lo,a[lo])		
	return lo - 1

sieve = []
for i in range (1,60005) :
	sieve.append(0)
prime = []
for i in range (2,60001) :
	if sieve[i] == 0 :
		prime.append(i)
		j = i * i
		while j <= 60000 :
			sieve[j] = 1
			j += i					

tc = int(input())
for t in range (1,tc + 1) :
	n = int(input())
	print ("Case #" + str(t) + ": " + str(prime[get(prime,n)]));	
