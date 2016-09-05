#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long LLU;

const LLU INF = (LLU)1e19;

LLU n,m,h;

LLU fpb(LLU a,LLU b) {
	return b ? fpb(b,a % b) : a;
}

void tes(long long a,long long b,long long c){
	long long tot = 0;
	long long lim = (long long)1e18;
	for(long long ans = 1 ; ; ans++) {
		if(ans % a == 0 && ans % b == 0) continue;
		if(ans % a == 0) {
			tot += ans;
			if(tot >= c) {
				cout << ans << endl;
				break;
			}
		}
		else if (ans % b == 0) {
			tot -= ans;
			if(tot < 0) tot = 0;
		}
	}
}

int main() {
	int tc;
	cin >> tc;
	while(tc--) {
		cin >> n >> m >> h;
		if(n == m) {
			cout << "-1\n";
		}	
		else if(n > m) {
			//tes(n,m,h);
			cout << ((h + n - 1) / n) * n << '\n';
		}	
		else {
			//tes(n,m,h);
			//cout << "shit\n";
			LLU sum = 0;
			LLU kpk = n * m / fpb(n,m);
			LLU occ = 0;
			long long tot = 0;
			bool sudah = 0;
			for(int i = 1 ; i < kpk ; i++) {
				if(i % n == 0) {
					occ += kpk;
					sum += i;
					tot += i;
					if(tot >= h) {
						cout << i << "\n";
						sudah = 1;
						break;
					}
				}
				else if(i % m == 0) {
					occ -= kpk;
					sum -= i;
					tot -= i;
					if(tot < 0) tot = 0;
				}
			}
			//cout << sudah << endl;
			if(!sudah) {
				//cout << tot << " " << occ << " " << sum << endl;
				LLU lo = 1;
				LLU hi = h / occ + 1;
				//cout << hi << endl;
				hi = (LLU)sqrt(hi)*(3LL + 2);
				//cout << hi << endl;
				while(lo < hi) {
					LLU mid = (lo + hi) / 2LL;
					LLU itung = mid * sum + (mid) * (mid + 1) * occ / 2LL + tot;
					if(itung >= h)
						hi = mid;
					else
						lo = mid + 1;	
				}
				lo--;
				tot += lo * sum + (lo) * (lo + 1) * occ / 2LL;
				//cout << lo << " " << tot << " " <<  h - tot << endl;
				for(LLU i = kpk * (lo + 1) + 1 ; i < kpk * (lo + 2) ; i++) {
					if(i % n == 0) {
						tot += i;
						if(tot >= h) {
							cout << i << "\n";
							sudah = 1;
							break;
						}
					}
					else if(i % m == 0) {
						tot -= i;
						if(tot < 0) tot = 0;
					}
				}
			}
			assert(sudah);
		}			
	}
	return 0;
}
