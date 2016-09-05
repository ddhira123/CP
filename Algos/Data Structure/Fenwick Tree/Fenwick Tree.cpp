#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int BIT[N];

// x must be positive!
void update(int x,int val) {
	for(; x < N ; x += x & -x)
		BIT[x] += val;
}

// query sum [1,x]
int query(int x) {
	int ret = 0;
	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}
	return ret;
}

// query sum[l,r] can be represented as sum[1,r] - sum[1,l-1]
int query(int l,int r) {
	return query(r) - query(l-1);
}

int main() {
	return 0;
}