#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second

struct node {
	int r,s,p;

	node operator +(node other) const {
		node res;
		res.r = r + other.r;
		res.p = p + other.p;
		res.s = s + other.s;
		return res;
	}

	bool operator ==(node other) const {
		return r == other.r && p == other.p && s == other.s;
	}
};

node dp[13][3];
string ret[13][3];
char c[3] = {'R','S','P'};
int n,r,p,s;

void compute() {
	dp[0][0] = (node){1,0,0};
	dp[0][1] = (node){0,1,0};
	dp[0][2] = (node){0,0,1};
	ret[0][0] = "R";
	ret[0][1] = "S";
	ret[0][2] = "P";

	for(int i = 1 ; i < 13 ; i++) 
		for(int j = 0 ; j < 3 ; j++) {
			dp[i][j] = dp[i-1][j] + dp[i-1][(j + 1) % 3];
			ret[i][j] = min(ret[i-1][j],ret[i-1][(j + 1) % 3]) + max(ret[i-1][j],ret[i-1][(j + 1) % 3]);
		}
}

void solve() {
	node tgt = (node){r,s,p};
	string haha = "Z";
	for(int i = 0 ; i < 3 ; i++)
		if(tgt == dp[n][i]) {
			haha = min(haha,ret[n][i]);
		}
	if(haha == "Z") haha = "IMPOSSIBLE";	
	cout << haha << endl;
}

int main() {
	compute();
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d %d %d %d",&n,&r,&p,&s);
		printf("Case #%d: ",tc);
		solve();
	}
	return 0;
}