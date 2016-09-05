#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int a[N], b[N];
int n;

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d",&n);
		for(int i = 1 ; i <= n ; i++)
			scanf("%d",a + i);
		for(int i = 1 ; i <= n ; i++)
			scanf("%d",b + i);

		int ans = 0;
		for(int i = 1 ; i <= n ; i++)
			ans += (a[i] - a[i-1] >= b[i]);
		printf("%d\n",ans);
	}
	return 0;
}