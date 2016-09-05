#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define pb push_back

vector<int> arr;
int n,k;
string s;

int main() {
	cin >> n >> k;
	cin >> s;
	for(int i = 0 ; i < s.length() ; i++)
		if(s[i] == '0')
			arr.pb(i);

	int ans = n + n;
	for(int i = k ; i < arr.size() ; i++) {
		int kiri = i - k;
		int diff = arr[i] - arr[kiri];
		diff /= 2;

		int lo = kiri;
		int hi = i;

		while(lo < hi) {
			int mid = (lo + hi + 1) / 2;
			if(arr[kiri] + diff >= arr[mid])
				lo = mid;
			else
				hi = mid - 1;
		}

		for(int j = max(kiri,lo - 10) ; j <= min(i,lo + 10) ; j++)
			ans = min(ans,max(arr[j] - arr[kiri],arr[i] - arr[j]));
	}	
	cout << ans << endl;
	return 0;
}