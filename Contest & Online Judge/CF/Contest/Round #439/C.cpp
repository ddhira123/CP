// Upsolving

#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

typedef long long LL;

int n;

set<pair<int,int>> ss;

struct BIT {
	vector<LL> tree[N];
	vector<int> isi[N];

	void update(int x, int y, LL val) {
		for(; x <= n ; x += x & -x) {
			int idx = lower_bound(isi[x].begin(), isi[x].end(), y) - isi[x].begin();
			for(int j = idx ; j < tree[x].size() ; j += j & -j)
				tree[x][j] += val;
		}
	}

	void tambah(int x ,int y) {
		for(; x <= n ; x += x & -x)
			ss.insert({x, y});
	}

	void initiator(int x, int y, LL val, int tipe) {
		if(tipe == 1) {
			tambah(x, y);
			tambah(y+1, y);
		} else {
			tambah(1, x);
			tambah(1, y+1);
			tambah(x+1, x);
			tambah(x+1, y+1);
		}
	}

	void init() {
		for(int i = 0 ; i < N ; i++) {
			isi[i].push_back(-1);
		}

		for(auto it : ss) {
			isi[it.first].push_back(it.second);
		}

		for(int i = 0 ; i < N ; i++) {
			tree[i].resize(isi[i].size(), 0);
		}
	}

	void updater(int x, int y, LL val, int tipe) {
		if(tipe == 1) {
			update(x, y, val);
			update(y+1, y, -val);
		} else {
			update(1, x, val);
			update(x+1, x, -val);
			update(1, y+1, -val);
			update(x+1, y+1, val);
		}
	}


	LL query_in(int a, int b) {
		LL ret = 0;
		for(int i = a ; i > 0 ; i -= i & -i) {
			int idx = upper_bound(isi[i].begin(), isi[i].end(), b) - isi[i].begin();
			idx--;
			for(int j = idx ; j > 0 ; j -= j & -j)
					ret += tree[i][j];
		}
		return ret;
	}

	LL query(int a, int b) {
		LL ret = query_in(a, b);
		// ret -= query_in(a-1,b);
		// ret -= query_in(a, b-1);
		// ret += query_in(a-1, b-1);

		return ret;
	}
};

int ori[N];
int arr[N];
int qu[N][3];
set<pair<int,int>> st;
BIT bit;
int q;

void add_awal(int x) {
	auto it = st.lower_bound({arr[x], x});
	if(it != st.begin()) {
		it--;
		if(it -> first != arr[x]) {
			bit.updater(1, x, -x, 1);
		} else {
			bit.updater((it -> second) + 1, x, -x, 1);
		}
	} else {
		bit.updater(1, x, -x, 1);
	}
}

void add_akhir(int x) {
	auto it = st.lower_bound({arr[x], x});
	it++;

	if(it != st.end()) {
		if(it -> first != arr[x]) {
			bit.updater(x, n, x, 2);
		} else {
			bit.updater(x, (it -> second) - 1, x, 2);
		}
	} else {
		bit.updater(x, n, x, 2);
	}
}

void remove_awal(int x) {
	auto it = st.lower_bound({arr[x], x});
	if(it != st.begin()) {
		it--;
		if(it -> first != arr[x]) {
			bit.updater(1, x, x, 1);
		} else {
			bit.updater((it -> second) + 1, x, x, 1);
		}
	} else {
		bit.updater(1, x, x, 1);
	}
}

void remove_akhir(int x) {
	auto it = st.lower_bound({arr[x], x});
	it++;

	if(it != st.end()) {
		if(it -> first != arr[x]) {
			bit.updater(x, n, -x, 2);
		} else {
			bit.updater(x, (it -> second) - 1, -x, 2);
		}
	} else {
		bit.updater(x, n, -x, 2);
	}
}

void add_init_awal(int x) {
	auto it = st.lower_bound({arr[x], x});
	if(it != st.begin()) {
		it--;
		if(it -> first != arr[x]) {
			bit.initiator(1, x, -x, 1);
		} else {
			bit.initiator((it -> second) + 1, x, -x, 1);
		}
	} else {
		bit.initiator(1, x, -x, 1);
	}
}

void add_init_akhir(int x) {
	auto it = st.lower_bound({arr[x], x});
	it++;

	if(it != st.end()) {
		if(it -> first != arr[x]) {
			bit.initiator(x, n, x, 2);
		} else {
			bit.initiator(x, (it -> second) - 1, x, 2);
		}
	} else {
		bit.initiator(x, n, x, 2);
	}
}

void rem_init_awal(int x) {
	auto it = st.lower_bound({arr[x], x});
	if(it != st.begin()) {
		it--;
		if(it -> first != arr[x]) {
			bit.initiator(1, x, x, 1);
		} else {
			bit.initiator((it -> second) + 1, x, x, 1);
		}
	} else {
		bit.initiator(1, x, x, 1);
	}
}

void rem_init_akhir(int x) {
	auto it = st.lower_bound({arr[x], x});
	it++;

	if(it != st.end()) {
		if(it -> first != arr[x]) {
			bit.initiator(x, n, -x, 2);
		} else {
			bit.initiator(x, (it -> second) - 1, -x, 2);
		}
	} else {
		bit.initiator(x, n, -x, 2);
	}
}

void read() {
	scanf("%d %d", &n, &q);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d", &arr[i]);
		ori[i] = arr[i];
	}
}

void init_init() {
	st.clear();

	for(int i = 1 ; i <= n ; i++) {
		arr[i] = ori[i];
		st.insert({arr[i], i});
	}

	for(int i = 1 ; i <= n ; i++) {
		add_init_awal(i);
		add_init_akhir(i);
	}
}

void init() {
	st.clear();

	for(int i = 1 ; i <= n ; i++) {
		arr[i] = ori[i];
		st.insert({arr[i], i});
	}

	for(int i = 1 ; i <= n ; i++) {
		add_awal(i);
		add_akhir(i);
	}
}


void updater(int p, int x) {
	remove_awal(p);
	remove_akhir(p);

	pair<int,int> temp = {arr[p], p};

	auto it = st.lower_bound(temp);
	if(it != st.begin()) {
		it--;
		if(it -> first == arr[p]) {
			remove_akhir(it -> second);
		}
	}
	it = st.lower_bound(temp);
	it++;
	if(it != st.end()) {
		if(it -> first == arr[p]) {
			remove_awal(it -> second);
		}
	}

	st.erase({arr[p], p});

	it = st.lower_bound(temp);
	if(it != st.begin()) {
		it--;
		if(it -> first == arr[p]) {
			add_akhir(it -> second);
		}
	}
	it = st.lower_bound(temp);
	if(it != st.end()) {
		if(it -> first == arr[p]) {
			add_awal(it -> second);
		}
	}

	arr[p] = x;
	temp = {arr[p], p};

	it = st.lower_bound(temp);
	if(it != st.begin()) {
		it--;
		if(it -> first == arr[p]) {
			remove_akhir(it -> second);
		}
	}
	it = st.lower_bound(temp);
	if(it != st.end()) {
		if(it -> first == arr[p]) {
			remove_awal(it -> second);
		}
	}

	st.insert({arr[p], p});

	it = st.lower_bound(temp);
	if(it != st.begin()) {
		it--;
		if(it -> first == arr[p]) {
			add_akhir(it -> second);
		}
	}
	it = st.lower_bound(temp);
	it++;
	if(it != st.end()) {
		if(it -> first == arr[p]) {
			add_awal(it -> second);
		}
	}

	add_awal(p);
	add_akhir(p);
}

void initiator(int p, int x) {
	rem_init_awal(p);
	rem_init_akhir(p);

	pair<int,int> temp = {arr[p], p};

	auto it = st.lower_bound(temp);
	if(it != st.begin()) {
		it--;
		if(it -> first == arr[p]) {
			rem_init_akhir(it -> second);
		}
	}
	it = st.lower_bound(temp);
	it++;
	if(it != st.end()) {
		if(it -> first == arr[p]) {
			rem_init_awal(it -> second);
		}
	}

	st.erase({arr[p], p});

	it = st.lower_bound(temp);
	if(it != st.begin()) {
		it--;
		if(it -> first == arr[p]) {
			add_init_akhir(it -> second);
		}
	}
	it = st.lower_bound(temp);
	if(it != st.end()) {
		if(it -> first == arr[p]) {
			add_init_awal(it -> second);
		}
	}

	arr[p] = x;
	temp = {arr[p], p};

	it = st.lower_bound(temp);
	if(it != st.begin()) {
		it--;
		if(it -> first == arr[p]) {
			rem_init_akhir(it -> second);
		}
	}
	it = st.lower_bound(temp);
	if(it != st.end()) {
		if(it -> first == arr[p]) {
			rem_init_awal(it -> second);
		}
	}

	st.insert({arr[p], p});

	it = st.lower_bound(temp);
	if(it != st.begin()) {
		it--;
		if(it -> first == arr[p]) {
			add_init_akhir(it -> second);
		}
	}
	it = st.lower_bound(temp);
	it++;
	if(it != st.end()) {
		if(it -> first == arr[p]) {
			add_init_awal(it -> second);
		}
	}

	add_init_awal(p);
	add_init_akhir(p);
}

LL querier(int l, int r) {
	return bit.query(l, r);
}

void work() {
	init_init();

	for(int i = 0 ; i < q ; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		qu[i][0] = a;
		qu[i][1] = b;
		qu[i][2] = c;
		if(a == 1) {
			initiator(b, c);
		} else {
			// printf("%lld\n", querier(b, c));
		}
	}

	bit.init();
	init();

	for(int i = 0 ; i < q ; i++) {
		int a = qu[i][0];
		int b = qu[i][1];
		int c = qu[i][2];

		if(a == 1) {
			updater(b, c);
		} else {
			printf("%lld\n", querier(b, c));
		}
	}
}

int main() {
	read();
	work();
	return 0;
}