#include <bits/stdc++.h>
using namespace std;

const int N = 305;

int cnt[N][N];
char s[N][N];
int n, m;

int ans[2 * N];
int tmp[2 * N];

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < n ; i++) {
    scanf("%s", s[i]);
    // for (int j = 0 ; j < m ; j++)
    //   s[i][j] = '1';
  }
}

void work() {
  memset(ans, 0, sizeof ans);
  memset(cnt, 0, sizeof cnt);

  for (int i = 0 ; i < n ; i++) {
    // cout << i << endl;
    // update cnt, swipe
    for (int j = 0 ; j < m ; j++) {
      for (int k = n ; k > 0 ; k--)
        cnt[j][k] = cnt[j][k-1];
      
      cnt[j][0] = (s[i][j] == '1');
    }

    // printf("done updating cnt\n");

    // sweep left to right
    memset(tmp, 0, sizeof tmp);
    for (int j = 0 ; j < m ; j++) {
      // swipe
      for (int k = n+m ; k > 0 ; k--) {
        tmp[k] = tmp[k-1];
      }
      tmp[0] = 0;

      // add from current column
      for (int k = 0 ; k < n ; k++) {
        tmp[k] += cnt[j][k];
      }

      if (s[i][j] == '1') {
        for (int k = 0 ; k <= n+m ; k++)
          ans[k] += tmp[k];
      }
    }

    // printf("done sweep l->r\n");

    // sweep right to left
    memset(tmp, 0, sizeof tmp);
    for (int j = m-1 ; j >= 0 ; j--) {
      // swipe
      for (int k = n+m ; k > 0 ; k--) {
        tmp[k] = tmp[k-1];
      }
      tmp[0] = 0;

      // add from current column
      for (int k = 0 ; k < n ; k++) {
        tmp[k] += cnt[j][k];
      }

      if (s[i][j] == '1') {
        for (int k = 0 ; k <= n+m ; k++)
          ans[k] += tmp[k];
      }
    }

    // remove double counting
    for (int j = 0 ; j < m ; j++) {
      for (int k = j+1 ; k < m ; k++)
        if (s[i][j] == '1' && s[i][k] == '1')
          ans[k-j]--;
      for (int k = 0 ; k < i ; k++) {
        if (s[i][j] == '1' && s[k][j] == '1')
          ans[i-k]--;
      }
    }
  }

  for (int i = 1 ; i <= n + m - 2 ; i++) {
    printf("%d%c", ans[i], i == n+m-2 ? '\n' : ' ');
  }
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    work();
  }
  return 0;
}