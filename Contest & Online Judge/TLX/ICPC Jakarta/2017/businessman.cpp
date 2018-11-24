
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];
int color[N];
int vals[N];

set<pair<int, int>> sets[2];
set<pair<int, pair<int, int>>> minimumDiffs;
int n, m, q;

bool bip;

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &vals[i]);
  }
  for (int i = 0 ; i < m ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

bool isBipartite() {
  memset(color, -1, sizeof color);

  queue<int> q;
  color[1] = 0;
  q.push(1);

  while(!q.empty()) {
    int now = q.front();
    q.pop();

    for (int nex : adj[now]) {
      if (color[nex] == -1) {
        color[nex] = color[now] ^ 1;
        q.push(nex);
      } else if (color[nex] == color[now]) {
        return false;
      }
    }
  }

  return true;
}

void addToMinDiff(int now) {
  int other = color[now] ^ 1;

  auto it = sets[other].lower_bound({vals[now], -1});
  if (it != sets[other].end()) {
    int val = (*it).first;
    int idx = (*it).second;
    minimumDiffs.insert({abs(val - vals[now]), {now, idx}});
  }
  if (it != sets[other].begin()) {
    it--;
    int val = (*it).first;
    int idx = (*it).second;
    minimumDiffs.insert({abs(val - vals[now]), {now, idx}});
  }
}

void prepare() {
  bip = isBipartite();

  if (bip) {
    for (int i = 1 ; i <= n ; i++) {
      sets[color[i]].insert({vals[i], i});
    }
    for (int i = 1 ; i <= n ; i++)
      if (color[i] == 0) {
        addToMinDiff(i);
      }
  }
}

int extractMins() {
  while(!minimumDiffs.empty()) {
    pair<int, pair<int, int>> best = *minimumDiffs.begin();
    int a = best.second.first;
    int b = best.second.second;

    // printf("a %d b %d val %d %d best %d\n", a, b, vals[a], vals[b], best.first);

    if (abs(vals[a] - vals[b]) == best.first) {
      return best.first;
    } else {
      minimumDiffs.erase(minimumDiffs.begin());
      addToMinDiff(a);
      addToMinDiff(b);
    }
  }
  assert(false);
  return -1;
}

void work() {
  scanf("%d", &q);
  for (int i = 0 ; i < q ; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    // printf("i %d a %d b %d c %d\n", i, a, b, c);
    if (a == 0) {
      if (bip) {
        sets[color[b]].erase({vals[b], b});
        vals[b] = c;
        sets[color[b]].insert({vals[b], b});
        addToMinDiff(b);
      }
    } else {
      if (!bip || color[b] == color[c]) {
        printf("0\n");
      } else {
        printf("%d\n", extractMins());
      }
    }
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}