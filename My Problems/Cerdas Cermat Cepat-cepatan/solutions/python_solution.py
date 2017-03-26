MOD = 1000000007
dp = {}

def solve(x):
	if x in dp:
		return dp.get(x)

	ret = 0
	i = 2
	isPrime = True

	while i * i <= x:
		if x % i == 0:
			isPrime = False
			j = x / i
			if i != j:
				ret = (ret + solve(i) * solve(j)) % MOD
			else:
				same = solve(i)
				diff = same * (same-1) / 2
				ret = (ret + same + diff) % MOD
		i += 1

	if isPrime:
		ret = 1

	dp[x] = ret
	return ret

n = int(input())
print(int(solve(n)))