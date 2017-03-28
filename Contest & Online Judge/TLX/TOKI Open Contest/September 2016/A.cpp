#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 1e3 + 5;

vector<int> v;
int n, k, m;
string s;

int main() {
	cin >> n >> k >> m;
	cin >> s;
	for(int i = 0 ; i < n ; i++) {
		int x; cin >> x;
		if(s[i] == '1') v.push_back(x);
	}
	sort(v.begin(),v.end());
	reverse(v.begin(),v.end());
	for(int i = 0 ; i < min(k+m,(int)v.size()) ; i++)
		if(i < k)
			v[i] = 0;
		else
			v[i] /= 2;
	cout << accumulate(v.begin(),v.end(),0) << "\n";
	return 0;
}