#include <bits/stdc++.h>
using namespace std;

const int MAXX = 40;
const int MOD = 1e9 + 7;

map<string, int> ways;
int n;
string s;

int dp[MAXX];

int solve(int now) {
  if(now == s.length()) return 1;

  int &ret = dp[now];
  if(ret != -1) return ret;

  ret = 0;
  string cur = "";
  for(int i = now ; i < s.length() ; i++) {
    cur += s[i];

    ret = (ret + 1ll * ways[cur] * solve(i+1)) % MOD;
  }

  return ret;
}

int main() {
  cin >> n >> s;
  for(int i = 0 ; i < n ; i++) {
    string x; 
    int way;
    cin >> x >> way;
    ways[x] += way;
  }
  
  memset(dp, -1, sizeof dp);
  cout << solve(0) << endl;
  return 0;
}