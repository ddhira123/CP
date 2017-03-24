#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

void make(vector<int> &v) {
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
}

int getIndex(vector<int> &v,int x) {
	return lower_bound(v.begin(), v.end(), x) - v.begin();
}

long long C2(long long x) {
	return x * (x+1) / 2;
}

int BIT[N];
long long pwr[N];
vector<int> arr;
int n;

void init() {
	pwr[0] = 1;
	for(int i = 1 ; i < N ; i++)
		pwr[i] = 2ll * pwr[i-1] % MOD;
}

void update(int x,int val,int lmt) {
	for(; x < lmt ; x += x & -x)
		BIT[x] = (BIT[x] + val) % MOD;
}

int query(int x) {
	int ret = 0;

	while(x) {
		ret =  (ret + BIT[x]) % MOD;
		x -= x & -x;
	}

	return ret;
}


int calc(vector<int> v) {
	vector<int> uniq = v;
	uniq.push_back(-MOD);
	make(uniq);

	int ret = 0;
	memset(BIT, 0, sizeof BIT);

	for(int x : v) {
		int idx = getIndex(uniq, x);

		int val = (query(idx) + 1) % MOD;
		ret = (ret + val) % MOD;

		update(idx, val, uniq.size());
	}

	return ret;
}

void read() {
	scanf("%d",&n);
	for(int i = 0 ; i < n ; i++) {
		int x; scanf("%d",&x);
		arr.push_back(x);
	}
}

int work() {
	long long ret = 0;

	ret = calc(arr);
	//cout << ret << "\n";
	for(int i = 0 ; i < n ; i++) {
		arr[i] = -arr[i];
	}

	ret = (ret + calc(arr)) % MOD;
	//cout << ret << "\n";

	map<int,int> cnt;

	for(int x : arr)
		cnt[x]++;

	for(auto it : cnt) {
		ret = (ret - pwr[it.second] + 1) % MOD;
	}

	ret = (pwr[n]-1 - ret) % MOD;
	ret = (ret + MOD) % MOD;

	return ret;
}

int main() {
	init();
	read();
	printf("%d\n", work());
	return 0;
}