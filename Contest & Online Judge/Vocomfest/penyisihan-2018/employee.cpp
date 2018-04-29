#include <bits/stdc++.h>
using namespace std;

const int N = 105;

vector<int> adj[N];
int match[N];
bool vis[N];
int n, m;

void read() {
  cin >> n >> m;
  for(int i = 1 ; i <= m ; i++) {
    int x; cin >> x;

    for(int j = 0 ; j < x ; j++) {
      int pos; cin >> pos;
      adj[i].push_back(pos);
    }
  }
}

int augment(int x) {
  if(vis[x]) return 0;
  vis[x] = 1;

  for(int nex : adj[x]) {
    if(match[nex] == -1 || augment(match[nex])) {
      match[nex] = x;
      return 1;
    }
  }

  return 0;
}

int mcbm() {
  memset(match, -1, sizeof match);
  int ret = 0;

  for(int i = 1 ; i <= m ; i++) {
    memset(vis, 0, sizeof vis);
    ret += augment(i);
  }

  return ret;
}

bool work() {
  return mcbm() == n;
}

int main() {
  read();
  printf("%s\n", work() ? "Yes" : "No");
  return 0;
}