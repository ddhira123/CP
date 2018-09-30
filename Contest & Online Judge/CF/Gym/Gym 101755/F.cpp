#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

vector<int> chld[N];
vector<int> possiblePar[N];
vector<int> adj[N];
vector<int> actual[N];
bool vis[N];
int n;

bool dfs(int st, int now) {
  if (vis[now]) return false;
  vis[now] = true;
  if (st != now) actual[st].push_back(now);

  for(int nex : adj[now]) {
    if (!dfs(st, nex))
      return false;
  }

  return true;
}

void read() {
  scanf("%d", &n);
  for(int i = 1 ; i <= n ; i++) {
    int x; scanf("%d", &x);

    for(int j = 0 ; j < x ; j++) {
      int c; scanf("%d", &c);

      chld[i].push_back(c);
      possiblePar[c].push_back(i);
    }
  }
}

bool work() {
  int noPar = 0;

  for(int i = 1 ; i <= n ; i++) {
    if (possiblePar[i].size() == 0) noPar++;
    else {
      int opt = possiblePar[i][0];
      for(int j = 1 ; j < possiblePar[i].size() ; j++) {
        int pos = possiblePar[i][j];
        if (chld[opt].size() > chld[pos].size())
          opt = pos;
      }

      adj[opt].push_back(i);
    }
  }

  if (noPar != 1) return false;

  // for (int i = 1 ; i <= n ; i++)
  //   for(int nex : adj[i])
  //     printf("%d %d\n", i, nex);

  for (int i = 1 ; i <= n ; i++) {
    memset(vis, 0, sizeof vis);
    if (!dfs(i, i)) return 0;

    // printf("%d\n", i);
    sort(chld[i].begin(), chld[i].end());
    sort(actual[i].begin(), actual[i].end());

    if (chld[i] != actual[i]) return 0;
  }

  return 1;
}

int main() {
  read();
  bool ok = work();

  if (!ok) puts("NO");
  else {
    puts("YES");
    for(int i = 1 ; i <= n ; i++) {
      for(int nex : adj[i])
        printf("%d %d\n", i, nex);
    }
  }
  return 0;
}