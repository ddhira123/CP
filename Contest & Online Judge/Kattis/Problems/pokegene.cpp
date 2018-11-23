#include <bits/stdc++.h>
using namespace std;

const int ALPHA = 26;
const int LOG = 20;
const int MX = 2e5 + 5;

string getString() {
  static char str[MX];
  scanf("%s", str);
  return (string)str;
}

int trie[MX][ALPHA];
int depth[MX];
int in[MX], ot[MX];
int anc[MX][LOG];
int arr[MX];
int n, q;

int trieSize = 0;

int addString(string s) {
  int cur = 0;
  for (char ch : s) {
    int &nex = trie[cur][ch - 'a'];
    if (nex == -1) nex = ++trieSize;
    cur = nex;
  }
  // cout << s << " " << cur << endl;
  return cur;
}

void build(int now, int prv) {
  depth[now] = depth[prv] + 1;
  anc[now][0] = prv;

  for (int i = 1 ; (1 << i) <= depth[now] ; i++) {
    anc[now][i] = anc[anc[now][i-1]][i-1];
  }
}

void dfs(int now) {
  static int cnt = 0;
  in[now] = ++cnt;
  for (int i = 0 ; i < ALPHA ; i++) {
    int nex = trie[now][i];
    if (nex == -1) continue;
    build(nex, now);
    dfs(nex);
  }
  ot[now] = cnt;
}

int getLCA(int u, int v) {
  // printf("u %d v %d: ", u, v);
  if (depth[u] < depth[v]) swap(u, v);
  int diff = depth[u] - depth[v];

  for (int i = 0 ; diff ; i++)
    if (diff & (1 << i)) {
      diff -= (1 << i);
      u = anc[u][i];
    }
  
  if (u == v) {
    // printf("a %d\n", u);
    return u;
  }
  for (int i = LOG-1 ; i >= 0 ; i--)
    if (depth[u] >= (1 << i) && anc[u][i] != anc[v][i]) {
      u = anc[u][i];
      v = anc[v][i];
    }
  
  // printf("b %d\n", anc[u][0]);
  return anc[u][0];
}

void read() {
  scanf("%d %d", &n, &q);
  for (int i = 1 ; i <= n ; i++) {
    string s = getString();
    arr[i] = addString(s);
  }
}

long long solve(vector<int> v, int k) {
  sort(v.begin(), v.end(), [&](int a, int b) {
    return in[a] < in[b];
  });

  // for (int x : v) {
  //   printf("%d ", x);
  // }
  // puts("");

  long long ret = 0;
  for (int i = 0 ; i+k-1 < v.size() ; i++) {
    int lca = getLCA(v[i], v[i+k-1]);

    int worst = 0;
    if (i > 0) worst = max(worst, depth[getLCA(v[i-1], v[i+k-1])]);
    if (i+k < v.size()) worst = max(worst, depth[getLCA(v[i], v[i+k])]);

    // printf("kiri %d kanan %d lca %d worst %d\n", v[i], v[i+k-1], lca, worst);
    ret += (depth[lca] - worst);
  }

  return ret;
}

void work() {
  dfs(0);

  for (int i = 0 ; i < q ; i++) {
    int sz, k;
    scanf("%d %d", &sz, &k);

    vector<int> v(sz);
    for (int &x : v) {
      int y; scanf("%d", &y);
      x = arr[y];
    }

    printf("%lld\n", solve(v, k));
  }
}

int main() {
  memset(trie, -1, sizeof trie);
  read();
  work();
  return 0;
}