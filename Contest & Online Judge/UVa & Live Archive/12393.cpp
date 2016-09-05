#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

typedef pair<int,int> pii;
#define fi first
#define se second

pii dek[2 * N + 5];
int psum[N + 5];
int arr[N + 5];
int l,r;
int n;

void add(pii x){
	while(r > l && dek[r - 1].fi >= x.fi)
		r--;
	dek[r++] = x;	
}

int main(){
	while(scanf("%d",&n) == 1 && n > 0){
		l = r = 0;
		for(int i = 1 ; i <= n ; i++){
			scanf("%d",&arr[i]);
			psum[i] = arr[i] + psum[i - 1];
		}
		int sum = 0;
		for(int i = 1 ; i <= n ; i++){
			sum += arr[i];
			add({sum,i});
		}
		int ans = 0;
		for(int i = n + 1 ; i <= 2 * n ; i++){
			while(dek[l].se < i - n) l++;
			if(dek[l].fi - psum[i - n - 1] >= 0)
				ans++;
			sum += arr[i - n];
			add({sum,i});	
		}
		printf("%d\n",ans);
	}
	return 0;
}
