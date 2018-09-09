#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int MOD = 10000;
const string PATTERN = "welcome to code jam";

string s;
int dp[N][19];

int solve(int now, int pos) {
  if(pos == PATTERN.length()) {
    return 1;
  }
  if(now == s.length()) {
    return 0;
  }

  int &ret = dp[now][pos];
  if(ret != -1) return ret;

  ret = solve(now+1, pos);
  if(s[now] == PATTERN[pos]) {
    ret += solve(now+1, pos+1);
  }
  ret %= MOD;

  return ret;
}

int main() {
  int t; cin >> t;
  getline(cin, s);
  for(int tc = 1 ; tc <= t ; tc++) {
    getline(cin, s);
    memset(dp, -1, sizeof dp);

    printf("Case #%d: %04d\n", tc, solve(0, 0));
  }
  return 0;
}