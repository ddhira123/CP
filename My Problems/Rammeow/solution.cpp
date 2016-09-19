#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

int last[N+5];
int lmt[N+5];
int arr[N+5];
long long psum[N+5];
int n, q;

long long getArithmeticSum(int l,int r) {
	long long len = r-l+1;
	return len * (l+r) /2;
}

void prepare() {
	for(int i = 1 ; i <= n ; i++) {
		lmt[i] = max(lmt[i-1],last[arr[i]]);
		last[arr[i]] = i;
		psum[i] = (i-lmt[i]) + psum[i-1];
	}
}

long long query(int l,int r) {
	int batas = upper_bound(lmt + 1,lmt + n + 1,l-1) - lmt;
	batas = min(batas,r+1);
	long long depan = getArithmeticSum(1,batas-l);
	long long belakang = psum[r] - psum[batas-1];
	return depan + belakang;
}

void read() {
	scanf("%d %d",&n,&q);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",arr + i);
}

void work() {
	prepare();
	for(int i = 1 ; i <= q ; i++) {
		int l, r;
		scanf("%d %d",&l,&r);
		printf("%lld\n",query(l,r));
	}
}

int main() {
	read();
	work();
	return 0;
}