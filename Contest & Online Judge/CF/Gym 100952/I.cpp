#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

map<int,int> cnt;
priority_queue<int,vector<int>, greater<int>> pq;

int arr[2][N];
int add[2][N];
int n;
pair<int,int> getNext(pair<int,int> cur) {
	if(cur.first == 0 && cur.second == n-1) return {1,n-1};
	if(cur.first == 0) return {0,cur.second+1};
	if(cur.first == 1 && cur.second == 0) return {0,0};
	return {1,cur.second-1};
}

void read() {
	for(int i = 0 ; i < 2 ; i++)
		for(int j = 0 ; j < n ; j++)
			scanf("%d",&arr[i][j]);
}

void solve(pair<int,int> st) {
	cnt.clear();
	while(!pq.empty()) pq.pop();
	for(int i = 0 ; i < 2 ; i++)
		for(int j = 0 ; j < n ; j++) {
			cnt[arr[i][j]]++;
			pq.push(arr[i][j]);
			add[i][j] = 0;
		}

	if(st.first == 1 && pq.top() >= arr[st.first][st.second]) {
		for(int i = 0 ; i < 2 ; i++) {
			for(int j = 0 ; j < n ; j++) {
				long long ret;
				if(i == st.first && j == st.second) ret = 2ll*n*arr[i][j];
				else ret = arr[i][j] - arr[st.first][st.second];

				printf("%lld%c",ret,j+1 == n ? '\n' : ' ');
			}
		}
		return;
	}

	pair<int,int> now = getNext(st);
	cnt[arr[st.first][st.second]]--;
	int mins = arr[st.first][st.second];
	add[st.first][st.second]--;
	int step = 0;

	while(now != st) {
		while(cnt[pq.top()] == 0) pq.pop();
		step++;
		if(now.first == 1 && mins-1 >= arr[now.first][now.second] && pq.top() >= arr[now.first][now.second]) {
			for(int i = 0 ; i < 2 ; i++) {
				for(int j = 0 ; j < n ; j++) {
					long long ret;
					if(i == now.first && j == now.second) ret = 2ll*n*arr[i][j] + step;
					else ret = arr[i][j] - arr[now.first][now.second] + add[i][j];
					printf("%lld%c",ret,j+1 == n ? '\n' : ' ');
				}
			}
			return;
		}

		cnt[arr[now.first][now.second]]--;
		mins = min(mins,arr[now.first][now.second]);
		add[now.first][now.second]--;
		now = getNext(now);
	}	
	puts("INVALID");
}

int main() {
	int a, b;
	int tc = 0;
	scanf("%d %d %d",&n,&a,&b);
	while(n+a+b > 0) {
		a--; b--;
		read();
		printf("Case %d:\n",++tc);
		solve({a,b});
		scanf("%d %d %d",&n,&a,&b);
	}
	return 0;
}