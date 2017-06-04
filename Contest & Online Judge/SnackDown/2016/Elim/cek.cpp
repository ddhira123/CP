#include <bits/stdc++.h>
using namespace std;

int n,q;
long long a[1005], b[1005];

int main() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) scanf("%lld",a + i);
	for(int i = 1 ; i <= n ; i++) scanf("%lld",b + i);
	scanf("%d",&q);
	for(int i = 0 ; i < q ; i++) {
		long long ret = 0;
		int l,r,c,d;
		scanf("%d %d %d %d",&l,&r,&c,&d);
		for(int j = l ; j <= r ; j++)
			ret += max(0ll,a[j]*c - b[j]*d);
		cout << ret << endl;
	}
	return 0;
}