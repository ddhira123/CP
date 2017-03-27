#include <bits/stdc++.h>
using namespace std;

const int N = 100000;

int arr[N + 5];
long long add[2 * N + 5];
int n,m,k;

bool check(int x) {
	int sisa = k;
	memset(add,0,sizeof add);
	long long cumulative = 0;
	for(int i = 0 ; i < n && sisa >= 0 ; i++) {
		cumulative += add[i];
		long long use = max(0LL,x - (arr[i] + cumulative));
		add[i + m] = -use;
		cumulative += use;
		sisa -= use;
	}
	return sisa >= 0;
}

int special() {
	int mins = arr[0];
	for(int i = 1 ; i < n ; i++)
		mins = min(mins,arr[i]);
	return mins;	
}

int main() {
	int t;
	scanf("%d",&t);
	
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d %d %d",&n,&m,&k);
		for(int i = 0 ; i < n ; i++)
			scanf("%d",&arr[i]);
		
		int ans;
		if(m == 0)
			ans = special();
		else {
			long long lo = 0;
			long long hi = (int)2e9 + 5;
			
			while(lo < hi) {
				long long mid = (lo + hi + 1) / 2LL;
				
				if(check(mid))
					lo = mid;
				else
					hi = mid - 1;	
			}
			
			ans = lo;
		}
		
		printf("%d\n",ans);		
	}
	return 0;
}