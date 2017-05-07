#include <bits/stdc++.h>
using namespace std;

long long pwr(long long base,int po) {
	long long ret = 1;
	while(po--) ret = ret * base;
	return ret;
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int k,c,s;
		cin >> k >> c >> s;
		printf("Case #%d:",tc);
		if(k == s) {
			long long gap = pwr(k,c - 1);
			for(int i = 0 ; i < k ; i++)
				printf(" %lld",1 + gap * i);
			puts("");
		}
		else puts("IMPOSSIBLE");
	}
	return 0;
}