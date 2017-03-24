#include <bits/stdc++.h>
using namespace std;

int main() {
	int ans = 0;
	int n; scanf("%d",&n);
	for(int i = 0 ; i < n ; i++) {
		int x; scanf("%d", &x);
		ans ^= x;
	}
	printf("%d\n",ans);
	return 0;
}