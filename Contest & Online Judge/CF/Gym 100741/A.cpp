#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
const int MAXMOD = 11;

long long BIT[MAXMOD][N];
long long arr[N];
int n, q, m;

void update(int id, int x, long long val) {
	for(; x <= n ; x += x & -x)
		BIT[id][x] += val;
}

long long query(int id, int x) {
	long long ret = 0;
	while(x) {
		ret += BIT[id][x];
		x -= x & -x;
	}
	return ret;
}

long long add(int pos, int x) {
	update(arr[pos] % m, pos, -arr[pos]);
	arr[pos] += x;
	update(arr[pos] % m, pos, arr[pos]);
	return arr[pos];
}

long long sub(int pos, int x) {
	if(arr[pos] < x) {
		return arr[pos];
	}

	update(arr[pos] % m, pos, -arr[pos]);
	arr[pos] -= x;
	update(arr[pos] % m, pos, arr[pos]);
	return arr[pos];
}

int main() {
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%lld", arr + i);
		update(arr[i] % m, i, arr[i]);
	}
	scanf("%d",&q);

	for(int i = 0 ; i < q ; i++) {
		char s[5];
		scanf("%s", s);

		long long ret;
		if(s[0] == 's') {
			int p, r, mod;
			scanf("%d %d %d",&p,&r,&mod);
			ret = query(mod, r) - query(mod, p-1);
		} else {
			int p, r;
			scanf("%d %d",&p,&r);
			if(s[0] == '+') {
				ret = add(p, r);
			} else {
				ret = sub(p, r);
			}
		}

		printf("%lld\n", ret);
	}
	return 0;
}