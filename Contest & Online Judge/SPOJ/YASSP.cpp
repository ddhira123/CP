#include <bits/stdc++.h>
using namespace std;

const int N = 50;
const int MAXX = 10000;

long long mask[N + 1][N * MAXX + 1];
int psum[N + 1];
int arr[N + 1];
int n,t;

void init() {
	memset(mask,-1,sizeof mask);
}

void read() {
	scanf("%d",&n);
	for(int i = 0 ; i < n ; i++)
		scanf("%d",arr + i);
}

void solve() {
	sort(arr,arr + n);
	psum[0] = arr[0];
	for(int i = 1 ; i < n ; i++)
		psum[i] = arr[i] + psum[i - 1];
	mask[0][0] = 0;
	for(int i = 0 ; i < n ; i++) {
		int lmt = (i == 0) ? 0 : psum[i - 1];
		mask[i + 1][arr[i]] = 1;
		for(int j = 0 ; j <= lmt ; j++)
			if(mask[i][j] != -1) {
				for(long long mul = 0 ; mul < 2 ; mul++) {
					int nxt = j + mul * arr[i];
					mask[i + 1][nxt] = max(mask[i + 1][nxt],0ll);
					mask[i + 1][nxt] |= (mask[i][j] << mul);
				}
				//printf("i %d j %d mask %lld\n",i,j,mask[i][j]);
				mask[i][j] = -1;
			}
	}		
	int ans = -1;
	int best = -1;
	
	for(int i = 0 ; i <= psum[n - 1] ; i++) 
		if(mask[n][i] != -1) {
			//printf("i %d mask %lld\n",i,mask[n][i]);
			int bit = __builtin_popcountll(mask[n][i]);
			
			if(bit > best) {
				ans = i;
				best = bit;
			}
			
			mask[n][i] = -1;
		}			
	
	printf("%d %d\n",best,ans);	
}

int main() {
	init();
	scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		solve();
	}
	return 0;
}