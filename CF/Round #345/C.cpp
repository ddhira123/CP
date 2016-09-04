#include <bits/stdc++.h>
using namespace std;

const int N = (int)1e6 + 5;

vector<int> arr[N];
vector<int> ans[N];
vector<pair<int,pair<int,int> > > proc;
int row[N], col[N];
bool vis[N];
vector<pair<int,int> > adj[N];
int num[N];
int n,m;

int getID(int r,int c) {
	return r * m + c;
}

int dfs(int r,int c) {
	int idx = getID(r,c);
	if(vis[idx]) return 0;
	int ret = max(row[r],col[c]);
	vis[idx] = 1;

	for(pair<int,int> nex : adj[idx]) {
		ret = max(ret,dfs(nex.first,nex.second));
	}

	return ret;
}

void fillVal(int r,int c,int val) {
	int idx = getID(r,c);
	if(ans[r][c]) return;
	ans[r][c] = val;
	row[r] = max(row[r],val);
	col[c] = max(col[c],val);

	for(pair<int,int> nex : adj[idx]) {
		fillVal(nex.first,nex.second,val);
	}
}

bool cmp(pair<int,pair<int,int> > a,pair<int,pair<int,int> > b) {
	return a.second.second < b.second.second;
}

void add(pair<int,int> a,pair<int,int> b) {
	adj[getID(a.first,a.second)].push_back(b);
	adj[getID(b.first,b.second)].push_back(a);
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < n ; i++) {
		arr[i].resize(m,0);
		ans[i].resize(m,0);
		for(int j = 0 ; j < m ; j++) {
			scanf("%d",&arr[i][j]);
			proc.push_back({arr[i][j],{i,j}});
		}
	}

	sort(proc.begin(),proc.end());

	for(int i = 0 ; i < proc.size() ; ) {
		int j = i;

		while(j < proc.size() && proc[i].first == proc[j].first)
			j++;

		for(int k = i + 1 ; k < j ; k++) {
			if(proc[k - 1].second.first == proc[k].second.first) {
				add(proc[k - 1].second,proc[k].second);
			}
		}

		sort(proc.begin() + i,proc.begin() + j,cmp);
		for(int k = i + 1 ; k < j ; k++) {
			if(proc[k - 1].second.second == proc[k].second.second) {
				add(proc[k - 1].second,proc[k].second);
			}
		}

		for(int k = i ; k < j ; k++) {
			//printf("%d\n",proc[k].first);
			int idx = getID(proc[k].second.first,proc[k].second.second);
			if(!vis[idx]) {
				int ret = dfs(proc[k].second.first,proc[k].second.second);
				ret++;
				fillVal(proc[k].second.first,proc[k].second.second,ret);
			}
		}

		//printf("haha %d %d\n",i,j);
		i = j;
	}

	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < m - 1 ; j++)
			printf("%d ",ans[i][j]);
		printf("%d\n",ans[i][m - 1]);
	}
	return 0;
}