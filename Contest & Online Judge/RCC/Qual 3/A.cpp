#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int a, b, c;
		scanf("%d %d %d",&a,&b,&c);
		long long area = (long long)a * b;
		long long c2 = (long long)c * c;

		long long sisa = max(1LL,area / c2);
		long long best = 4e18;
		long long ans;
		for(int i = 0 ; i < 2 ; i++) {
			long long diff = abs(area - c2*(sisa + i));
			if(diff <= best) {
				best = diff;
				ans = c2*(sisa + i);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}