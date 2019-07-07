#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int r, c;
string s[N];
string result[N];
string trail;

int dp1[N][N], dp2[N][N];
bool flag[N][N];

int solve1(int nr, int nc) {
  if (nc < 0 || nr < 0 || s[nr][nc] == '#') return 0;
  if (flag[nr][nc]) return 1;

  int &ret = dp1[nr][nc];
  if (ret != -1) return ret;

  return ret = solve1(nr-1, nc) | solve1(nr, nc-1);
}

int solve2(int nr, int nc) {
  if (nr == r || nc == c || s[nr][nc] == '#') return 0;
  if (flag[nr][nc]) return 1;

  int &ret = dp2[nr][nc];
  if (ret != -1) return ret;

  return ret = solve2(nr + 1, nc) | solve2(nr, nc + 1);
}

int main() {
  cin >> r >> c;
  cin >> trail;
  for (int i = 0 ; i < r ; i++) {
    cin >> s[i];
    result[i] = s[i];
  }

  flag[0][0] = 1;
  for (int i = 0, nr = 0, nc = 0 ; i < trail.size() ; i++) {
    if (trail[i] == '>') nc++;
    else nr++;

    flag[nr][nc] = 1;
  }

  memset(dp1, -1, sizeof dp1);
  memset(dp2, -1, sizeof dp2);

  for (int i = 0 ; i < r ; i++)
    for (int j = 0 ; j < c ; j++) {
      if (s[i][j] == '#') {
        result[i][j] = '#';
      } else if (solve1(i, j) == 0 || solve2(i, j) == 0) {
        result[i][j] = 'P';
      } else if (flag[i][j]) {
        result[i][j] = '!';
      }
      else {
        result[i][j] = '.';
      }
    }
  
  for (int i = 0 ; i < r ; i++) {
    cout << result[i] << endl;
  }

  return 0;
}
