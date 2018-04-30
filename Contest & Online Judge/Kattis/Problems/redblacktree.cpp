#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

bool red[N];
vector<int> chld[N];
vector<int> dp[N];
int n, m;

void read() {
  scanf("%d %d", &n, &m);
  for(int i = 2 ; i <= n ; i++) {
    int x; scanf("%d", &x);
    chld[x].push_back(i);
  }
  for(int i = 0 ; i < m ; i++) {
    int x; scanf("%d", &x);
    red[x] = 1;
  }
}

void solve(int now) {
  dp[now] = vector<int>(1, 1);

  // cout << "start " << now << endl;

  for(int nex : chld[now]) {
    solve(nex);
    vector<int> tmp = vector<int>(dp[now].size() + dp[nex].size() - 1, 0);

    // cout << tmp.size() << " " << ret.size() << " " << nxt.size() << endl;

    for(int i = 0 ; i < dp[now].size() ; i++) {
      for(int j = 0 ; j < dp[nex].size() ; j++) {
        tmp[i+j] = (tmp[i+j] + 1ll * dp[now][i] * dp[nex][j]) % MOD;
      }
    }

    dp[nex].clear();
    dp[now] = tmp;
  }

  // cout << "done " << now << endl;

  if(red[now]) {
    if(dp[now].size() < 2) dp[now].push_back(0);
    dp[now][1] = (dp[now][1] + 1) % MOD;
  } else {
    dp[now][0] = (dp[now][0] + 1) % MOD;
  }
}

int main() {
  read();

  solve(1);
  vector<int> ret = dp[1];
  while(ret.size() < m+1) ret.push_back(0);

  for(int x : ret) {
    printf("%d\n", x);
  }

  return 0;
}