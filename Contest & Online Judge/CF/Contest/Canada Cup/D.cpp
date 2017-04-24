#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 3e5 + 5;

pair<LL,LL> arr[N];
priority_queue<LL,vector<LL>, greater<LL>> pq;
int n;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for(int i = 0 ; i < n ; i++)
		cin >> arr[i].first >> arr[i].second;
	sort(arr + 1,arr + n);
	int iter = n-1;

	while(iter >= 1 && arr[iter].first > arr[0].first) {
		pq.push(arr[iter].second + 1 - arr[iter].first);
		iter--;
	}

	int ans = pq.size()+1;

	while(!pq.empty() && pq.top() <= arr[0].first) {
		arr[0].first -= pq.top();
		pq.pop();

		while(iter >= 1 && arr[iter].first > arr[0].first) {
			pq.push(arr[iter].second + 1 - arr[iter].first);
			iter--;
		}

		ans = min(ans, (int)pq.size() + 1);
	}

	cout << ans << "\n";
	return 0;
}