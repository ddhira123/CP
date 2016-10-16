// aimed for 40% only
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int a[N];
int p[N];
int v[N];
int n;

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",a + i);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",p + i);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",v + i);
}

void solve() {
	set<pair<int,int>> s;
	for(int i = 1; i <= n ;i++)
		s.insert({v[i],i});
	int ans = 0;
	for(int i = 1 ; i <= n ; i++) {
		pair<int,int> temp = {p[i],1e9};
		auto it = s.upper_bound(temp);
		ans++;
		if(it == s.end()) {
			ans--;
			it = s.begin();
		}
		s.erase(it);
	}
	printf("%d\n",ans);
}

int main() {
	read();
	solve();
	return 0;
}