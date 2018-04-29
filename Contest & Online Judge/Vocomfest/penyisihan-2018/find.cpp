#include <bits/stdc++.h>
using namespace std;

const int N = 205;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

int dist[N][N];
bool done[N][N];
char s[N][N];
int rs, cs;
int rt, ct;
int n, m;

void read() {
  scanf("%d %d", &n, &m);
  for(int i = 0 ; i < n ; i++) {
    scanf("%s", s[i]);
  }

  scanf("%d %d", &rs, &cs);
  scanf("%d %d", &rt, &ct);
}

void prepare() {
  for(int i = 0 ; i < n ; i++) {
    for(int j = 0 ; j < m ; j++) {
      done[i][j] = false;
      dist[i][j] = 1e9;
    }
  }
}

int work() {
  deque<pair<int, int>> dq;
  dq.push_back({rs, cs});

  dist[rs][cs] = s[rs][cs] == '#';

  while(!dq.empty()) {
    pair<int, int> now = dq.front();
    dq.pop_front();

    if(done[now.first][now.second]) {
      continue;
    }
    done[now.first][now.second] = true;

    for(int i = 0 ; i < 4 ; i++) {
      int nr = now.first + dr[i];
      int nc = now.second + dc[i];

      if(nr >= 0 && nr < n && nc >= 0 && nc < m) {
        int ndist = dist[now.first][now.second];

        if(s[nr][nc] == '.') {
          if(dist[nr][nc] > ndist) {
            dist[nr][nc] = ndist;
            dq.push_front({nr, nc});
          }
        } else {
          ndist++;
          if (dist[nr][nc] > ndist) {
            dist[nr][nc] = ndist;
            dq.push_back({nr, nc});
          }
        }
      }
    }
  }

  return dist[rt][ct];
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    prepare();
    int ret = work();

    printf("Case #%d: %d\n", tc, ret);
  }
  return 0;
}