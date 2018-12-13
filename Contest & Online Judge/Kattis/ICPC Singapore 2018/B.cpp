#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

vector<int> adj[N];
int n, m;

int color[N];

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < m ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

int isBipartite(int st) {
  queue<int> q;
  q.push(st);
  color[st] = 0;

  bool bip = true;
  while(!q.empty()) {
    int now = q.front();
    q.pop();

    for (int nex : adj[now]) {
      if (color[nex] == -1) {
        color[nex] = color[now] ^ 1;
        q.push(nex);
      } else if (color[nex] == color[now]) {
        bip = false;
      }
    }
  }

  return bip;
}

int work() {
  int component = 0;
  int hasNotBip = 0;

  for (int i = 1 ; i <= n ; i++)
    if (color[i] == -1) {
      component++;
      hasNotBip |= (!isBipartite(i)); 
    }
  
  return component - 1 + (1 - hasNotBip);
}

int main() {
  memset(color, -1, sizeof color);
  read();
  printf("%d\n", work());
  return 0;
}