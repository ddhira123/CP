#include <bits/stdc++.h>
using namespace std;

const int SQRT = 400;
const int N = 2e5 + 5;

vector<int> chld[N];
int opt[N], Y[N], NUM[N]; 
int in[N], ot[N];
int dfsCount;
int n = 1;
int q;

long long BIT[N];
long long maks[N];

vector<int> heavy;

bool isHeavy(int idx) {
	return chld[idx].size() >= SQRT;
}

void update(int x,int val) {
	for(; x <= n ; x += x & -x)
		BIT[x] += val;
}

long long query(int x) {
	long long ret = 0;
	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}
	return ret;
}

long long query(int a,int b) {
	return query(b) - query(a-1);
}

void dfs(int now) {
	in[now] = ++dfsCount;
	for(int nex : chld[now])
		dfs(nex);
	ot[now] = dfsCount;
}

int getAncestor(int par,int x) {
	int lo = 0, hi = chld[par].size()-1;
	while(lo < hi) {
		int mid = (lo + hi + 1) / 2;
		if(in[chld[par][mid]] > in[x])
			hi = mid-1;
		else
			lo = mid;
	}
	return chld[par][lo];
}

void updateWorker(int x,int val) {
	update(in[x],val);

	for(int heavyNode : heavy)
		if(in[heavyNode] <= in[x] && in[x] <= ot[heavyNode]) {
			int ancestor = getAncestor(heavyNode,x);
			maks[heavyNode] = max(maks[heavyNode], query(in[ancestor],ot[ancestor]));
		}
}

long long queryWorker(int x) {
	if(isHeavy(x))
		return maks[x];
	long long ret = 0;
	for(int nex : chld[x])
		ret = max(ret,query(in[nex],ot[nex]));
	return ret;
}

void read() {
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i++) {
		scanf("%d",opt + i);
		if(opt[i] == 1) {
			int par;
			scanf("%d %d",&par,Y + i);
			NUM[i] = ++n;
			chld[par].push_back(n);
		}
		else {
			scanf("%d",Y + i);
		}
	}
}

void prepare() {
	dfs(1);
	for(int i = 1 ; i <= n ; i++)
		if(isHeavy(i))
			heavy.push_back(i);
}

void solve() {
	for(int i = 1 ; i <= q ; i++) {
		if(opt[i] == 1) {
			updateWorker(NUM[i],Y[i]);
		}
		else {
			printf("%lld\n",queryWorker(Y[i]));
		}
	}
}

int main() {
	read();
	prepare();
	solve();
	return 0;
}