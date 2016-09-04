#include <bits/stdc++.h>
using namespace std;

int cnt[15];
int f,t,ii;
string s;

int main() {
	cin >> f >> ii >> t;
	f < ii ? cin >> s : cout <<"b\n";
	f < ii ? cin >> s : cout <<"b\n";	
	for(int i = 0 ; i < f ; i++) {
		cin >> s;
		for(int j = 0 ; j < ii ; j++)
			if(s[j] == 'Y')
				cnt[j]++;
	}
	int ans = 0;
	for(int i = 0 ; i < ii ; i++)
		if(cnt[i] >= t) ans++;
	cout << ans << "\n";
	cerr << "?\n";
	return 0;
}