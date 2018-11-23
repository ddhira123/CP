#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;

struct Node {
  int maks;
  int lazy;

  void add(int x) {
    maks += x;
    lazy += x;
  }

  Node operator +(Node other) const {
    Node ret;
    ret.lazy = 0;
    ret.maks = max(maks, other.maks);
    return ret;
  }
};

Node stree[4 * N];
int par[N];
vector<int> chld[N];
int in[N], ot[N];
int inve[N];
int cntDfs;
vector<int> adj[N];
int deg[N];
bool vis[N];
int n, m, k;

void build(int id, int l, int r) {
  stree[id].lazy = 0;
  stree[id].maks = 0;

  if (l < r) {
    int m = (l + r) / 2;
    int chld = id << 1;

    build(chld, l, m);
    build(chld+1, m+1, r);
  }
}

void propagate(int id) {
  int chld = id << 1;

  stree[chld].add(stree[id].lazy);
  stree[chld+1].add(stree[id].lazy);

  stree[id].lazy = 0;
}

void update(int id, int l, int r, int x, int y, int val) {
  if (x <= l && r <= y) {
    stree[id].add(val);
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    propagate(id);
    if (x <= m) update(chld, l, m, x, y, val);
    if (y > m)  update(chld+1, m+1, r, x, y, val);

    stree[id] = stree[chld] + stree[chld+1];
  }
}

int query(int id, int l, int r) {
  if (l == r) {
    return l;
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    propagate(id);
    stree[id] = stree[chld] + stree[chld+1];

    if (stree[chld].maks == stree[id].maks) {
      return query(chld, l, m);
    } else {
      return query(chld+1, m+1, r);
    }
  }
}

void dfs(int now) {
  in[now] = ++cntDfs;
  inve[cntDfs] = now;
  for (int nex : chld[now]) {
    dfs(nex);
  }
  ot[now] = cntDfs;
}

void read() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0 ; i < m ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);

    deg[u]++;
    deg[v]++;
  }
}

void prepare() {
  queue<int> q;
  for (int i = 1 ; i <= n ; i++)
    if (deg[i] == 1) {
      q.push(i);
    }
  
  while (!q.empty()) {
    int now = q.front();
    q.pop();

    vis[now] = true;

    for (int nex : adj[now]) {
      deg[nex]--;
      if (deg[nex] == 1) {
        q.push(nex);
      }
      if (deg[nex] == 0) {
        par[nex] = now;
      }
    }
  }

  for (int i = 1 ; i <= n ; i++) {
    if (vis[i]) {
      chld[par[i]].push_back(i);
    } 
  }

  dfs(0);
  build(1, 1, cntDfs);
  
  for (int i = 0 ; i <= n ; i++)
    if (vis[i]) {
      update(1, 1, cntDfs, in[i], ot[i], 1);
    }
}

void updater(int now) {
  if (!vis[now]) return;

  update(1, 1, cntDfs, in[now], ot[now], -1);
  vis[now] = 0;

  updater(par[now]);
}

int work() {
  for (int i = 0 ; i < k ; i++) {
    int inPos = query(1, 1, cntDfs);
    int pos = inve[inPos];
    updater(pos);
  }
  int ret = 0;
  for (int i = 1 ; i <= n ; i++)
    ret += vis[i];
  return ret;
}

void reset() {
  cntDfs = 0;
  for (int i = 0 ; i <= n ; i++) {
    par[i] = 0;
    adj[i].clear();
    chld[i].clear();
    deg[i] = 0;
    vis[i] = 0;
  }
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    prepare();
    printf("%d\n", work());
    reset();
  }
  return 0;
}