#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int K = 1e5 + 5;

typedef pair<int,int> pii;
#define fi first
#define se second

vector<pair<int,pair<int,int>>> v[K+1];
int n, m;

vector<pii> d[K+1];
int pr[K+1];

void prec() {
	for(int i = 2 ; i <= K ; i++)
		if(pr[i] == 0)
			for(int j = i ; j <= K ; j += i)
				pr[j] = i;

	for(int i = 1 ; i <= K ; i++) {
		int x = i;
		while(x != 1) {
			int lst = pr[x];
			int mul = 1;
			while(pr[x] == lst) {
				mul *= lst;
				x /= lst;
			}
			d[i].push_back({lst,mul});
		}
	}
}

vector<pair<pii,int>> occ[K+1];

void add(int mod,int x) {
	for(pii y : d[x]) {
		bool ada = 0;
		pii tmp = {mod % y.second,y.second};
		for(int i = 0 ; i < occ[y.first].size() ; i++)
			if(occ[y.first][i].first == tmp) {
				ada = 1;
				occ[y.first][i].second++;
				break;
			}
		if(!ada ){
			occ[y.first].push_back({tmp,1});
		}
	}
}

void remove(int mod,int x) {
	for(pii y : d[x]) {
		bool ada = 0;
		pii tmp = {mod % y.second,y.second};
		for(int i = 0 ; i < occ[y.first].size() ; i++)
			if(occ[y.first][i].first == tmp) {
				occ[y.first][i].second--;
				if(occ[y.first][i].second == 0) {
					occ[y.first].erase(occ[y.first].begin()+i);
				}
				break;
			}
	}
}

bool check(int mod,int x) {
	for(pii y : d[x]) {
		for(int i = 0 ; i < occ[y.first].size() ; i++) {
			int mins = min(y.second,occ[y.first][i].first.second);
			if(mod % mins != occ[y.first][i].first.first % mins)
				return 0;
		}
	}
	return 1;
}

int main() {
	prec();
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= n ; i++) {
		int k; scanf("%d",&k);
		for(int j = 0 ; j < k ; j++) {
			int x; scanf("%d",&x);
			v[x].push_back({i,{j,k}});
		}
	}
	for(int i = 1 ; i <= m ; i++) {
		int l = 0;
		int ans = 0;
		for(int j = 0 ; j < v[i].size() ; j++) {
			if(j > 0 && v[i][j].first != v[i][j-1].first+1) {
				while(l < j) {
					int mod = v[i][l].second.first;
					int x = v[i][l].second.second;
					remove(mod,x);
					l++;
				}
			}
			while(!check(v[i][j].second.first,v[i][j].second.second)) {
				int mod = v[i][l].second.first;
				int x = v[i][l].second.second;
				remove(mod,x);
				l++;
			}
			add(v[i][j].second.first,v[i][j].second.second);
			ans = max(ans,j-l+1);
		}
		while(l < v[i].size()) {
			int mod = v[i][l].second.first;
			int x = v[i][l].second.second;
			remove(mod,x);
			l++;
		}
		printf("%d\n",ans);
	}
	return 0;
}