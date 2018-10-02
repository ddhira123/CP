#include <bits/stdc++.h>
using namespace std;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

const int N = 1505;

char s[N][N];
int dst[N][N];
int n;

void read() {
  scanf("%d", &n);
  for(int i = 0 ; i < n ; i++) {
    scanf("%s", s[i]);
  }
}

int work() {
  memset(dst, -1, sizeof dst);
  queue<pair<int, int>> q;

  for(int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < n ; j++) {
      if (s[i][j] == '3') {
        dst[i][j] = 0;
        q.push({i, j});
      }
    }
  
  while(!q.empty()) {
    pair<int, int> now = q.front();
    q.pop();

    int r = now.first;
    int c = now.second;

    for(int i = 0 ; i < 4 ; i++) {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if (nr >= 0 && nr < n && nc >= 0 && nc < n && dst[nr][nc] == -1) {
        dst[nr][nc] = dst[r][c] + 1;
        q.push({nr, nc});
      }
    }
  }

  int mx = 0;
  for(int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < n ; j++)
      if (s[i][j] == '1')
        mx = max(mx, dst[i][j]);
  
  return mx;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}