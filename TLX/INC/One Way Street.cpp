#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int dist[N][N];
int n,m,q;
int tc;

void warshall(){
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			for(int k = 1 ; k <= n ; k++)
				dist[j][k] = min(dist[j][k],dist[j][i] + dist[i][k]);
}

int main(){
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++){
		scanf("%d %d",&n,&m);
		for(int i = 1 ; i <= n ; i++){
			for(int j = 1 ; j <= n ; j++)
				dist[i][j] = (int)1e9;
			dist[i][i] = 0;	
		}	
		while(m--){
			int u,v;
			scanf("%d %d",&u,&v);
			dist[u][v] = 0;
			dist[v][u] = min(dist[v][u],1);
		}
		warshall();
		scanf("%d",&q);
		printf("Case #%d:\n",t);
		while(q--){
			int u,v;
			scanf("%d %d",&u,&v);
			printf("%d\n",dist[u][v] == (int)1e9 ? -1 : dist[u][v]);
		}
	}
	return 0;
}
