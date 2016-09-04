#include <bits/stdc++.h>
using namespace std;

const int N = 10000;
const int K = 100;

bool can[N + 1][K + 1];
vector<int> chld[N + 1];
int arr[N + 1];
int n;

bool cmp(int a,int b) {
	return arr[a] < arr[b];
}

void dfs(int v) {
	sort(chld[v].begin(),chld[v].end(),cmp);
	for(int nex : chld[v]) {
		dfs(nex);
	}
	can[v][arr[v]] = 1;
	for(int i = 0 ; i < chld[v].size() ; i++) {
		int nex = chld[v][i];
		if(arr[nex] > arr[v])
			for(int j = arr[v] ; j < arr[nex] ; j++)
				if(can[v][j] && can[nex][j + 1]) {
					for(int k = arr[nex] ; k <= K ; k++)
						can[v][k] |= can[nex][k];
					break;
				}
	}
	for(int i = (int)chld[v].size() - 1 ; i >= 0 ; i--) {
		int nex = chld[v][i];
		if(arr[nex] < arr[v])
			for(int j = arr[v] ; j > arr[nex] ; j--)
				if(can[v][j] && can[nex][j - 1]) {
					for(int k = arr[nex] ; k >= 1 ; k--)
						can[v][k] |= can[nex][k];
					break;
				}
	}	
}


int main(){
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",&arr[i]);
	for(int i = 1 ; i < n ; i++) {
		int u,v;
		scanf("%d %d",&u,&v);
		chld[u].push_back(v);
	}	
	dfs(1);
	int kiri = 0;
	int kanan = 0;
	for(int i = 1 ; i <= arr[1] ; i++)
		kiri += can[1][i];
	for(int i = arr[1] ; i <= K ; i++)
		kanan += can[1][i];	
	printf("%d\n",kiri * kanan);	
	return 0;
}
