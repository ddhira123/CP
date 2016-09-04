#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const int N = 1005;
const LL INF = 1e16;
set<LL> st;
vector<double> vel;

LL arr[N];
LL stamp[N];
int n,m;

LL gcd(LL a,LL b) {
	return b == 0 ? a : gcd(b,a % b);
}

LL simplify(LL a,LL b,LL c) {
	LL fpb = gcd(a,b);
	LL ret = a / fpb;
	b /= fpb;
	fpb = gcd(b,c);

	if(fpb != b) return -1;
	c /= fpb;
	if(INF / ret < c) return -1;
	ret *= c;
	return ret;
}

void coba(int a,int b) {
	LL ds = arr[b] - arr[a];
	LL dt = stamp[2] - stamp[1];
	int lst = b;
	for(int i = 3 ; i <= m ; i++) {
		if(n - lst < m - i + 1) return;
		LL dtnow = stamp[i] - stamp[i-1];
		LL ret = simplify(ds,dt,dtnow);
		if(ret == -1) return;
		ret += arr[lst];
		if(arr[lst+1] != ret) return;
		lst++;
	}
	vel.push_back((double)ds / dt);
	st.insert(ds);
}

int getDistinct() {
	sort(vel.begin(),vel.end());
	int ans = 0;
	for(int i = 0; i < vel.size() ; i++)
		if(i == 0 || vel[i] - vel[i-1] > 1e-17)
			ans++;
	return ans;	
}

int main() {
	cin >> m >> n;
	for(int i = 1 ; i <= m ; i++)
		cin >> stamp[i];
	for(int i = 1 ; i <= n ; i++)
		cin >> arr[i];
	for(int i = 1 ; i+1 <= n ; i++)
		for(int j = i + 1 ; j <= i+1 ; j++)
			coba(i,j);
	printf("%d\n",getDistinct());
	for(auto it : st)	
		cout << it << " "; 
	return 0;
}