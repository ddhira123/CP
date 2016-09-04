#include <bits/stdc++.h> 
using namespace std;

const int MX = 1000005;

int papa[MX];
pair<int, int> ans[MX];

int main(){
	memset(papa,-1,sizeof papa);
	int m;
	scanf("%d",&m);
	for(int i = 0 ; i < m ; i++){
		int idx,n;
		scanf("%d %d",&idx,&n);
		for(int j = 0 ; j < n ; j++){
			int chld;
			scanf("%d",&chld);
			papa[chld] = idx;
		}
	}
	int q;
	scanf("%d",&q);
	for(int i = 0 ; i < q ; i++){
		int opt;
		scanf("%d",&opt);
		if(opt == -1){
			int u;
			scanf("%d",&u);
			printf("%d %d\n",ans[u].first,ans[u].second);
		}
		else{
			int v1,v2;
			scanf("%d %d",&v1,&v2);
			while(opt != -1){
				ans[opt].first += v1;
				ans[opt].second += v2;
				opt = papa[opt];
			}
		}
	}
	return 0;
}
