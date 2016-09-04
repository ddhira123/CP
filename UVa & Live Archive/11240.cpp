#include <bits/stdc++.h>
using namespace std;

const int N = 30005;

int BIT[2][N];
int n;
int arr[N];

void update(int tipe,int x,int val){
	for(; x <= n + 1 ; x += x & -x)
		BIT[tipe][x] = max(BIT[tipe][x],val);
}

int query(int tipe,int x){
	int res = 0;
	while(x){
		res = max(res,BIT[tipe][x]);
		x -= x & -x;
	}
	return res;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i = 1 ; i <= n ; i++)
			scanf("%d",&arr[i]);
		
		memset(BIT,0,sizeof BIT);
		for(int i = 1 ; i <= n ; i++){
			arr[i]++;
			int dari_bawah = query(0,arr[i] - 1);
			int dari_atas = query(1,n + 1 - arr[i]);
			if(dari_atas)
				update(0,arr[i],dari_atas + 1);
			update(1,n + 2 - arr[i],dari_bawah + 1);	
		}	
		int ans = max(query(0,n + 1),query(1,n + 1));
		printf("%d\n",ans);
	}
	return 0;
}
