#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> seen;
vector<pair<int, int>> adj[N];
vector<pair<int, int>> tree[N];
int n, m;

int use[N];
int U[N], V[N];

int parity[N];
int toggle[N];
bool vis[N];

vector<int> avail[N];

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < m ; i++) {
    scanf("%d %d", &U[i], &V[i]);

    adj[U[i]].push_back({V[i], i});
    adj[V[i]].push_back({U[i], i});

    use[i] = U[i];
    parity[U[i]] ^= 1;
  }
}

void dfsComponent(int now) {
  vis[now] = 1;
  seen.push_back(now);

  for (auto edge : adj[now]) {
    int nex = edge.first;
    int idx = edge.second;

    if (!vis[nex]) {
      tree[now].push_back({nex, idx});
      dfsComponent(nex);
    }
  }
}

void dfsToggle(int now) {
  for (auto edge : tree[now]) {
    int nex = edge.first;
    int idx = edge.second;

    dfsToggle(nex);
    toggle[now] ^= toggle[nex];
    if (toggle[nex]) {
      use[idx] ^= (U[idx] ^ V[idx]);
    }
  }
}

void solveComponent(int root) {
  seen.clear();
  dfsComponent(root);

  vector<int> odd;
  for (int x : seen)
    if (parity[x]) {
      odd.push_back(x);
    }

  for (int i = 0 ; i+1 < odd.size() ; i += 2) {
    toggle[odd[i]] = 1;
    toggle[odd[i+1]] = 1;
  }

  dfsToggle(root);
}

void work() {
  for (int i = 1 ; i <= n ; i++)
    if (!vis[i])
      solveComponent(i);
  
  for (int i = 0 ; i < m ; i++) {
    avail[use[i]].push_back(use[i] ^ U[i] ^ V[i]);
  }
  
  vector<pair<int, pair<int, int>>> ans;
  for (int i = 1 ; i <= n ; i++) {
    for (int j = 0 ; j+1 < avail[i].size() ; j += 2) {
      ans.push_back({avail[i][j], {i, avail[i][j+1]}});
    }
  }

  cout << ans.size() << endl;
  for (auto x : ans) {
    printf("%d %d %d\n", x.first, x.second.first, x.second.second);
  } 
}

int main() {
  read();
  work();
  return 0;
}