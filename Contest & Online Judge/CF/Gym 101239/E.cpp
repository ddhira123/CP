//  TLE - O(N^2L)
#include <bits/stdc++.h>
using namespace std;

const int N = 4005;

char dummy[N];

string read_string() {
	scanf("%s", dummy);
	return (string)dummy;
}

void print_string(string &s) {
	printf("%s\n", s.c_str());
}

int getIndex(char c) {
	return c == 'A' ? 0 : c == 'C' ? 1 : 2;
}

int dp[N][N];
int can[N][N];
string s[N];
int nxt[N][N][3];
vector<int> chld[N];
string species;
int n;

void read() {
	scanf("%d", &n);
	species = read_string();
	for(int i = 0 ; i < n ; i++) {
		s[i] = read_string();
	}
}

int check(int a, int b) {
	if(can[a][b] != -1) return can[a][b];
	if(s[a].length() > s[b].length()) return false;
	if(a == 0) {
		can[a][b] = 1;
		return true;
	}

	int len = s[a].length();
	int now = nxt[b][0][getIndex(s[a][0])];

	for(int i = 1 ; i < len ; i++) {
		if(now == s[b].length()) {
			can[a][b] = 0;
			return false;
		}
		now = nxt[b][now+1][getIndex(s[a][i])];
	}

	if(now == s[b].length()) {
		can[a][b] = 0;
		return false;
	} else {
		can[a][b] = 1;
		return true;
	}
}

int solve(int a, int b) {
	int c = max(a, b) + 1;

	if(c == n-1) {
		return true;
	}

	int &ret = dp[a][b];
	if(ret != -1) {
		return ret;
	}

	ret = 0;

	if(rand() % 2) {
		if(check(a, c)) {
			ret = solve(c, b);
		}
		if(ret == 0 && check(b, c)) {
			ret = solve(a, c);
		}
	} else {
		if(check(b, c)) {
			ret = solve(a, c);
		}
		if(ret == 0 && check(a, c)) {
			ret = solve(c, b);
		}
	}

	return ret;
}

bool prepare() {
	vector<string> vs[N];
	for(int i = 0 ; i < n ; i++)
		vs[s[i].length()].push_back(s[i]);

	n = 0;
	s[n++] = "";
	for(int i = 0 ; i < N ; i++) {
		if(vs[i].size() > 2) return false;
		for(string x : vs[i])
			s[n++] = x;
	}
	s[n++] = species;

	for(int i = 0 ; i < n ; i++) {
		int len = s[i].length();

		for(int j = 0 ; j < 3 ; j++)
			nxt[i][len][j] = len;

		for(int j = len-1 ; j >= 0 ; j--) {
			for(int k = 0 ; k < 3 ; k++)
				nxt[i][j][k] = nxt[i][j+1][k];

			int idx = getIndex(s[i][j]);

			nxt[i][j][idx] = j;
		}
	}

	memset(dp, -1, sizeof dp);
	memset(can, -1, sizeof can);

	for(int i = 0 ; i < n ; i++)
		if(!check(i, n-1)) {
			return false;
		}

	return true;
}

void backtrack() {
	vector<string> va;
	vector<string> vb;

	int a = 0, b = 0;
	for(int i = 1 ; i+1 < n ; i++) {
		if(check(a, i) && solve(i, b)) {
			va.push_back(s[i]);
			a = i;
		} else {
			vb.push_back(s[i]);
			b = i;
		}
	}

	// swap(va, vb);
	printf("%d %d\n", (int)va.size(), (int)vb.size());
	for(string x : va)
		print_string(x);
	for(string x : vb)
		print_string(x);
}

int main() {
	read();
	if(prepare() && solve(0, 0)) {
		backtrack();
	} else {
		puts("impossible");
	}
	return 0;
}