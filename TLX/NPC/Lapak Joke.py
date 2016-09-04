
n, m = map(int, input().split())
arr = [int(i) for i in input().split()]
k = int(input())

arr.sort()
ans = 0
for i in range (0,min(k,n)) :
	ans += arr[i]
if k > n :
	ans -= m * (k - n)
if ans < 0 :
	print ("Joke Rapopo")
else :
	print (ans)			
