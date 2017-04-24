#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int N = 2e5 + 5;

struct node {
	int dp[4][4];

	node() {
		for(int i = 0 ; i < 4 ; i++) {
			for(int j = 0 ; j < 4 ; j++) {
				dp[i][j] = INF;
			}
		}	
	}

	node operator +(node other) const {
		node res;

		for(int i = 0 ; i < 4 ; i++)
			for(int j = i ; j < 4 ; j++) {
				res.dp[i][j] = min(dp[i][j], other.dp[i][j]);
				for(int k = i ; k < j ; k++) {
					res.dp[i][j] = min(res.dp[i][j], dp[i][k] + other.dp[k+1][j]);
				}
			}

		return res;
	}
};

node stree[4*N];
char s[N];
int psum[N][10];
int n, q;

void update(int id,int l,int r,int x) {
	if(l == r) {
		if(s[x-1] == '2') {
			stree[id].dp[0][0] = psum[l-1][2] - psum[l-1][0];
		}
		else if(s[x-1] == '0') {
			stree[id].dp[1][1] = psum[l-1][0] - psum[l-1][1];
		}
		else if(s[x-1] == '1') {
			stree[id].dp[2][2] = psum[l-1][1] - psum[l-1][6];
		}
		else if(s[x-1] == '7'){
			stree[id].dp[3][3] = 0;
		}
		//printf("%d %d %d\n",id,l,stree[id].dp[3]);
	}
	else {
		int m = (l+r)/2;
		int chld = id << 1;

		if(x <= m)
			update(chld,l,m,x);
		else
			update(chld + 1,m + 1,r,x);

		stree[id] = stree[chld] + stree[chld+1];
	}
}

node query(int id,int l,int r,int x,int y) {
	node res;
	if(x <= l && r <= y) {
		res = stree[id];
		//printf("take here\n");
	}
	else {
		int m = (l + r) / 2;
		int chld = id << 1;

		if(y <= m)
			res =  query(chld,l,m,x,y);
		else if(x > m)
			res =  query(chld + 1,m + 1,r,x,y);
		else {
			res = query(chld,l,m,x,y);
			res = res + query(chld+1,m+1,r,x,y);
		}
	}
	// printf("%d %d %d %d %d\n",id,l,r,x,y);
	// for(int i = 0 ; i < 4 ; i++)
	// 	printf("%d dp %d stat %d\n",i,res.dp[i],res.stat[i]);
	return res;
}

void read() {
	scanf("%d %d",&n,&q);
	scanf("%s",s);
}

void prepare() {
	for(int i = 1 ; i <= n ; i++) {
		for(int j = 0 ; j < 10 ; j++)
			psum[i][j] = psum[i-1][j];
		psum[i][s[i-1]-'0']++;
		update(1,1,n,i);
	}
}

int solve(int a,int b) {
	node ret = query(1,1,n,a,b);
	if(ret.dp[0][3] > 10*n)
		return -1;
	return ret.dp[0][3] + psum[b][6] - psum[a-1][2];
}

int main() {
	read();
	prepare();
	for(int i = 1 ; i <= q ; i++) {
		int a, b;
		scanf("%d %d",&a,&b);
		printf("%d\n",solve(a,b));
	}
	return 0;
}