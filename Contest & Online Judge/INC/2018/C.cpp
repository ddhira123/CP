#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int LOG = 20;

struct Query {
  int a, b, l, r;

  void read() { scanf("%d %d %d %d", &a, &b, &l, &r); }
};

struct Event {
  int tipe;
  int ansId;
  int l, r;
};

int arr[N];
vector<int> adj[N];
int anc[N][LOG];
int depth[N];
long long ans[N];

int n, q;

vector<int> uniq;
long long BIT[N];

Query queries[N];
vector<Event> ev[N];

int getID(int x) {
  auto it = upper_bound(uniq.begin(), uniq.end(), x);
  return it - uniq.begin() - 1;
}

void update(int id, int x) {
  // printf("id %d get %d\n", id, getID(id));
  id = getID(id);
  // print
  for (; id < uniq.size() ; id += id & -id)
    BIT[id] += x;
}

long long query(int id) {
  id = getID(id);
  long long ret = 0;
  while(id > 0) {
    ret += BIT[id];
    id -= id & -id;
  }
  return ret;
}

void build(int now, int prv) {
  anc[now][0] = prv;
  depth[now] = depth[prv]+1;

  for (int i = 1 ; (1 << i) <= depth[now] ; i++) {
    anc[now][i] = anc[anc[now][i-1]][i-1];
  }
}

void dfs(int now, int prv) {
  for (int nex : adj[now]) {
    if (nex == prv) continue;
    build(nex, now);
    dfs(nex, now);
  }
}

int getLCA(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int diff = depth[u] - depth[v];

  for (int i = 0 ; diff ; i++)
    if (diff & (1 << i)) {
      diff -= (1 << i);
      u = anc[u][i];
    }
  
  if (u == v) return u;

  for (int i = LOG-1 ; i>= 0 ; i--)
    if (depth[u] >= (1 << i) && anc[u][i] != anc[v][i]) {
      u = anc[u][i];
      v = anc[v][i];
    }

  return anc[u][0];
}

void dfsSolve(int now, int prv) {
  // printf("upd\n");
  update(arr[now], arr[now]);
  // printf("don\n");
  for (Event e : ev[now]) {
    int tipe = e.tipe;
    int ansId = e.ansId;
    int l = e.l;
    int r = e.r;

    // printf("l %d r %d\n", l, r);
    long long cnt = query(r) - query(l-1);
    // printf("udh\n");
    if (tipe == 0) {
      ans[ansId] -= 2 * cnt;
      ans[ansId] += (l <= arr[now] && arr[now] <= r ? arr[now] : 0);
    } else {
      ans[ansId] += cnt;
    }
  }

  for (int nex : adj[now]) {
    if (nex == prv) continue;
    dfsSolve(nex, now);
  }

  update(arr[now], -arr[now]);
}

void read() {
  scanf("%d %d", &n, &q);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
  }
  for (int i = 1 ; i < n ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 1 ; i <= q ; i++) {
    queries[i].read();
  }
}

void prepare() {
  dfs(1, -1);

  for (int i = 1 ; i <= n ; i++) {
    uniq.push_back(arr[i]);
  }
  uniq.push_back(-1e9);
  sort(uniq.begin(), uniq.end());
  uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
  // for (int x : uniq) printf("x %d\n", x);

  for (int i = 1 ; i <= q ; i++) {
    int u = queries[i].a;
    int v = queries[i].b;
    int l = queries[i].l;
    int r = queries[i].r;

    int lca = getLCA(u, v);

    ev[u].push_back((Event){1, i, l, r});
    ev[v].push_back((Event){1, i, l, r});
    ev[lca].push_back((Event){0, i, l, r});
  }
}

void work() {
  // puts("kuy");
  dfsSolve(1, -1);
  for (int i =1 ; i <= q ; i++)
    printf("%lld\n", ans[i]);
}

int main() {
  read();
  prepare();
  work();
  return 0;
}