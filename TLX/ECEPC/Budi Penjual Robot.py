
fibo = []
fibo.append(1)
fibo.append(1)
for x in range (2,93) :
	fibo.append(fibo[x - 1] + fibo[x - 2])

tc = int(input())
for t in range (1,tc + 1) :
	n = int(input())
	arr = [int(i) for i in input().split()]
	ans = 0
	for i in range (0,n) :
		ans += fibo[arr[i]]
	print ("Case #" + str(t) + ": " + str(ans))		
