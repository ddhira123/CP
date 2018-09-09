#include <bits/stdc++.h>
using namespace std;

const int N = 505;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

int n, m;
string s[N];
int dist_to_tree[N][N];
int min_max_dist[N][N];

void read() {
  cin >> n >> m;
  for(int i = 0 ; i < n ; i++) {
    cin >> s[i];
  }
}

void prepare() {
  memset(dist_to_tree, -1, sizeof dist_to_tree);
  queue<pair<int, int>> q;
  
  for(int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < m ; j++) {
      if(s[i][j] == '+') {
        dist_to_tree[i][j] = 0;
        q.push({i, j});
      }
    }
  
  while(!q.empty()) {
    auto now = q.front();
    q.pop();

    for(int i = 0 ; i < 4 ; i++) {
      int nr = now.first + dr[i];
      int nc = now.second + dc[i];

      if(nr >= 0 && nc >= 0 && nr < n && nc < m && dist_to_tree[nr][nc] == -1) {
        dist_to_tree[nr][nc] = dist_to_tree[now.first][now.second] + 1;
        q.push({nr, nc});
      }
    }
  }
}

int work() {
  memset(min_max_dist, -1, sizeof min_max_dist);
  priority_queue<pair<int, pair<int, int>>> pq;

  for(int i = 0 ; i < n ; i++) {
    for(int j = 0 ; j < m ; j++) {
      if(s[i][j] == 'V') {
        min_max_dist[i][j] = dist_to_tree[i][j];
        pq.push({min_max_dist[i][j], {i, j}});
      }
    }
  }

  while(!pq.empty()) {
    auto now = pq.top();
    pq.pop();

    int r = now.second.first;
    int c = now.second.second;

    if(now.first != min_max_dist[r][c]) {
      continue;
    }

    for(int i = 0 ; i < 4 ; i++) {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if(nr >= 0 && nr < n && nc >= 0 && nc < m) {
        int ndis = min(min_max_dist[r][c], dist_to_tree[nr][nc]);

        if(ndis > min_max_dist[nr][nc]) {
          min_max_dist[nr][nc] = ndis;
          pq.push({ndis, {nr, nc}});
        }
      }
    }
  }

  for(int i = 0 ; i < n ; i++) {
    for(int j = 0 ; j < m ; j++) {
      if(s[i][j] == 'J') {
        return min_max_dist[i][j];
      }
    }
  }

  return -1;
}

int main() {
  read();
  prepare();
  printf("%d\n", work());
  return 0;
}