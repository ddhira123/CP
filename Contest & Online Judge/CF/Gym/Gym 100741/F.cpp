#include <bits/stdc++.h>
using namespace std;

const int N = 305;

map<int ,int> idx;
map<int, int> revIdx;
int idxSize;
vector<int> adj[N*N];
int arr[N][N];
int dia[N][N];
int leftToRight[N*N];
int rightToLeft[N*N];
int vis[N*N];
int n;

void makeDiagonal() {
	int cnt = 0;
	for(int j = 1 ; j <= n ; j++)
		for(int i = n ; i >= 1 ; i--)
			if(i == 1 || j == 1)
				dia[i][j] = ++cnt;
			else
				dia[i][j] = dia[i-1][j-1];
}

void make() {
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++) {
			if(idx.count(arr[i][j])) {
				arr[i][j] = idx[arr[i][j]];
			} else {
				idx[arr[i][j]] = ++idxSize;
				revIdx[idxSize] = arr[i][j];
				arr[i][j] = idx[arr[i][j]];
			}

			adj[dia[i][j]].push_back(arr[i][j]);
		}
}

int augment(int x) {
	if(vis[x]) {
		return 0;
	}

	vis[x] = 1;

	for(int nex : adj[x]) {
		if(rightToLeft[nex] == 0 || augment(rightToLeft[nex])) {
			leftToRight[x] = nex;
			rightToLeft[nex] = x;
			return 1;
		}
	}

	return 0;
}

int maxMatching() {
	int ret = 0;
	for(int i = 1 ; i <= 2*n-1 ; i++) {
		memset(vis, 0, sizeof vis);
		ret += augment(i);
	}
	return ret;
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			scanf("%d",&arr[i][j]);
}

int main() {
	read();
	makeDiagonal();
	make();

	int ret = maxMatching();

	if(ret == 2*n-1) {
		puts("YES");
		for(int i = 1 ; i < 2*n ; i++)
			printf("%d%c", revIdx[leftToRight[i]], i+1 == 2*n ? '\n' : ' ');
	} else {
		puts("NO");
	}
	return 0;
}