#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	for (scanf("%d", &t); t--; ){
		int n;
		long long ans = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++){
			long long l , r;
			scanf("%lld%lld", &l, &r);
			ans+=(r - l);
		}
		printf("%lld.%lld\n", ans/2, (ans%2) * 5);
	}
}