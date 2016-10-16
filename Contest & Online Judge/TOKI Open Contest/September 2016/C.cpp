#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second

LL a, b, c, d;
const LL MOD = 1e9;
const LL LMT = 2e6;

int main() {
	cin >> a >> b >> c >> d;
	LL ret = 0;

	for(int i = -LMT ; i <= LMT ; i++) {
		if(1-b <= i && i <= a-1 && 1-d <= i && i <= c-1) {
			LL x = 0, y = 0;
			if(i < 0) {
				if(a-i <= b) x = a;
				else x = max(0LL,b+i);
				if(c-i <= d) y = c;
				else y = max(0LL,d+i);
				
			}
			else if(i == 0) {
				x = min(a,b);
				y = min(c,d);
			}
			else {
				if(b+i <= a) x = b;
				else x = max(0LL,a - i);
				if(d+i <= c) y = d;
				else y = max(0LL,c - i);
			}
			ret = (ret + 4*x*y) % MOD;
		}
	}

	if(ret % 4 == 0) ret /= 4;
	else ret = (ret - (ret % 4));

	cout << ret << "\n";
	return 0;
}