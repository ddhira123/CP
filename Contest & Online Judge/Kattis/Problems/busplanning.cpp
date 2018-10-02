#include <bits/stdc++.h>
using namespace std;

const int N = 17;

string names[N];
map<string, int> nameToIdx;

int dp[1 << N];
int hate[1 << N];

int n, m, c;

int solve(int mask) {
  int &ret = dp[mask];
  if (ret != -1) return ret;

  if (__builtin_popcount(mask) <= c && (hate[mask] & mask) == 0) {
    return ret = 1;
  }

  ret = 1e9;
  for (int i = mask & (mask - 1) ; i >= (mask - i) ; i = mask & (i - 1)) {
    ret = min(ret, solve(i) + solve(mask - i));
  }

  return ret;
}

void bt(int mask) {
  if (solve(mask) == 1) {
    bool space = 0;
    for (int i = 0 ; i < n ; i++)
      if (mask & (1 << i)) {
        if (space) printf(" ");
        else space = true;

        printf("%s", names[i].c_str());
      }
    puts("");
  } else {
    for (int i = mask & (mask - 1); i >= (mask - i); i = mask & (i - 1)) {
      if (solve(mask) == solve(i) + solve(mask - i)) {
        bt(i);
        bt(mask - i);
        break;
      }
    }
  }
}

void read() {
  cin >> n >> m >> c;
  for (int i = 0 ; i < n ; i++) {
    cin >> names[i];
    nameToIdx[names[i]] = i;
  }
  for (int i = 0 ; i < m ; i++) {
    string s, t;
    cin >> s >> t;

    int a = nameToIdx[s];
    int b = nameToIdx[t];

    hate[1 << a] |= (1 << b);
    hate[1 << b] |= (1 << a);
  }
}

void prepare() {
  memset(dp, -1, sizeof dp);
  for (int i = 1 ; i < (1 << n) ; i++)
    hate[i] = hate[i ^ (i & -i)] | hate[i & -i];
}

void work() {
  printf("%d\n", solve((1 << n) - 1));
  bt((1 << n) - 1);
}

int main() {
  read();
  prepare();
  work();
  return 0;
}