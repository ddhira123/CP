#include <bits/stdc++.h>
using namespace std;

int get(char x) {
	if(x == 'f') return 1;
	if(x == 'e') return 2;
	if(x == 'd') return 3;
	return 4 + x - 'a';
}

int main() {
	string s; cin >> s;
	long long a = 0;
	for(int i = 0 ; i+1 < s.length() ; i++)
		a = a*10 + (s[i] - '0');
	char x = s[s.length()-1];
	long long ans = get(x);
	if(a % 4 == 1) {
		a--;
		long long jmp = a / 4;
		ans += 12 * jmp;
		ans += a;
	}
	else if(a % 4 == 2) {
		a--;
		long long jmp = a / 4;
		ans += 12 * jmp;
		ans += 6;
		ans += a;
	}
	else if(a % 4 == 3) {
		a--;
		long long jmp = a / 4;
		ans += 12 * jmp;
		ans += a-2;
	}
	else {
		a--;
		long long jmp = a / 4;
		ans += 12 * jmp;
		ans += 6;
		ans += a-2;
	}
	cout << ans << "\n";
	return 0;
}