#include <bits/stdc++.h>
using namespace std;

const int N = 20005;

int depth[N];
vector<int> adj[N];
int n, m;

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < m ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

int minCycle = N;

void dfs(int now, int prv) {
  for (int nex : adj[now]) {
    if (nex == prv) continue;
    if (depth[nex] == -1) {
      depth[nex] = depth[now]+1;
      dfs(nex, now);
    } else if (depth[now] > depth[nex]) {
      // assert(depth[nex] < depth[now]);
      // printf("now %d nex %d dnow %d dnex %d\n", now, nex, depth[now], depth[nex]);
      minCycle = min(minCycle, depth[now] - depth[nex] + 1);
    }
  }
}

int work() {
  memset(depth, -1, sizeof depth);
  for (int i = 1 ; i <= n ; i++)
    if (depth[i] == -1) {
      depth[i] = 0;
      dfs(1, -1);
    }
  if (minCycle == N) return -1;
  return minCycle;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}