#include <bits/stdc++.h>
using namespace std;

bool can(int n,long long k) {
	if(n == 1) {
		return k == 1;
	}
	if(n % 2 == 0) {
		return k <= 2;
	}
	int idx = n / 2 + 1;
	long long val = idx + 4;
	for(int i = 0 ; i < idx - 2 && val < k ; i++)
		val *= 2;
	//printf("%lld\n",val);
	return val >= k;
}

int ans[1000005];
bool udah[1000005];
long long cnt = 0;

void dfs(int pos,int en) {
	if(pos > en) {
		cnt--;
		if(cnt == 0) {
			for(int i = 1 ; i <= en ; i++)
				printf("%d%c",ans[i],i == en ? '\n' : ' ');
		}
	}
	else {
		for(int i = 1 ; ans[pos - 1] - i >= en / 2 && cnt > 0 ; i++)
			if(!udah[i]) {
				ans[pos] = i;
				udah[i] = 1;
				dfs(pos + 1,en);
				udah[i] = 0;
			}
		for(int i = ans[pos - 1] + en / 2 ; i <= en && cnt > 0 ; i++)
			if(!udah[i]) {
				ans[pos] = i;
				udah[i] = 1;
				dfs(pos + 1,en);
				udah[i] = 0;
			}			
	}
}

void solve(int n,long long k) {
	if (!can(n,k)) {
		puts("-1");
		return;
	}
	if(n == 1) {
		puts("1");
	}
	else if(n % 2 == 0) {
		for(int i = 1 ; i <= n ; i += 2) {
			ans[i] = n / 2 - (i+1) / 2 + 1;
			ans[i + 1] = n - (i+1) / 2 + 1;
		}
		if(k == 2) reverse(ans + 1,ans + n + 1);
		for(int i = 1 ; i <= n ; i++)
			printf("%d%c",ans[i],i == n ? '\n' : ' ');
	}
	else {
		cnt = k;
		for(int i = 1 ; i <= n && cnt > 0 ; i++) {
			udah[i] = 1;
			ans[1] = i;
			dfs(2,n);
			udah[i] = 0;
		}
	}
}

int main() {
	int n,t;
	long long k;
	scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d %lld",&n,&k);
		solve(n,k);
	}
	return 0;
}