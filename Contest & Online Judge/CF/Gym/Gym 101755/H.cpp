#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

string getString() {
  static char str[N];
  scanf("%s", str);
  return (string)str;
}

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int n, m, d;
vector<string> arr;
vector<vector<bool>> can;
vector<vector<int>> dist;

void read() {
  scanf("%d %d %d", &n, &m, &d);
  for(int i = 0 ; i < n ; i++) {
    string s = getString();

    arr.push_back(s);
    can.push_back(vector<bool>(m, true));
    dist.push_back(vector<int>(m, -1));
  }
}

void prepare() {
  queue<pair<int, int>> q;
  for(int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < m ; j++)
      if(arr[i][j] == 'M') {
        q.push({i, j});
        can[i][j] = false;
      }
  
  for(int i = 0 ; i < d ; i++) {
    queue<pair<int, int>> tmp;
    
    while(!q.empty()) {
      pair<int, int> now = q.front();
      q.pop();

      for(int j = 0 ; j < 4 ; j++) {
        int nr = now.first + dr[j];
        int nc = now.second + dc[j];

        if (nr >= 0 && nr < n && nc >= 0 && nc < m && can[nr][nc]) {
          can[nr][nc] = false;
          tmp.push({nr, nc});
        }
      }
    }

    q = tmp;
  }
}

int work() {
  queue<pair<int, int>> q;
  for(int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < m ; j++) {
      if (arr[i][j] == 'S' && can[i][j]) {
        dist[i][j] = 0;
        q.push({i, j});
      }
    }
  
  while (!q.empty()) {
    pair<int, int> now = q.front();
    q.pop();

    if (arr[now.first][now.second] == 'F')
      return dist[now.first][now.second];

    for (int j = 0; j < 4; j++) {
      int nr = now.first + dr[j];
      int nc = now.second + dc[j];

      if (nr >= 0 && nr < n && nc >= 0 && nc < m && can[nr][nc] && dist[nr][nc] == -1) {
        dist[nr][nc] = dist[now.first][now.second]+1;
        q.push({nr, nc});
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