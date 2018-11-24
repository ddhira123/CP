#include <bits/stdc++.h>
using namespace std;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

const int N = 105;
const int OBSTACLE = -100000;
const int INF = 1e9;

int dist[N][N];
int arr[N][N];
int sr, sc, tr, tc;
int n, m, e;

void read() {
  scanf("%d %d %d %d %d %d %d", &n, &m, &e, &sr, &sc, &tr, &tc);
  for (int i = 1 ; i <= n ; i++)
    for (int j = 1 ; j <= m ; j++)
      scanf("%d", &arr[i][j]);
}

int work() {
  priority_queue<pair<int, pair<int, int>>> pq;

  for (int i = 1 ; i <= n ; i++)
    for (int j = 1 ; j <= m ; j++) {
      dist[i][j] = INF;
    }
  
  dist[sr][sc] = 0;
  pq.push({0, {sr, sc}});

  while(!pq.empty()) {
    pair<int, pair<int, int>> now = pq.top();
    pq.pop();

    int r = now.second.first;
    int c = now.second.second;

    if (dist[r][c] != -now.first) continue;

    for (int i = 0 ; i < 4 ; i++) {
      int nr = dr[i] + r;
      int nc = dc[i] + c;

      if (1 <= nr && nr <= n && 1 <= nc && nc <= m && arr[nr][nc] != OBSTACLE) {
        int ndis = dist[r][c] - arr[nr][nc];

        if (ndis < dist[nr][nc] && e - ndis >= 0) {
          dist[nr][nc] = ndis;
          pq.push({-ndis, {nr, nc}});
        }
      }
    }
  }

  return dist[tr][tc] != INF ? e - dist[tr][tc] : -1;
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    printf("Case #%d: %d\n", tc, work());
  }
  return 0;
}