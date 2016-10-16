#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second

priority_queue<pair<LL,pii>> pq;
set<pii> st;

LL psum[N];
int n;

int main() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%lld",psum + i);
		psum[i] += psum[i-1];
	}
	pq.push({psum[n],{1,n}});
	st.insert({1,n});
	for(int i = 1 ; i < n ; i++) {
		int x; scanf("%d",&x);
		pii temp = {x+1,-1};
		auto it = st.lower_bound(temp);
		it--;
		pii now = *it;

		st.erase(now);
		if(now.fi != x) {
			st.insert({now.fi,x-1});
			pq.push({psum[x-1]-psum[now.fi-1],{now.fi,x-1}});
		}
		if(now.se != x) {
			st.insert({x+1,now.se});
			pq.push({psum[now.se]-psum[x],{x+1,now.se}});
		}

		while(!st.count(pq.top().se)) pq.pop();
		printf("%lld\n",pq.top().fi);
	}
	puts("0");
	return 0;
}