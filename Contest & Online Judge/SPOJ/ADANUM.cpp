#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 500;
const int N = 2e5 + 5;

struct query {
	int l;
	int r;
	int idx;

	bool operator <(query other) const {
		if(l / MAGIC == other.l / MAGIC)
			return r < other.r;
		return l / MAGIC < other.l / MAGIC; 
	}
};

long long arithmeticSum(int l,int r) {
	int len = r-l+1;
	return 1ll * len * (l + r) / 2;
}

int arr[N];
int cnt[N];
int total[N];
int nxt[N], prv[N];
int n, q;

long long ans[N];
query kuery[N];

void add(int x) {
	int CNT = cnt[x];

	if(total[CNT+1] == 0) {
		prv[nxt[CNT]] = CNT+1;
		nxt[CNT+1] = nxt[CNT];
		prv[CNT+1] = CNT;
		nxt[CNT] = CNT+1;
	}

	if(total[CNT] == 1) {
		prv[nxt[CNT]] = prv[CNT];
		nxt[prv[CNT]] = nxt[CNT];
	}

	total[CNT]--;
	cnt[x]++;
	total[CNT+1]++;
}

void remove(int x) {
	int CNT = cnt[x];

	if(total[CNT-1] == 0) {
		nxt[CNT-1] = CNT;
		prv[CNT-1] = prv[CNT];
		nxt[prv[CNT]] = CNT-1;
		prv[CNT] = CNT-1;
	}

	if(total[CNT] == 1) {
		prv[nxt[CNT]] = prv[CNT];
		nxt[prv[CNT]] = nxt[CNT];
	}

	total[CNT]--;
	cnt[x]--;
	total[CNT-1]++;
}	


long long calc() {
	int now = prv[n+1];
	int lst = 0;
	long long ret = 0;

	while(now != 0) {
		int val = total[now];
		//printf("now %d val %d\n", now, val);
		ret += arithmeticSum(lst+1, lst+val) * now;
		lst += val;
		now = prv[now];
	}

	return ret;
}

void renumber() {
	vector<int> uniq;
	for(int i = 1 ; i <= n ; i++)
		uniq.push_back(arr[i]);

	sort(uniq.begin(), uniq.end());
	uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());

	for(int i = 1 ; i <= n ; i++)
		arr[i] = lower_bound(uniq.begin(), uniq.end(), arr[i]) - uniq.begin() + 1;
}

void read() {
	scanf("%d %d", &n, &q);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d", arr + i);
	for(int i = 1 ; i <= q ; i++) {
		scanf("%d %d",&kuery[i].l, &kuery[i].r);
		kuery[i].idx = i;
	}
}

void solve() {
	total[0] = n+1;
	nxt[0] = n+1;
	prv[n+1] = 0;

	sort(kuery + 1, kuery + q + 1);
	int l = 1, r = 1;

	for(int i = 1 ; i <= q ; i++) {
		int L = kuery[i].l;
		int R = kuery[i].r;
		//printf("%d %d %d %d\n", l, r, L, R);
		while(r <= R) {
			add(arr[r]);
			r++;
		}
		while(l-1 >= L) {
			add(arr[l-1]);
			l--;
		}

		while(r-1 > R) {
			remove(arr[r-1]);
			r--;
		}
		while(l < L) {
			remove(arr[l]);
			l++;
		}

		ans[kuery[i].idx] = calc();
	}

	for(int i = 1 ; i <= q ; i++)
		printf("%lld\n", ans[i]);
}

int main() {
	read();
	renumber();
	solve();
	return 0;
}