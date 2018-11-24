#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LOG = 20;

int anc[N][LOG];
vector<int> child[N];
int depth[N];

int in[N], ot[N];

int streeAnc[4 * N];
pair<int, int> streeT[4 * N];
int n, q;

void buildST(int now, int prv) {
  depth[now] = depth[prv]+1;
  anc[now][0] = prv;
  for (int i = 1 ; (1 << i) <= depth[now] ; i++) {
    anc[now][i] = anc[anc[now][i-1]][i-1];
  }
}

void dfs(int now) {
  static int cnt = 0;
  in[now] = ++cnt;
  for (int nex : child[now]) {
    buildST(nex, now);
    dfs(nex);
  }
  ot[now] = cnt;
}

int getLCA(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  
  int diff = depth[u] - depth[v];
  for (int i = 0 ; diff > 0 ; i++)
    if (diff & (1 << i)) {
      diff -= (1 << i);
      u = anc[u][i];
    }
  
  if (u == v) return u;

  for (int i = LOG-1 ; i >= 0 ; i--)
    if (depth[u] >= (1 << i) && anc[u][i] != anc[v][i]) {
      u = anc[u][i];
      v = anc[v][i];
    }
  
  return anc[u][0];
}

void build(int id, int l, int r) {
  if (l == r) {
    streeAnc[id] = l;
    streeT[id] = {l, r};
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    build(chld, l, m);
    build(chld+1, m+1, r);

    streeAnc[id] = getLCA(streeAnc[chld], streeAnc[chld+1]);
    streeT[id].first = in[streeT[chld].first] < in[streeT[chld+1].first] ? streeT[chld].first : streeT[chld+1].first;
    streeT[id].second = in[streeT[chld].second] > in[streeT[chld+1].second] ? streeT[chld].second : streeT[chld+1].second;
  }
}

pair<int, int> queryT(int id, int l, int r, int x, int y) {
  if (x <= l && r <= y) {
    return streeT[id];
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    if (y <= m) return queryT(chld, l, m, x, y);
    if (x > m)  return queryT(chld+1, m+1, r, x, y);

    pair<int, int> a = queryT(chld, l, m, x, y);
    pair<int, int> b = queryT(chld+1, m+1, r, x, y);
    pair<int, int> ret;

    ret.first = in[a.first] < in[b.first] ? a.first : b.first;
    ret.second = in[a.second] > in[b.second] ? a.second : b.second;

    return ret;
  }
}

int queryAnc(int id, int l, int r, int x, int y) {
  if (x <= l && r <= y) {
    return streeAnc[id];
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    if (y <= m) return queryAnc(chld, l, m, x, y);
    if (x > m)  return queryAnc(chld+1, m+1, r, x, y);

    return getLCA(queryAnc(chld, l, m, x, y), queryAnc(chld+1, m+1, r, x, y));
  }
}

int solveRangeExcluding(int l, int r, int x) {
  if (x == l) return queryAnc(1, 1, n, l+1, r);
  if (x == r) return queryAnc(1, 1, n, l, r-1);
  return getLCA(queryAnc(1, 1, n, l, x-1), queryAnc(1, 1, n, x+1, r));
}

pair<int, int> solve(int l, int r) {
  pair<int, int> imp = queryT(1, 1, n, l, r);
  int a = solveRangeExcluding(l, r, imp.first);
  int b = solveRangeExcluding(l, r, imp.second);

  if (depth[a] > depth[b]) return {imp.first, depth[a]};
  return {imp.second, depth[b]};
}

void read() {
  scanf("%d %d", &n, &q);
  for (int i = 2 ; i <= n ; i++) {
    int par; scanf("%d", &par);
    child[par].push_back(i);
  }
}

void prepare() {
  dfs(1);
  build(1, 1, n);
}

void work() {
  for (int i = 1 ; i <= q ; i++) {
    int l, r;
    scanf("%d %d", &l, &r);

    pair<int, int> ret = solve(l, r);
    printf("%d %d\n", ret.first, ret.second);
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}