/**
	Fenwick Tree

	A data structure that is usually used for counting sum in some range.
	Can be used for RMQ for LIS. Actually in general case, it can't be used for RMQ.
	But according to http://www.ioinformatics.org/oi/shtm/v9_2015_39_44.shtml , it can be done.

	Complexity:
		- Update : O(log N)
		- Query : O(log N)
*/
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