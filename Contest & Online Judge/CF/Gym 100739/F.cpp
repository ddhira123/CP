#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

LL n,p,q;

int main() {
	cin >> n >> p >> q;
	LL tot = 0;
	for(int i = n ; i >= 1 ; i--) {
		tot += i;
		if((n - i + 1) % q == 0) {
			LL tq = n - i + 1;
			LL tp = p * (tq / q);
			if(tot >= tp) {
				vector<int> ans;
				for(int j = i ; j <= n ; j++)
					ans.push_back(j);
				LL diff =  tot - tp;
				for(int j = 0 ; j < ans.size() ; j++) {
					int mins = j+1;
					LL kurang = ans[j] - mins;
					LL tdiff = min(diff,kurang);
					ans[j] -= tdiff;
					diff -= tdiff;
				}
				for(int x : ans)
					printf("%d ",x);
				puts("");
				return 0;
			}
		}
	}
	puts("IMPOSSIBLE");
	return 0;
}