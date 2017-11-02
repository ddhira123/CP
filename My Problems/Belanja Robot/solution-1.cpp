#include <bits/stdc++.h>
using namespace std;
int n, q;
long long memo[50][100005];
int p[100005], s[100005];
vector <int> a, b;

long long dp(int pos, int money){
	if (pos == a.size()) return 0;
	if (memo[pos][money] != -1) return memo[pos][money];
	long long &ret = memo[pos][money];
	ret = dp(pos + 1, money);
	if (money < a[pos]) return ret;
	return ret = max(ret, b[pos] + dp(pos, money - a[pos]));
}

long long query(int l, int r, int m){
	memset(memo, -1 ,sizeof (memo));
	a.clear();
	b.clear();
	for (int i = l; i <= r; i++)
		a.push_back(p[i]), b.push_back(s[i]);

	return dp(0, m);
}

int main(){
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++){
		scanf("%d", &p[i]);
	}
	for (int i = 1; i <= n; i++)
		scanf("%d", &s[i]);
	for (; q--; ){
		int c;
		scanf("%d", &c);
		if (c == 1){
			int l,r,m;
			scanf("%d%d%d", &l, &r, &m);
			printf("%lld\n", query(l,r,m));
		}else{
			int x, y;
			scanf("%d%d", &x, &y);
			s[x] = y;
		}
	}
}