// WA
#include <bits/stdc++.h>
using namespace std;

const int N = 20005;

int depth[N];
vector<int> adj[N];
int dist[N];
int pred[N];
int n, m;

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

  while(!q.empty() && dist[q.front()]+1 < minCycle) {
    int now = q.front();
    q.pop();
    // vis.push_back(now);

    for (int nex : adj[now]) {
      if (dist[nex] == -1) {
        dist[nex] = dist[now]+1;
        pred[nex] = now;
        vis.push_back(nex);
        q.push(nex);
      } else if (pred[now] != nex) {
        minCycle = min(minCycle, dist[now] + dist[nex] + 1);
      }
    }
  }

  for (int x : vis) {
    dist[x] = -1;
  }
}

int work() {
  // memset(depth, -1, sizeof depth);
  // for (int i = 1; i <= n; i++)
  //   if (depth[i] == -1) {
  //     depth[i] = 0;
  //     dfs(1, -1);
  //   }
  memset(dist, -1, sizeof dist);
  memset(isTree, -1, sizeof isTree);

  for (int i = 1 ; i <= n ; i++)
    if (isTree[i] == -1) {
      vNum = 0;
      eNum = 0;
      asd.clear();
      dfs(i, -1);

      eNum /= 2;
      for (int x : asd)
        isTree[x] = vNum == (eNum+1);
    }
  
  for (int i = 1 ; i <= n ; i++)
    if (!isTree[i]) {
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