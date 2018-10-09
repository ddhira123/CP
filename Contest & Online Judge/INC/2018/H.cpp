#include <bits/stdc++.h>
using namespace std;

long long dp[20][10][2];
string s;

long long solve(int now, int lst, int kur) {
  if (now == -1) {
    return lst % 2 == 1;
  }

  // cout << now << " " << lst << " " << kur << endl;

  long long &ret = dp[now][lst][kur];
  if (ret != -1) {
    return ret;
  }

  ret = 0;
  if (kur) {
    for (int i = 0 ; i < 10 ; i++) {
      ret += solve(now-1, i != 0 ? i : lst, 1);
    }
  } else {
    // cout << "skr" << now << " " << s[now] << endl;
    for (int i = 0 ; i <= s[now]-'0' ; i++) {
      ret += solve(now-1, i != 0 ? i : lst, i != s[now] - '0');
    }
  }

  return ret;
}

long long calc(long long b) {
  s = "";
  long long a = b;
  if (b == 0) s = "0";
  while (b > 0) {
    // printf("%lld %d\n", b, b % 10);
    s += (char)(b % 10 + '0');
    b /= 10;
  }

  // cout << s << endl;

  memset(dp, -1, sizeof dp);
  long long ret = solve(s.length()-1, 0, 0);
  // printf("%lld -> %lld\n", a, ret);
  return ret;
}

int main() {
  long long a, b;
  cin >> a >> b;

  long long odd = calc(b) - calc(a-1);
  long long even = b-a+1 - odd;

  printf("%lld %lld\n", odd, even);
  return 0;
}