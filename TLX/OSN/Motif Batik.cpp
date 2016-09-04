#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 100005;

pair<int,int> arr[N];
LL occ[N];
LL sumOfOcc[N];
int n,m;

int main(){
	ios_base::sync_with_stdio(0);
	string dummy; cin >> dummy;
	cin >> n >> m;
	for(int i = 0 ; i < n ; i++)
		cin >> arr[i].second >> arr[i].first;
	sort(arr,arr + n);
	LL ans = 0;
	LL sum = 0;
	for(int i = 0 ; i < n ; i++){
		LL res = sum - sumOfOcc[arr[i].second];
		LL tot = i - occ[arr[i].second];
		LL add = tot * arr[i].first - res;
		
		//cerr << arr[i].first << " " << arr[i].second << endl;
		//cerr << tot << " " << res << " " << add << endl;
		
		ans += add;
		sum += arr[i].first;
		occ[arr[i].second]++;
		sumOfOcc[arr[i].second] += arr[i].first;
	}	
	cout << ans << endl;
	return 0;
}
