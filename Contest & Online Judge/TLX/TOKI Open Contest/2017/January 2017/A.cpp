#include <bits/stdc++.h>
using namespace std;

int main() {
	int lst = 0;
	int n;
	int sum = 0;
	int ans = 0;
	scanf("%d", &n);

	for(int i = 1 ; i <= n ; i++) {
		int a, b;
		scanf("%d %d",&a,&b);
		sum -= b;

		if(sum == 0) {
			ans = max(ans, i-lst);
			lst = i;
		}

		sum += a;
	}

	printf("%d\n",ans * 10);
	return 0;
}