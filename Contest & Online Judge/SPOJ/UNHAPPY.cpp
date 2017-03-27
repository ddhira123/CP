#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 1459;
const int N = 18;

bool happy[MAGIC];
long long dp[N][MAGIC][2];
int digit[N];

int sqr(int x) {
	return x * x;
}

int convert(int x) {
	int res = 0;
	while(x) {
		int lastDigit = x % 10;
		res += sqr(lastDigit);
		x /= 10;
	}
	return res;
}

void generateUnhappy() {
	for(int i = 1 ; i < MAGIC ; i++) {
		set<int> seen;
		int j = i;
		while(!seen.count(j)) {
			seen.insert(j);
			if(j == 1) {
				happy[i] = 1;
				break;
			}
			j = convert(j);
		} 
	}
}

long long solve(int pos,int sum,int udah) {
	if(pos == -1)
		return !happy[sum];
	long long &ret = dp[pos][sum][udah];
	if(ret != -1) return ret;
	ret = 0;
	if(udah) {
		for(int i = 0 ; i <= 9 ; i++)
			ret += solve(pos - 1,sum + sqr(i),udah);
	}
	else {
		for(int i = 0 ; i <= digit[pos] ; i++)
			ret += solve(pos - 1,sum + sqr(i),i < digit[pos]);
	}	
	return ret;
}

long long calc(long long x) {
	if(x <= 1) return 0;
	int len = 0;
	while(x) {
		digit[len] = x % 10LL;
		x /= 10LL;
		len++;
	}
	long long res = 0;
	memset(dp,-1,sizeof dp);
	for(int i = 1 ; i <= digit[len - 1] ; i++)
		res += solve(len - 2,sqr(i),i < digit[len - 1]);
	for(int pos = len - 2 ; pos >= 0 ; pos--)
		for(int i = 1 ; i <= 9 ; i++)
			res += solve(pos - 1,sqr(i),1);
	return res;			
}

int main() {
	generateUnhappy();
	long long a,b;
	while(scanf("%lld %lld",&a,&b) == 2 && (a | b) > 0) {
		printf("%lld\n",calc(b) - calc(a - 1));
	}
	return 0;
}