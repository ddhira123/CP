#include <bits/stdc++.h>
using namespace std;

const int MX = 200000;
const int N = 100000;

typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back

int dp[MX + 5];
bool vis[MX + 5];
pii arr[N + 5];
vector<pii> adj[MX + 5];
set<int> seen;
int n;

void dfs(int u,int prv){
	vis[u] = 1;
	dp[u] = 0;
	for(pii nex : adj[u]){
		int v = nex.fi;
		int cost = nex.se;
		if(v == prv) continue;
		dfs(v,u);
		dp[u] += max(0,dp[v] + cost);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	while(cin >> n && n > 0){
		int ans = 0;
		for(int i = 0 ; i < n ; i++){
			int cost = 0;
			cin >> arr[i].fi >> arr[i].se >> cost;
			adj[arr[i].fi].pb({arr[i].se,cost});
			adj[arr[i].se].pb({arr[i].fi,cost});
			seen.insert(arr[i].fi);
			seen.insert(arr[i].se);
		}		
		
		for(auto it = seen.begin() ; it != seen.end() ; it++){
			int u = *it;
			if(!vis[u])
				dfs(u,-1);
			ans = max(ans,dp[u]);	
		}
		
		cout << ans << "\n";
		
		for(auto it = seen.begin() ; it != seen.end() ; it++){
			int u = *it;
			adj[u].clear();
			vis[u] = 0;
		}
		
		seen.clear();
	}
	return 0;
}
