#include <bits/stdc++.h>
using namespace std;

int main() {
	int d, k, n;
	cin >> d >> k >> n;
	k--;

	if(k & 1) {
		int pos = (k - n) % d;
		int prv = (pos - 1) % d;
		int nxt = (pos + 1) % d;

		int a = (prv - n) % d;
		int b = (nxt - n) % d;

		a = (a + d) % d;
		b = (b + d) % d;

		//printf("%d %d %d\n",pos,prv,nxt);

		printf("%d %d\n",b+1,a+1);
	}
	else {
		int pos = (k + n) % d;
		int prv = (pos - 1 + d) % d;
		int nxt = (pos + 1) % d;

		int a = (prv + n) % d;
		int b = (nxt + n) % d;

		printf("%d %d\n",b+1,a+1);
	}
	return 0;
}