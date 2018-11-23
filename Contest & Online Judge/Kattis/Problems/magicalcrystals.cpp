#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

struct Edge {
  int u, v, w;

  void read() {
    scanf("%d %d %d", &u, &v, &w);
  }
};

long long ans[N];

int n, q;
Edge elist[N];
map<int, int> vals[N];
int pset[N];

int finds(int x) {
  return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
  x = finds(x);
  y = finds(y);

  if (x != y) {
    pset[x] += pset[y];
    pset[y] = x;
  }
}

int sign(int x) {
  return x < 0 ? -1 : 1;
}

void read() {
  scanf("%d", &n);
  for (int i = 0 ; i+1 < n ; i++) {
    elist[i].read();
  }
  scanf("%d", &q);
  for (int i = 0 ; i < q ; i++) {
    int sz; scanf("%d", &sz);

    for (int j = 0 ; j < sz ; j++) {
      int x, v;
      scanf("%d %d", &x, &v);

      vals[x][i] += v;
    }
  }
}

void work() {
  for (int i = 1 ; i <= n ; i++) {
    pset[i] = -1;
  }

  sort(elist, elist + n - 1, [](Edge a, Edge b) {
    return a.w < b.w;
  });

  for (int i = 0 ; i+1 < n ; i++) {
    int u = elist[i].u;
    int v = elist[i].v;
    int w = elist[i].w;

    u = finds(u); v = finds(v);

    if (vals[u].size() > vals[v].size()) {
      swap(u, v);
    }

    for (auto it : vals[u]) {
      int idx = it.first;
      int tot = it.second;

      if (vals[v].count(idx)) {
        int otherTot = vals[v][idx];

        if (sign(tot) != sign(otherTot)) {
          int mins = min(abs(tot), abs(otherTot));

          ans[idx] += 1ll * mins * w;
        }
      }

      vals[v][idx] += tot;
    }

    join(v, u);
    vals[u].clear();
  }

  for (int i = 0 ; i < q ; i++) {
    printf("%lld\n", ans[i]);
  }
}

int main() {
  read();
  work();
  return 0;
}