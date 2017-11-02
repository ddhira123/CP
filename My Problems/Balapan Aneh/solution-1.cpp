#include <bits/stdc++.h>
#define pb push_back
using namespace std;
bool vis[105][105];
int n, m, k;
vector <int> vc[105];
void dfs(int a, int b){
	vis[a][b] = 1;
	if (b == 100) return;
	for (int i = 0; i < vc[a].size(); i++){
		if (vis[vc[a][i]][b + 1]) continue;
		dfs(vc[a][i], b+1);
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for (;m--;){
		int a,b;
		scanf("%d%d", &a,&b);
		vc[a].pb(b);
		vc[b].pb(a);
	}
	dfs(n, 0);
	for (; k--;){
		int p,a,b,c;
		scanf("%d%d%d%d", &p, &a, &b, &c);
		int ret = 1e9;
		for (int i = 0; i <= 100; i++)
			if (vis[p][i]) ret = min(ret, a * i * i + b * i + c);
		printf("%d\n", ret);
	}
}