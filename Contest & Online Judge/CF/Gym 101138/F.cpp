// upsolving
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1e5 + 5;
const LL LMT = 3e9 + N;

int arr[N];
int n, h;

int main() {
	scanf("%d %d",&n,&h);
	for(int i = 0 ; i < n ; i++)
		scanf("%d",arr + i);

	long long all = accumulate(arr,arr + n,0ll);
	long long sum = 0;
	long long ans = 4e18;

	for(int i = 0 ; i < n ; i++) {
		sum += arr[i];

		LL lo = 0, hi = (LMT / n) + 5;

		while(lo < hi) {
			LL mid = (lo + hi) / 2;
			LL day = mid * n + i+1;
			LL total = sum + all * mid;
			LL target = h - day * (day+1) / 2;

			if(total >= target)
				hi = mid;
			else
				lo = mid+1;
		}

		if(sum >= h - 1ll * (i+1)*(i+2) / 2)
			lo = 0;
		ans = min(ans, n * lo + i+1);
	}

	printf("%lld\n",ans);
	return 0;
}