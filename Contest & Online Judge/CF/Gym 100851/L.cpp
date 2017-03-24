#include <bits/stdc++.h>
using namespace std;

void OPEN(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void CLOSE() {
	fclose(stdin);
	fclose(stdout);
}

typedef long long LL;
const int N = 1e5 + 5;
const LL INF = 4e18;

struct data {
	LL sum;
	int cnt;
	int mins;
	int maks;

	data(LL _s = 0,int _c = 0, int _mins = N, int _maks = 0) {
		sum = _s;
		cnt = _c;
		mins = _mins;
		maks = _maks;
	}

	data operator +(data other) const {
		data ret;
		ret.sum = sum + other.sum;
		ret.cnt = cnt + other.cnt;
		ret.mins = min(mins, other.mins);
		ret.maks = max(maks, other.maks);
		return ret;
	}

	data operator -(data other) const {
		data ret;
		ret.sum = sum - other.sum;
		ret.cnt = cnt - other.cnt;
		return ret;
	}
};

struct node {
	data dat;
	int L;
	int R;

	node() {
		dat = data();
		L = -1;
		R = -1;
	}
};

node stree[50 * N];
int root[2*N];
vector<LL> uniq;
int h[N];
int n;
LL z;
int cnt;

void build(int now,int l,int r) {
	if(l < r) {
		int m = (l + r) / 2;
		stree[now].L = ++cnt;
		stree[now].R = ++cnt;

		build(stree[now].L, l, m);
		build(stree[now].R, m+1, r);
	}
}

void update(int prv,int now,int l,int r,int x,LL add,int mins,int maks) {
	data temp = (data){add, 1, mins, maks};
	stree[now].dat = stree[prv].dat + temp;
	if(l < r) {
		int m = (l + r) / 2;

		if(x <= m) {
			stree[now].L = ++cnt;
			stree[now].R = stree[prv].R;
			update(stree[prv].L, cnt, l, m, x, add, mins, maks);
		} else {
			stree[now].R = ++cnt;
			stree[now].L = stree[prv].L;
			update(stree[prv].R, cnt, m+1, r, x, add, mins, maks);
		}
	}
}

data query(int now,int l,int r,int x,int y) {
	if(x <= l && r <= y) {
		return stree[now].dat;
	} else {
		int m = (l + r) / 2;
		data ret;

		if(x <= m) ret = ret + query(stree[now].L, l, m, x, y);
		if(y > m)  ret = ret + query(stree[now].R, m+1, r, x, y);

		return ret;
	}
}

int getID(LL x) {
	return (int)(upper_bound(uniq.begin(), uniq.end(), x) - uniq.begin()) - 1;
}

void init() {
	// create uniq
	for(int i = 1 ; i <= n ; i++) {
		uniq.push_back(h[i] + i);
		uniq.push_back(h[i] - i);
	}
	sort(uniq.begin(), uniq.end());
	uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());

	root[0] = ++cnt;
	build(cnt, 0, uniq.size()-1);
	for(int i = 1 ; i <= n ; i++) {
		root[i] = ++cnt;
		int idx = getID(h[i] - i);

		update(root[i-1], root[i], 0, uniq.size()-1, idx, h[i]-i, i, i);
	}

	root[n+1] = ++cnt;
	build(cnt, 0, uniq.size()-1);
	int tmp = n+1;
	for(int i = n ; i >= 1 ; i--) {
		root[++tmp] = ++cnt;
		int idx = getID(h[i] + i);

		update(root[tmp-1], root[tmp], 0, uniq.size()-1, idx, h[i]+i, i, i);
	}
}

LL get(int id,LL val) {
	LL ret = 0;
	// dari kiri
	int idKiri = getID(val - id);
	if(idKiri != -1) {
		int asu = idKiri;
		if(uniq[idKiri] != val-id) {
			asu++;
		}
		int kiri = 0;
		if(asu != uniq.size()) {
			kiri = query(root[id], 0, uniq.size()-1, asu, uniq.size()-1).maks;
		}

		if(kiri == 0) {
			return INF;
		}

		data dat = query(root[id], 0, uniq.size()-1, 0, idKiri) - query(root[kiri], 0, uniq.size()-1, 0, idKiri);
		ret += (val - id) * dat.cnt - dat.sum;

	}

	// dari kanan
	int idKanan = getID(val + id);
	if(idKanan != -1) {
		int asu = idKanan;
		if(uniq[idKanan] != val+id) {
			asu++;
		}
		int kanan = n+1;
		if(asu != uniq.size()) {
			kanan = query(root[n+1 + n-id+1], 0, uniq.size()-1, asu, uniq.size()-1).mins;
			kanan = min(kanan, n+1);
		}

		if(kanan == n+1) {
			return INF;
		}

		data dat = query(root[n+1 + n-id+1], 0, uniq.size()-1, 0, idKanan) - query(root[n+1 + n-kanan+1], 0, uniq.size()-1, 0, idKanan);
		LL add = (val+id) * dat.cnt - dat.sum;
		ret += (val+id) * dat.cnt - dat.sum;

	}

	ret -= (val - h[id]);
	return ret;
}

LL solve() {
	LL ret = -1;
	int maks = 0;
	for(int i = 1 ; i <= n ; i++)
		maks = max(maks, h[i]);
	ret = maks;
	for(int i = 1 ; i <= n ; i++) {
		LL lo = ret, hi = maks + n;

		while(lo < hi) {
			LL mid = (lo + hi + 1) / 2;
			LL val = get(i,mid);

			//cout << mid << " " << val << "\n";
			if(val <= z) {
				lo = mid;
			} else {
				hi = mid-1;
			}
		}

		if(lo > ret && get(i, lo) <= z)
			ret = lo;
	}
	return ret;
}

void read() {
	scanf("%d %lld",&n,&z);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",h + i);
	}
}

int main() {
	OPEN("landscape");
	read();
	init();
	printf("%lld\n", solve());
	CLOSE();
	return 0;
}