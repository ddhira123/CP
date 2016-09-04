#include <bits/stdc++.h>
using namespace std;

const int N = 10000;

vector<int> adj[N + 1];
bool vis[N + 1];
int maxSuffix[N + 1];
int n,m,q;

int DFSSize(int u){
	int res = 1;
	vis[u] = 1;
	for(int v : adj[u])
		if(!vis[v])
			res += DFSSize(v);
	return res;		
}

pair<int,int> FindDiameter(int u,int prv){
	pair<int,int> res = {0,u};
	for(int v : adj[u])
		if(v != prv)
			res = max(res,FindDiameter(v,u));
	res.first++;
	return res;
}

void Process(int u){
	int size = DFSSize(u);
	pair<int,int> temp = FindDiameter(u,-1);
	temp = FindDiameter(temp.second,-1);
	maxSuffix[size] = max(maxSuffix[size],temp.first);
}

int main(){
	int tc;
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++){
		scanf("%d %d",&n,&m);
		
		//reset everything
		for(int i = 1 ; i <= n ; i++){
			vis[i] = 0;
			adj[i].clear();
			maxSuffix[i] = -1;
		}
		
		//read graph
		for(int i = 0 ; i < m ; i++){
			int u,v;
			scanf("%d %d",&u,&v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		
		//compute everything needed
		for(int i = 1 ; i <= n ; i++)
			if(!vis[i])
				Process(i);
		for(int i = n - 1 ; i >= 1 ; i--)
			maxSuffix[i] = max(maxSuffix[i],maxSuffix[i + 1]);		
				
		//solve
		scanf("%d",&q);
		printf("Case %d:\n",t);
		while(q--){
			int query;
			scanf("%d",&query);
			if(query > n || maxSuffix[query] == -1)
				puts("impossible");
			else{
				int maks = maxSuffix[query];
				//printf("%d %d\n",query,maks);
				if(maks >= query)
					printf("%d\n",query - 1);
				else
					printf("%d\n",maks - 1 + 2 * (query - maks));
			}	
		}
	}
	return 0;
}
