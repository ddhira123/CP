// fail; too slow T_T
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 1e5 + 5;
const int Q = 3e5 + 5;
const int MAGIC = 400;
const pii NON = {-1, -1};

set<pii> diffCnt;
set<pii> active;

int n, q;

pair<pii, int> query[Q];
int ans[Q];
int arr[N];

bool cmp(pair<pii,int> a, pair<pii,int> b) {
	if(a.fi.fi / MAGIC == b.fi.fi /MAGIC)
		return a.fi.se < b.fi.se;
	return a.fi.fi / MAGIC == b.fi.fi / MAGIC;
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d", arr + i);
	scanf("%d", &q);
	for(int i = 1 ; i <= q ; i++) {
		scanf("%d %d",&query[i].fi.fi, &query[i].fi.se);
		query[i].se = i;
	}
}

int extract() {
	return (*diffCnt.begin()).fi;
}

pii getUpper(pii x) {
	auto it = active.upper_bound(x);
	if(it == active.end()) return NON;
	return *it;
}

pii getLower(pii x) {
	auto it = active.lower_bound(x);
	if(it == active.begin()) return NON;
	it--;
	return *it;
}

void ins(int diff) {
	auto it = diffCnt.lower_bound({diff,-1});
	if(it == diffCnt.end() || (*it).fi != diff) {
		diffCnt.insert({diff, 1});
	} else {
		pii x = *it;
		diffCnt.erase(it);
		x.se++;
		diffCnt.insert(x);
	}
}

void del(int diff) {
	auto it = diffCnt.lower_bound({diff,-1});

	if((*it).se == 1) {
		diffCnt.erase(it);
	} else {
		pii x = *it;
		diffCnt.erase(it);
		x.se--;
		diffCnt.insert(x);
	}
}

void add(pii x) {
	pii atas = getUpper(x);
	pii bawah = getLower(x);
	if(atas != NON) {
		ins(atas.fi-x.fi);
	}
	if(bawah != NON) {
		ins(x.fi-bawah.fi);
	}
	if(atas != NON && bawah != NON) {
		del(atas.fi-bawah.fi);
	}

	active.insert(x);
}

void remove(pii x) {
	pii atas = getUpper(x);
	pii bawah = getLower(x);

	if(atas != NON) {
		del(atas.fi-x.fi);
	}
	if(bawah != NON) {
		del(x.fi-bawah.fi);
	}
	if(atas != NON && bawah != NON) {
		ins(atas.fi-bawah.fi);
	}

	active.erase(x);
}

void refresh(int l, int r) {
	diffCnt.clear();
	active.clear();

	for(int i = l ; i < r ; i++)
		add({arr[i], i});
}

void solve() {
	sort(query + 1, query + q + 1, cmp);

	int l = 1, r = 1;

	for(int i = 1 ; i <= q ; i++) {
		if(query[i].fi.fi / MAGIC != query[i-1].fi.fi / MAGIC) {
			l = query[i].fi.fi;
			r = query[i].fi.se+1;

			refresh(l, r);
		}
		while(r <= query[i].fi.se) {
			add({arr[r],r});
			r++;
		}
		while(l-1 >= query[i].fi.fi) {
			add({arr[l-1], l-1});
			l--;
		}

		while(r-1 > query[i].fi.se) {
			remove({arr[r-1],r-1});
			r--;
		}
		while(l < query[i].fi.fi) {
			remove({arr[l], l});
			l++;
		}

		ans[query[i].se] = extract();
	}

	for(int i = 1 ; i <= q ; i++)
		printf("%d\n", ans[i]);
}

int main() {
	read();
	solve();
	return 0;
}