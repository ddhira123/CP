#include <bits/stdc++.h>
using namespace std;

int deg[200005];
int nex[200005];
int n;

void BFS() {
	queue<int> q;
	for(int i = 1 ; i <= n ; i++)
		if(deg[i] == 0)
			q.push(i);

	while(!q.empty()) {
		int now = q.front();
		q.pop();
		deg[nex[now]]--;
		if(deg[nex[now]] == 0)
			q.push(nex[now]);
	}	
}

int destroy(int st) {
	int now = st;
	int sz = 0;
	do {
		deg[now]--;
		now = nex[now];
		sz++;
	}while(now != st);
	return sz;
}

void solve() {
	BFS();
	int cycle = 0;
	vector<pair<int,int> > v;
	for(int i = 1 ; i <= n ; i++) 
		if(deg[i] == 1) {
			v.push_back({destroy(i),i});
			cycle++;
		}

	sort(v.begin(),v.end());
	int en = v[0].second;
	if(v[0].first == 1)
		cycle--;
	for(int i = 0 ; i < v.size() ; i++)
		nex[v[i].second] = en;

	printf("%d\n",cycle);
	for(int i = 1 ; i <= n ; i++)
		printf("%d ",nex[i]);	
}

int main() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",nex + i);
		deg[nex[i]]++;
	}
	solve();
	return 0;
}