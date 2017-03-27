fact = []
fact.append(1)
for i in range (1,101) :
	fact.append(fact[i - 1] * i)
tc = int(input())
for t in range(0,tc) : 
	n = int(input())
	print (fact[n])	