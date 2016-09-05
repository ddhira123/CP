#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int BIT[N];
int arr[N];
int n;

void update(int x,int val) {
	for(; x <= n ; x += x & -x)
		BIT[x] += val;
}

int query(int x) {
	int ret = 0;
	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}
	return ret;
}

int query(int l,int r) {
	return query(r) - query(l-1);
}

void reset() {
	for(int i = 1 ; i <= n ; i++) {
		BIT[i] = 0;
		arr[i] = 0;
	}
}

int main() {
	int tc = 0;

	scanf("%d",&n);
	while(n > 0) {
		if(tc) puts("");
		printf("Case %d:\n",++tc);

		reset();
		for(int i = 1 ; i <= n ; i++) {
			scanf("%d",arr + i);
			update(i,arr[i]);
		}

		while(1) {
			char opt[5];
			scanf("%s",opt);

			if(opt[0] == 'E')
				break;

			int a, b;
			scanf("%d %d",&a,&b);

			if(opt[0] == 'M')
				printf("%d\n",query(a,b));
			else {
				update(a,b - arr[a]);
				arr[a] = b;
			}
		}

		scanf("%d",&n);
	}
	return 0;
}