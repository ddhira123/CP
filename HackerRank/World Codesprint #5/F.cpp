#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

string s;
int odd[MAXN], even[MAXN];
int best[2][MAXN];
int len;

string a, b;
string ret;
int ans;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	cin >> s;
	manacher(0);

	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		cin >> a >> b;
		ans = -1;

		for(int i = 0 ; i < a.length() ; i++) {
			for(int j = 0 ; j < b.length() ; j++) {
				if(a[i] != b[j]) continue;
				int ii = i;
				int jj = j;

				string ai = "";
				string bj = "";
				while(ii < a.length() && jj >= 0 && a[ii] == b[jj]) {
					ii++;
					jj--;
					ai += a[ii];
					bj += 
				}
				int len = 2*(ii-i);

				string
				for(int k =)	
			}
		}
	}
	return 0;
}