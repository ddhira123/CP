#include <bits/stdc++.h>
using namespace std;

const int N = 305;

int m, n;
int arr[N][N];

void read() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < m ; j++)
			scanf("%d",&arr[i][j]);
}

int solve() {
	priority_queue<int, vector<int>, greater<int>> pq;
	int ret = 0;

	for(int i = 0 ; i < n ; i++) {
		sort(arr[i], arr[i] + m);
		for(int j = 0 ; j < m ; j++) {
			arr[i][j] += 2*j + 1;
			pq.push(arr[i][j]);
		}
		ret += pq.top();
		pq.pop();
	}

	return ret;
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		printf("Case #%d: %d\n",tc,solve());
	}
	return 0;
}