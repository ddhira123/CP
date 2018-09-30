#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];
int n, m, k;

int cities[N];
bool flag[N];
pair<int, int> best[N][2];

void read() {
  scanf("%d %d %d", &n, &m, &k);
  for(int i = 1 ; i < n ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for(int i = 1 ; i <= m ; i++) {
    scanf("%d", &cities[i]);
  }
}

void prepare() {
  for(int i = 1 ; i <= n ; i++) {
    best[i][0] = best[i][1] = {-1, -1};
  }

  for(int i = 1 ; i <= m ; i++) {
    flag[cities[i]] = true;
  }
}

void dfs1(int now, int prv) {
  if(flag[now]) {
    best[now][0] = {0, now};
  }

  for(int nex : adj[now]) {
    if(nex == prv) continue;
    dfs1(nex, now);

    if(best[nex][0].first >= 0) {
      pair<int, int> tmp = best[nex][0];
      tmp.first++;
      tmp.second = nex;

      if(best[now][1] < tmp) swap(best[now][1], tmp);
      if(best[now][0] < best[now][1]) swap(best[now][0], best[now][1]);
    }
  }
}

void dfs2(int now, int prv) {
  for(int nex : adj[now]) {
    if(nex == prv) continue;

    int idx = 0;
    if(best[now][0].second == nex)
      idx = 1;
    
    if(best[now][idx].first >= 0) {
      pair<int, int> tmp = best[now][idx];
      tmp.first++;
      tmp.second = now;

      if (best[nex][1] < tmp) swap(best[nex][1], tmp);
      if (best[nex][0] < best[nex][1]) swap(best[nex][0], best[nex][1]);
    }

    dfs2(nex, now);
  }
}

int work() {
  dfs1(1, 0);
  dfs2(1, 0);

  int ret = 0;
  for(int i = 1 ; i <= n ; i++)
    if(best[i][0].first <= k)
      ret++;
  
  return ret;
}

void reset() {
  for(int i = 1 ; i <= n ; i++) {
    adj[i].clear();
    flag[i] = 0;
  }
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    prepare();
    printf("%d\n", work());
    reset();
  }
  return 0;
}