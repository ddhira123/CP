#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;

#define fi first
#define se second
#define pb push_back

set<string> st;

int n,q;
string a[50], b[50];

void rec(string now) {
	if(now.length() == n) {
		st.insert(now);
	}
	else {
		char c = now[0];
		now.erase(now.begin());
		for(int i = 0 ; i < q ; i++)
			if(c == b[i][0]) {
				rec(a[i] + now);
			}
	}
}

int main() {
	cin >> n >> q;
	for(int i = 0 ; i < q ; i++) cin >> a[i] >> b[i];
	rec("a");
	cout << st.size() << endl;
	return 0;
}