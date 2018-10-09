// WA
#include <bits/stdc++.h>
using namespace std;

const int N = 20005;

int depth[N];
vector<int> adj[N];
int dist[N];
int pred[N];
int n, m;

bitset<20001> ancestor[N];
bitset<20001> sameLevelAnc[N];

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

int minCycle = N;

int isTree[N];
bool visited[N];
vector<int> asd;
int vNum, eNum;

void dfs(int now, int prv) {
  visited[now] = true;
  vNum++;
  eNum += adj[now].size();
  asd.push_back(now);

  for (int nex : adj[now]) {
    if (!visited[nex]) {
      dfs(nex, now);
    }
  }
}

void bfs(int start) {
  vector<int> vis = {start};

  queue<int> q;
  dist[start] = 0;
  q.push(start);

  // ancestor[start].set(start, 1);

  while (!q.empty()) {
    int now = q.front();
    q.pop();
    visited[now] = true;
    // ancestor[start].set(start, true);

    for (int nex : adj[now]) {
      if (dist[nex] == -1) {
        dist[nex] = dist[now] + 1;
        ancestor[nex] = ancestor[now];
        ancestor[nex].set(now, true);
        pred[nex] = now;
        // printf("now -> nex %d %d\n", now, nex);
        vis.push_back(nex);
        q.push(nex);
      } else if (dist[nex] >= dist[now]) {
        bitset<20001> common = ancestor[nex] & ancestor[now];
        bitset<20001> commonSame = (ancestor[nex] & sameLevelAnc[now]) | (ancestor[now] & sameLevelAnc[nex]);
        bitset<20001> superSame = (sameLevelAnc[now] & sameLevelAnc[nex]);

        for (int i = 1; i <= n; i++) {
          if (common.test(i)) {
            int dst = dist[now] + dist[nex] + 1 - 2 * dist[i];
            if (dst > 2) {
              // printf("now %d nex %d i %d dst %d\n", now, nex, i, dst);
              minCycle = min(minCycle, dst);
            }
          }

          if (commonSame.test(i)) {
            int dst = dist[now] + dist[nex] + 2 - 2 * dist[i];
            if (dst > 2) {
              // printf("now %d nex %d i %d dst %d\n", now, nex, i, dst);
              minCycle = min(minCycle, dst);
            }
          }

          if (superSame.test(i)) {
            int dst = dist[now] + dist[nex] + 3 - 2 * dist[i];
            if (dst > 2) {
              // printf("now %d nex %d i %d dst %d\n", now, nex, i, dst);
              minCycle = min(minCycle, dst);
            }
          }
        }
        if (dist[now] + 1 == dist[nex]) {
          ancestor[nex] |= ancestor[now];
          ancestor[nex].set(now, true);
        } else {
          // printf("yahu\n");
          sameLevelAnc[nex] |= ancestor[now];
          sameLevelAnc[now] |= ancestor[nex];
        }
        // minCycle = min(minCycle, dist[now] + dist[nex] + 1);
      }
    }
  }
}

int work() {
  memset(dist, -1, sizeof dist);
  memset(visited, 0, sizeof visited);
  for (int i = 1; i <= n; i++)
    if (!visited[i]) {
      bfs(i);
      // printf("st %d\n", i);
    }

  if (minCycle == N) return -1;
  return minCycle;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}