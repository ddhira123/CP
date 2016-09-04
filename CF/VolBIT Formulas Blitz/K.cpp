#include <bits/stdc++.h>
using namespace std;

int prima[4] = {2,3,5,7};

int main() {
	long long n; cin >> n;
	long long ans = 0;
	for(int i = 1 ; i < (1 << 4) ; i++) {
		int mul = 1;
		for(int j = 0 ; j < 4 ; j++)
			if(i & (1 << j))
				mul = mul * prima[j] / __gcd(mul,prima[j]);
		if(__builtin_popcount(i) % 2 == 1)
			ans += n / mul;
		else
			ans -= n / mul;		
	}
	cout << n - ans << endl;
	return 0;
}