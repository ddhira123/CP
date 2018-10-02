#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 2e5 + 5;

int pset[N];
vector<int> adj[N];
pair<int, pair<int, int>> elist[M];
int n, m, a;

int finds(int x) {
  return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

bool join(int x, int y) {
  x = finds(x);
  y = finds(y);

  if (x == y) return 0;
  pset[x] += pset[y];
  pset[y] = x;

  return 1;
}

void read() {
  scanf("%d %d %d", &n, &m, &a);
  for (int i = 0 ; i < m ; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);

    elist[i] = {w, {u, v}};
  }
}

int dist_uv;

void dfs(int now, int prv, int tgt, int dst) {
  if (now == tgt) {
    dist_uv = dst;
    return;
  }

  for (int nex : adj[now]) {
    if (nex == prv) continue;
    dfs(nex, now, tgt, dst+1);
  }
}

void work() {
  memset(pset, -1, sizeof pset);
  sort(elist, elist + m);

  for (int i = 0 ; i < m ; i++) {
    int u = elist[i].second.first;
    int v = elist[i].second.second;

    if (!join(u, v)) {
      dfs(u, -1, v, 0);
      long long ret = 1ll * elist[i].first * elist[i].first;
      ret += 1ll * a * (dist_uv + 1);
      
      printf("%lld\n", ret);
      return;
    } else {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  puts("Poor girl");
}

int main() {
  read();
  work();
  return 0;
}