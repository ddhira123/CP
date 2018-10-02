#include <bits/stdc++.h>
using namespace std;

string get_string() {
  static char str[25];
  scanf("%s", str);
  return (string)str;
}

long long dp[20][8][20][2];
string num;

long long solve(int idx, int mod, int has, int is_less) {
  if (idx < 0) {
    return mod == 0 ? has : 0;
  }

  long long &ret = dp[idx][mod][has][is_less];
  if (ret != -1) return ret;

  ret = 0;
  if (is_less) {
    for (int i = 0 ; i < 10 ; i++) {
      ret += solve(idx - 1, (mod * 10 + i) % 8, has + (i == 8 || i == 6), 1);
    }
  } else {
    for (int i = 0 ; i <= num[idx]-'0' ; i++) {
      ret += solve(idx - 1, (mod * 10 + i) % 8, has + (i == 8 || i == 6), i < num[idx] - '0');
    }
  }

  return ret;
}

long long work() {
  long long val = stoll(num);

  reverse(num.begin(), num.end());
  memset(dp, -1, sizeof dp);

  long long ret = solve(num.length()-1, 0, 0, 0);
  
  int has = 0;
  for (char ch : num) has += (ch == '6' || ch == '8');
  if (val % 8 != 0) ret += has;

  return ret;
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    num = get_string();
    printf("%lld\n", work());
  }
  return 0;
}