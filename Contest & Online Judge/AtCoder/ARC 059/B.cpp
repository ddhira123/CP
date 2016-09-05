#include <bits/stdc++.h>
using namespace std;

string s;

int main() {
	cin >> s;
	for(char x = 'a' ; x <= 'z' ; x++) {
		int mins = 1e9;
		int pos = -1;
		int cnt = 0;

		for(int i = 0 ; i < s.length() ; i++) {
			if(s[i] != x) continue;
			int sekarang = 2*cnt - i + 1;
			cnt++;
			
			if(sekarang > mins) {
				cout << pos+1 << " " << i+1 << endl;
				return 0;
			}

			sekarang--;
			if(sekarang < mins) {
				mins = sekarang;
				pos = i;
			}
		}
	}
	cout << -1 << " " << -1 << endl;
	return 0;
}