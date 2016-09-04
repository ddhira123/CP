#include <bits/stdc++.h>
using namespace std;

const int N = 100000;
const int K = 20;
const int MOD = 10007;

int stree[3 * N + 5][K + 1];
int a[N + 5], b[N + 5];
int n,k,q;


void merge(int id){
	int chld = id << 1;
	int tot = 0;
	for(int i = 0 ; i <= k ; i++)
		stree[id][i] = 0;
	for(int i = 0 ; i <= k ; i++) {
		for(int j = i ; j < k ; j++)
			stree[id][j] = (stree[id][j] + stree[chld][i] * stree[chld + 1][j - i]) % MOD;
		tot = tot + stree[chld + 1][k - i];
		stree[id][k] = (stree[id][k] + (tot * stree[chld][i])) % MOD;
	}
}

void build(int id,int l,int r){
	if(l == r) {
		stree[id][0] = b[l];
		stree[id][1] = a[l];
	}
	else {
		int mid = (l + r) / 2;
		int chld = id << 1;
		build(chld,l,mid);
		build(chld + 1,mid + 1,r);
		merge(id);
	}
}

void update(int id,int l,int r,int x){
	if(l == r) {
		stree[id][0] = b[l];
		stree[id][1] = a[l];
	}
	else {
		int mid = (l + r) / 2;
		int chld = id << 1;
		if(x <= mid)	update(chld,l,mid,x);
		else			update(chld + 1,mid + 1,r,x);
		merge(id);		
	}
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",&a[i]);
		a[i] %= MOD;
	}
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",&b[i]);
		b[i] %= MOD;
	}	
	build(1,1,n);
	scanf("%d",&q);
	for(int i = 0 ; i < q ; i++) {
		int id,x,y;
		scanf("%d %d %d",&id,&x,&y);
		a[id] = x % MOD;
		b[id] = y % MOD;
		update(1,1,n,id);
		printf("%d\n",stree[1][k]);
	}
	return 0;
}
