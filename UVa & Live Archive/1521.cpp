#include <bits/stdc++.h>
using namespace std;

const int MX = 10000;

bool flag[MX + 5];
vector<int> prime;
int n;

void sieve(){
	for(int i = 2 ; i <= MX ; i++)
		if(!flag[i]){
			prime.push_back(i);
			for(int j = i ; j <= MX ; j += i)
				flag[j] = 1;
		}
}

int main(){
	sieve();
	while(scanf("%d",&n) == 1){
		int tail = upper_bound(prime.begin(),prime.end(),n) - prime.begin();
		tail--;
		int head = 0;
		int ans = 0;
		while(head <= tail){
			ans++;
			int mul = prime[tail];
			tail--;
			while(head <= tail && mul * prime[head] <= n){
				mul *= prime[head];
				head++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
