#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int arr[N];
int n;

int main(){
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",&arr[i]);
	sort(arr + 1,arr + n + 1);
	reverse(arr + 1,arr + n + 1);
	long long ans = 0;
	for(int i = 1 ; i <= n ; i++)
		if(i % 3)
			ans += arr[i];
	printf("%lld\n",ans);			
	return 0;
}
