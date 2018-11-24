#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

char s[N][N];
long long dp[N][N];
long long sumDP[N][N];
int cnt[N];
int n, m;

long long solve(int row, int column) {
  if (row == 0 || column == 0) return 0;

  long long &ret = dp[row][column];
  if (ret != -1) return ret;

  ret = row * column;
  ret += solve(row-1, column);
  ret += solve(row, column-1);
  ret -= solve(row-1, column-1);

  return ret;
}

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < n ; i++)
    scanf("%s", s[i]);
}

void prepare() {
  memset(dp, -1, sizeof dp);
  for (int i = 1 ; i <= n ; i++)
    for (int j = 1 ; j <= m ; j++) {
      sumDP[i][j] = sumDP[i][j-1] + solve(i, j);
    }
}

long long work() {
  long long ret = 0;
  for (int i = 0 ; i < n ; i++) {
    for (int j = 0 ; j < m ; j++) {
      cnt[j] = (s[i][j] == '#' ? 0 : cnt[j] + 1);
    }

    // <height, leftmost index>
    vector<pair<int, int>> stek;
    for (int j = 0 ; j <= m ; j++) {
      int lst = j;
      while (!stek.empty() && stek.back().first >= cnt[j]) {
        // harusnya sum solve(stek., j - lst+1 sampe j-stek.back().second)
        ret += sumDP[stek.back().first][j - stek.back().second];
        ret -= sumDP[stek.back().first][j - lst];

        lst = stek.back().second;
        stek.pop_back();
      }

      ret -= sumDP[cnt[j]][j - lst];

      stek.push_back({cnt[j], lst});
    }

    // cout << i << " " << ret << endl;
  }

  return ret;
}

int main() {
  read();
  prepare();
  printf("%lld\n", work());
  return 0;
}