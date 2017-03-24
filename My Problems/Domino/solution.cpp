#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5;
const int MOD = 1e9 + 7;

int C[N][N];
int k;

// pascal triangle
void precompute() {
	for(int i = 0 ; i < N ; i++) {
		C[i][0] = 1;
		for(int j = 1 ; j <= i ; j++)
			C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
	}
}

// driver for combination
int getComb(int a,int b) {
	if(a < 0 || b < 0 || a < b) return 0;
	return C[a][b];
}

// convert s (in binary) to s-1 (in binary)
void decrement(string &s) {
	int cur = s.length()-1;

	while(s[cur] == '0') {
		s[cur] = '1';
		cur--;
	}

	s[cur] = '0';
	if(cur == 0)
		s.erase(s.begin());
}


// calculate how many x, 1 <= x <= s, such that f(x) = k
int calc(string s) {
	if(s.length() == 0) return 0;

	int ret = 0;
	for(int start = 1 ; start < s.length() ; start++)
		for(int en = start+1 ; en < s.length() ; en++) {
			ret = (ret + getComb(en-start-1,k-1)) % MOD;
		}

	int zero = 0;
	for(int i = 1 ; i < s.length() ; i++)
		if(s[i] == '1') {
			if(zero+1 == k) ret = (ret + 1) % MOD;

			// assume i'th bit is zero
			zero++;

			for(int en = i+1 ; en < s.length() ; en++)
				ret = (ret + getComb(en-i-1,k-1-zero)) % MOD;

			// normalize
			zero--;	
		}
		else {
			zero++;
		}

	return ret;	
}

int main() {
	precompute();

	string a, b;
	cin >> a >> b >> k;

	decrement(a);
	int ans = b.length() - a.length();
	if(k > 0)
		ans = (calc(b) - calc(a) + MOD) % MOD;

	cout << ans << "\n";
	return 0;
}