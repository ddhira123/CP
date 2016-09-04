#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;

int getMask(long long x) {
	int ret = 0;
	while(x) {
		ret |= (1 << (x%10));
		x /= 10;
	}
	return ret;
}

int getAns(int x) {
	int mask = 0;
	for(long long i = x ; ; i += x) {
		mask |= getMask(i);
		if(mask == 1023)
			return i;
	}
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int n; scanf("%d",&n);
		printf("Case #%d: ",tc);
		if(n == 0) puts("INSOMNIA");
		else printf("%d\n",getAns(n));
	}
	return 0;
}