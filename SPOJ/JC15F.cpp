#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1000;
const int N2 = N * N;
const LL MOD = (LL)1e9 + 7;

int fact[N2 + 5];
int inve[N2 + 5];
int arr[N + 5];
int ways[N + 5];
int n;

int modPow(LL base,int po) {
	LL ret = 1;
	
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	
	return ret;
}

int getInverse(int x,int flag) {
	if(flag == 0) { // x^-1 % MOD
		return modPow(x,MOD - 2);
	}
	// (x!)^-1 % MOD
	if(inve[x] != -1) return inve[x];
	return inve[x] = modPow(fact[x],MOD - 2);
}

void precompute() {
	fact[0] = 1;
	inve[0] = 1;
	for(int i = 1 ; i <= N2 ; i++) {
		fact[i] = ((LL)fact[i - 1] * i) % MOD;
		inve[i] = -1;
	}
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",arr + i);
}

void solve() {
	int sum = 0;
	int fpb = arr[1];
	
	for(int i = 1 ; i <= n ; i++) {
		sum += arr[i];
		fpb = __gcd(fpb,arr[i]);
	}
	
	for(int i = fpb ; i >= 1 ; i--)
		if(fpb % i == 0) {
			ways[i] = fact[sum / i];
			
			for(int j = 1 ; j <= n ; j++) {
				int inCycle = arr[j] / i;
				ways[i] = ((LL)ways[i] * getInverse(inCycle,1)) % MOD;
			}
			
			// after this loop, ways will be exactly using i cycle, no i*smth cycle
			for(int j = i + i ; j <= fpb ; j += i)
				ways[i] = (ways[i] + MOD - ways[j]) % MOD;
			
		}
	
	int ans = 0;
	
	for(int i = fpb ; i >= 1 ; i--) 
		if(fpb % i == 0 && ways[i] > 0) {
		
			int lengthOfCycle = sum / i;
			int numOfWays = ((LL)ways[i] * getInverse(lengthOfCycle,0)) % MOD;
			
			ans = (ans + numOfWays) % MOD;
			
			//printf("%d ways %d\n",lengthOfCycle,numOfWays);
		}
	
	printf("%d\n",ans);	
}

int main() {
	precompute();
	read();
	solve();
	return 0;
}