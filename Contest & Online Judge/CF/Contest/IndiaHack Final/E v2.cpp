#include <bits/stdc++.h>
using namespace std;

const int N = 300005;

typedef long long LL;
typedef pair<int,int> pii;

#define fi first
#define se second
#define pb push_back

int pset[N];
int sial[N];
vector<int> v[N];
set<int> s;
bool mampus[N];
bool udah[N];
int n,m,k;

int finds(int x) {
	return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void uni(int x,int y) {
	//printf("x %d y %d\n",x,y);
	x = finds(x);
	y = finds(y);
	//printf("xx %d yy %d\n",x,y);
	pset[y] += pset[x];
	pset[x] = y;
}

void dfs(int x) {
	s.erase(x);
	int last = 1;
	while(s.upper_bound(last) != s.end()) {
		auto it = s.upper_bound(last);
		int y = *it;
		if(!binary_search(v[x].begin(),v[x].end(),y) && finds(x) != finds(y)) {
			uni(x,y);
			dfs(y);
		}
		last = y;
	}
}

void init() {
	for(int i = 1 ; i <= n ; i++) {
		pset[i] = -1;
		s.insert(i);
		sort(v[i].begin(),v[i].end());
	}
}

void read() {
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1 ; i <= m ; i++) {
		int a,b;
		scanf("%d %d",&a,&b);
		if(a == 1)
			mampus[b] = 1;
		else if(b == 1)
			mampus[a] = 1;
		else {
			v[a].pb(b);
			v[b].pb(a);
		}
	}
}

void solve() {
	init();
	s.erase(1);
	for(int i = 2 ; i <= n ; i++) {
		if(s.count(i)) 
			dfs(i);
	}	

	//puts("a");

	for(int i = 2 ; i <= n ; i++)
		if(mampus[i])
			sial[finds(i)]++;

	int bisa = 0;
	int tree = 0;
	for(int i = 2 ; i <= n ; i++)
		if(finds(i) == i) {
			if(pset[i] + sial[i] == 0) {
				bisa = -1;
				break;
			}
			//printf("%d %d\n",i,-pset[i] - sial[i]);
			bisa += (-pset[i] - sial[i]);
			tree++;
		}

	printf("%s\n",bisa >= k && tree <= k ? "possible" : "impossible");		
}

int main() {
	read();
	solve();
	return 0;
}