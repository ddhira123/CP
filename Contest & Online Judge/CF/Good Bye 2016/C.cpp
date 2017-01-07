#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 25e6;
const int INF = 1e9;

int maxdiv2 = -INF;
int mindiv1 = INF;
int n;

int main() {
	scanf("%d",&n);
	int cur = 0;

	for(int i = 1 ; i <= n ; i++) {
		int c, d;
		scanf("%d %d",&c,&d);

		if(d == 1) {
			mindiv1 = min(mindiv1, cur);
		}
		else {
			maxdiv2 = max(maxdiv2, cur);
		}

		cur += c;
	}

	int ans = INF;

	for(int i = MAGIC ; i >= -MAGIC ; i--) {
		if(i + maxdiv2 <= 1899 && i + mindiv1 >= 1900) {
			ans = i;
			break;
		}
	}

	if(ans == MAGIC) {
		puts("Infinity");
	}
	else if(ans == INF) {
		puts("Impossible");
	}
	else {
		printf("%d\n",ans + cur);
	}
	return 0;
}