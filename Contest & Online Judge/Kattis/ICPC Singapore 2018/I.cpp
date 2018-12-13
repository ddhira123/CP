#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e16;
const int LIMIT = 100;

string s;
string f[26];
long long dp[105][26];
long long sums[1000005];
int nex[105][26];
long long k;

long long solve(int sisa, int letter) {
  if (sisa == 0) return 1;

  long long &ret = dp[sisa][letter];
  if (ret != -1) return ret;

  ret = 0;
  for (char ch : f[letter]) {
    ret = min(INF, ret + solve(sisa-1, ch - 'a'));
  }

  return ret;
}

void read() {
  cin >> s;
  for (int i = 0 ; i < 26 ; i++) {
    cin >> f[i];
  }
  cin >> k;
}

void prepare() {
  memset(dp, -1, sizeof dp);

  if (k <= 100) {
    for (int i = 1 ; i <= s.length() ; i++) {
      sums[i] = sums[i-1] + solve(k, s[i-1] - 'a');
      sums[i] = min(sums[i], INF);
    }
  }

  for (int i = 0 ; i < 26 ; i++) {
    nex[0][i] = f[i][0] - 'a'; 
  }

  for (int i = 1 ; i < 100 ; i++)
    for (int j = 0 ; j < 26 ; j++)
      nex[i][j] = nex[i-1][nex[i-1][j]];
}

char recurse(int sisa, long long x, char ch) {
  if (sisa == 0) return ch + 'a';

  // printf("ch %c\n", ch + 'a');
  for (char it : f[ch]) {
    // printf("now %d %c x %lld solve %lld\n", sisa, it, x, solve(sisa-1, it - 'a'));
    if (solve(sisa-1, it - 'a') >= x)
      return recurse(sisa-1, x, it - 'a');
    x -= solve(sisa-1, it - 'a');
  }

  assert(0);
}

char get(long long x) {
  if (k <= 100) {
    int idx = lower_bound(sums + 1, sums + s.length() + 1, x) - sums - 1;
    x -= sums[idx];

    // printf("idx %d x %lld\n", idx, x);

    return recurse(k, x, s[idx] - 'a'); 
  }

  long long sisa = k - 100;
  char cur = s[0] - 'a';

  for (int i = 0 ; sisa > 0 ; i++)
    if (sisa & (1ll << i)) {
      cur = nex[i][cur];
      sisa -= (1ll << i);
    }
  
  return recurse(100, x, cur);
}

void work() {
  int m; scanf("%d", &m);

  for (int i = 0 ; i < m ; i++) {
    long long x; scanf("%lld", &x);

    printf("%c\n", get(x));
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}