#include <bits/stdc++.h>
using namespace std;

const int MX = 1300000;

int c,m,n;
int fibo[MX];
vector<int> res;

void init() {
	fibo[1] = 1;
	fibo[2] = 2;
	for(int i = 3 ; i < MX ; i++) {
		int &ret = fibo[i];
		ret = fibo[i -1 ] + fibo[i - 2];
		while(ret >= m) ret -= m;
	}
}

int main() {
	cin >> c >> m >> n;
	init();
	int awal = 6;
	int akhir = 6 + 4 * (n - 2);
	long long c2 = c;
	c2 = (c2 * c2) % (long long)m;

	for(int i = awal ; i <= akhir ; i += 2) {
		long long val = fibo[i];
		val = (val * c2) % (long long)m;
		res.push_back(val);
	}

	sort(res.begin(),res.end());
	cout << unique(res.begin(),res.end()) - res.begin() << endl;
	return 0;
}