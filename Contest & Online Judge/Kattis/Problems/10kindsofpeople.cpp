#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

char s[N][N];
int region[N][N];
int n, m;

void dfs(int r, int c, int num, int val) {
  if(r < 0 || r >= n || c < 0 || c >= m || region[r][c] != 0 || s[r][c] != val)
    return;
  region[r][c] = num;
  for(int i = 0 ; i < 4 ; i++) {
    dfs(r + dr[i], c + dc[i], num, val);
  }
}

void read() {
  scanf("%d %d", &n, &m);
  for(int i = 0 ; i < n ; i++)
    scanf("%s", s[i]);
}

void prepare() {
  int nums = 0;

  for(int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < m ; j++)
      if(region[i][j] == 0) {
        nums++;
        dfs(i, j, nums, s[i][j]);
      }
}

void work() {
  int q; scanf("%d", &q);
  for(int i = 0 ; i < q ; i++) {
    int r1, c1, r2, c2;
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

    r1--; c1--; r2--; c2--;

    if(region[r1][c1] != region[r2][c2]) {
      puts("neither");
    } else {
      printf("%s\n", s[r1][c1] == '1' ? "decimal" : "binary");
    }
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}