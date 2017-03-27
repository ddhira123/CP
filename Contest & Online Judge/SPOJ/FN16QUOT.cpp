#include <bits/stdc++.h>
using namespace std;

const int N = 101;

bool dp[N][2][N*N];
int stamp[N][2][N*N];
int curTime;
int lmt;
int block[N*N];
int tot;
int a[N];
int n;

int getBlock(int x) {
	if(x > tot) return -1;
	return block[x];
}

bool solve(int k, int flag, int pos) {
	// printf("masuk %d %d %d\n", k, flag, pos);
	if(k > lmt || getBlock(pos) != getBlock(pos+k-1)) return 0;

	if(pos+k == tot) {
		if(k == lmt && flag == 1) return true;
		return false;
	}

	bool &ret = dp[k][flag][pos];
	if(stamp[k][flag][pos] == curTime) return ret;
	stamp[k][flag][pos] = curTime;

	ret = false;
	if(flag == 0) {
		if(k == 1) {
			ret = solve(1, 1, pos+1);
		} else {
			ret = solve(k-1, 0, pos+k);
		}
	} else {
		if(k < lmt)
			ret = solve(k, 0, pos+k);
		ret |= solve(k+1, 1, pos+k);
	}

	// printf("%d %d %d -> %d\n", k, flag, pos, ret);
	return ret;
}

bool read() {
	if(scanf("%d", &n) != 1) {
		return false;
	}

	for(int i = 0 ; i < n ; i++)
		scanf("%d", a + i);

	return true;
}

void prepare() {
	tot = 0;
	for(int i = 0 ; i < n ; i++) {
		for(int j = 0 ; j < a[i] ; j++)
			block[tot+j] = i;
		tot += a[i];
	}
}

int calc() {
	int ret = -1;
	for(int i = 1 ; i <= a[0] ; i++) {
		curTime++;
		lmt = i;
		if(solve(i, 0, 0)) {
			ret = i;
		}
	}
	return ret;
}

int main() {
	while(read()) {
		prepare();
		int ret = calc();
		if(ret == -1) {
			puts("no quotation");
		} else {
			printf("%d\n", ret);
		}
	}
	return 0;
}