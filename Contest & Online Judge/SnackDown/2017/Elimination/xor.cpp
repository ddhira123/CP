#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;
const int LOG = 31;

struct node {
	vector<int> val;
	vector<long long> psum;

	void add(int x) {
		val.push_back(x);
	}

	void make() {
		sort(val.begin(), val.end());
		psum.resize(val.size(), 0);
		for(int i = 1 ; i < psum.size() ; i++)
			psum[i] = val[i] + psum[i-1];
	}

	long long query(int r) {
		int pos = upper_bound(val.begin(), val.end(), r) - val.begin();
		long long ret = psum[pos-1];
		ret += 1ll * (val.size()-pos) * r;

		return ret;
	}
};

vector<int> st[LOG][2];
int arr[N];
int batas[N];
int n, q;
node stree[3*N];

void build(int id, int l, int r) {
	stree[id].add(0);
	for(int i = l ; i <= r ; i++) {
		stree[id].add(batas[i]);
	}
	stree[id].make();

	if(l < r) {
		int chld = id << 1;
		int m = (l + r) / 2;

		build(chld, l, m);
		build(chld+1, m+1, r);
	}
}

long long query(int id, int l, int r, int x, int y) {
	if(x <= l && r <= y) {
		return stree[id].query(y);
	} else {
		int chld = id << 1;
		int m = (l + r) / 2;
		long long ret = 0;

		if(x <= m) ret += query(chld, l, m, x, y);
		if(y > m)  ret += query(chld+1, m+1 ,r, x, y);

		return ret;
	}
}

void read() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d", arr + i);
}

void prepare() {
	for(int i = 1 ; i <= n ; i++)
		arr[i] ^= arr[i-1];
	for(int i = 1 ; i <= n ; i++) {
		// printf("%d val %d\n", i, arr[i]);
		for(int j = LOG-1 ; j >= 0 ; j--)
			if((arr[i] & (1<<j)) != (arr[i-1] & (1 << j))) {
				int val = (arr[i] & (1<<j));
				val = val > 0;

				st[j][val].push_back(i);
				// printf("push %d to %d %d\n", i, j, val);
				break;
			}
	}

	for(int i = 1 ; i <= n ; i++) {
		batas[i] = n+1;

		for(int j = 0 ; j < LOG ; j++) {
			if((arr[i-1] & (1 << j))) {
				auto it = upper_bound(st[j][1].begin(), st[j][1].end(), i);
				if(it != st[j][1].end()) {
					batas[i] = min(batas[i], *it);
				}
			} else {
				auto it = upper_bound(st[j][0].begin(), st[j][0].end(), i);
				if(it != st[j][0].end()) {
					batas[i] = min(batas[i], *it);
				}
			}
		}
		batas[i]--;

		// printf("%d batas %d\n", i, batas[i]);
	}

	build(1, 1, n);
}

long long queryWork(int l, int r) {
	long long atas = query(1, 1, n, l, r);
	long long bawah = 1ll * (r-l+1) * (r + l - 2) / 2;

	return atas - bawah;
}

void solve() {
	scanf("%d", &q);
	long long last = 0;

	for(int i = 1 ; i <= q ; i++) {
		int l, r;
		scanf("%d %d", &l, &r);

		l = (l + last) % n + 1;
		r = (r + last) % n + 1;

		// printf("%d %d\n", l, r);

		last = queryWork(l, r);
		assert(last >= 0);

		printf("%lld\n", last);
	}
}

int main() {
	read();
	prepare();
	solve();
	return 0;
}