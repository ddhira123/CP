def pwr(x) :
	y = 1
	base = 2
	while x > 0 :
		if x % 2 == 1 :
			y = (y * base) % 1000000007
		base = (base * base) % 1000000007
		x //= 2
	return y					

n = int(input())
print (pwr(n))
