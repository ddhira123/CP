#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define pb push_back

int BIT[100005];
int n,k;
int arr[100005];

void update(int x) {
	for(; x <= n ; x += x & -x)
		BIT[x]++;
}

int query(int x) {
	int res = 0;
	while(x) {
		res += BIT[x];
		x -= x & -x;
	}
	return res;
}

int main() {
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i++)
		arr[i] = i;
	for(int i = 1 ; i <= k ; i++) {
		int j = n - i + 1;
		if(i >= j) continue;
		swap(arr[i],arr[j]);
	}
	long long ans = 0;
	for(int i = 1 ; i <= n ; i++) {
		//cout << arr[i] << endl;
		update(arr[i]);
		ans += (query(n) - query(arr[i]));
	}
	cout << ans << endl;
	return 0;
}