#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;
const int N = 5e5 + 5;

int cnt[MX];
int n;

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; i++) {
		int x;
		scanf("%d", &x);
		cnt[x]++;
	}

	int sum = 0;
	int ret = -1;
	for(int i = MX-1 ; i >= 0 ; i--) {
		sum += cnt[i];
		if(sum >= i) {
			ret = i;
			break;
		}
	}

	printf("%d\n", ret);
	return 0;
}