#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

vector<pair<int, int>> upd[N];
vector<int> adj[N];

long long ans[N];
long long BIT[N];

int n, m;

void update(int idx, int v) {
  for (; idx < N ; idx += idx & -idx)
    BIT[idx] += v;
}

long long query(int x) {
  long long ret = 0;
  while(x) {
    ret += BIT[x];
    x -= x & -x;
  }
  return ret;
}

void read() {
  scanf("%d", &n);
  for (int i = 1 ; i < n ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  scanf("%d", &m);
  for (int i = 0 ; i < m ; i++) {
    int v, d, x;
    scanf("%d %d %d", &v, &d, &x);

    upd[v].push_back({d, x});
  }
}

void dfs(int now, int prv, int dep) {
  for (auto it : upd[now]) {
    int lim = min(N, dep + it.first + 1);
    update(dep, it.second);
    update(lim, -it.second);
  }

  ans[now] = query(dep);
  for (int nex : adj[now]) {
    if (nex == prv) continue;
    dfs(nex, now, dep+1);
  }

  for (auto it : upd[now]) {
    int lim = min(N, dep + it.first + 1);
    update(dep, -it.second);
    update(lim, it.second);
  }
}

int main() {
  read();
  dfs(1, -1, 1);

  for (int i = 1 ; i <= n ; i++)
    printf("%lld ", ans[i]);
  return 0;
}