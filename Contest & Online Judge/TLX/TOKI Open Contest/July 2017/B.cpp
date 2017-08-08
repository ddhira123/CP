#include <bits/stdc++.h>
using namespace std;

const int A = 1;
const int B = 2;
const int C = 4;
const int D = 8;
const int E = 16;
const int F = 32;
const int G = 64;
const int N = 1e5 + 5;
const int MOD = 1e9 + 8;

int mask[10];
int num[N];
char s[N];
bool may_dead[N];
int n;

void init() {
	mask[0] = A | B | C | D | E | F;
	mask[1] = B | C;
	mask[2] = A | B | G | E | D;
	mask[3] = A | G | C | B | D;
	mask[4] = B | C | F | G;
	mask[5] = A | F | G | C | D;
	mask[6] = A | F | G | C | D | E;
	mask[7] = A | B | C;
	mask[8] = 127;
	mask[9] = A | B | C | F | G;
}

bool exist(int x) {
	for(int i = 0 ; i < 10 ; i++)
		if(mask[i] == x) {
			return true;
		}
	return false;
}

int is_subset(int x, int y) {
	return (x | mask[y]) == mask[y];
}

int calc(int x) {
	int ret = 0;
	for(int i = 0 ; i < 10 ; i++)
		ret += is_subset(x, i);
	return ret;
}

void read() {
	scanf("%d", &n);
	scanf("%s", s);
	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < 7 ; j++) {
			int x; scanf("%d", &x);
			num[i] |= (x << j);
		}
	}
}

void prepare() {
	for(int i = 0 ; i < n ; i++) {
		if(num[i] == 0) {
			may_dead[i] = 1;
		} else {
			break;
		}
	}
}

void solve() {
	for(int i = 0 ; i < n ; i++) {
		if(s[i] == '1' && num[i] != 0 && !exist(num[i])) {
			puts("0");
			return;
		}
	}

	// puts("hehe");

	long long way = 1;
	long long ret = 0;

	for(int i = n-1 ; i >= 0 ; i--) {
		if(s[i] == '1' && num[i] == 0) {
			break;
		}

		int possible = 1 - (i != n-1 && mask[0] == num[i]);
		if(s[i] != '1') {
			possible = calc(num[i]) - (is_subset(num[i], 0) && i != n-1);
		}

		// printf("%lld %lld\n", ret, way);

		if(i == 0 || may_dead[i-1]) {
			ret = (ret + way * possible) % MOD;
		}

		if(s[i] == '1') {
			possible += (mask[0] == num[i] && i != n-1);
		} else {
			possible += (is_subset(num[i], 0) && i != n-1);
		}

		way = way * possible % MOD;
	}

	printf("%lld\n", ret);
}

int main() {
	init();
	read();
	prepare();
	solve();
	return 0;
}