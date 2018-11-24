#include <bits/stdc++.h>
using namespace std;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

const int N = 105;
const int OBSTACLE = -100000;
const int INF = 1e9;

const int MAXTRAP = 15;

int arr[N][N];
int sr, sc, tr, tc;
int n, m, e;

int sums[1 << MAXTRAP];
int trapSums[1 << MAXTRAP];
bool canReach[1 << MAXTRAP];
bool vis[N][N];
int trapNum[N][N];
int valTrap[MAXTRAP];
int trapCnt;
int dp[1 << MAXTRAP];

void read() {
  scanf("%d %d %d %d %d %d %d", &n, &m, &e, &sr, &sc, &tr, &tc);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) scanf("%d", &arr[i][j]);
}

void dfs(int r, int c, int mask) {
  if (r < 1 || r > n || c < 1 || c > m) return;
  if (arr[r][c] == OBSTACLE) return;
  if (trapNum[r][c] != -1 && (mask & (1 << trapNum[r][c])) == 0) return;
  if (vis[r][c]) return;

  vis[r][c] = true;
  sums[mask] += max(arr[r][c], 0);
  canReach[mask] |= (r == tr && c == tc);

  for (int i = 0 ; i < 4 ; i++)
    dfs(r + dr[i], c + dc[i], mask);
}

void prepare() {
  trapCnt = 0;
  memset(trapNum, -1, sizeof trapNum);
  
  for (int i = 1 ; i <= n ; i++)
    for (int j = 1 ; j <= m ; j++) {
      if (arr[i][j] > OBSTACLE && arr[i][j] < 0) {
        trapNum[i][j] = trapCnt++;
        valTrap[trapCnt-1] = arr[i][j];

        // printf("i %d j %d trapCnt %d\n", i, j, trapCnt-1);
      }
    }
  
  // cout << "trap" << trapCnt << endl;
  
  for (int mask = 0 ; mask < (1 << trapCnt) ; mask++) {
    memset(vis, 0, sizeof vis);
    sums[mask] = 0;
    canReach[mask] = false;
    trapSums[mask] = 0;

    for (int i = 0 ; i < trapCnt ; i++)
      if (mask & (1 << i))
        trapSums[mask] += valTrap[i];

    dfs(sr, sc, mask);
    // if (mask == 32) {
    //   for (int i = 1 ; i <= n ; i++) {
    //     for (int j = 1 ; j <= m ; j++) printf("%d ", vis[i][j]);
    //     puts("");
    //   }
    // }
  }
}

int work() {
  dp[0] = 1;

  for (int mask = 1 ; mask < (1 << trapCnt) ; mask++) {
    dp[mask] = false;

    for (int i = 0 ; i < trapCnt ; i++)
      if (mask & (1 << i)) {
        int bef = mask ^ (1 << i);
        if (!dp[bef]) continue;

        int sumBef = sums[bef];
        int trapBef = trapSums[bef];

        if (e + sumBef + trapBef + valTrap[i] >= 0) {
          dp[mask] = true;
        }
      }
    
    // printf("mask %d dp %d sums %d trap %d\n", mask, dp[mask], sums[mask], trapSums[mask]);
  }

  int ret = -1;
  for (int i = 0 ; i < (1 << trapCnt) ; i++)
    if (dp[i] && canReach[i]) {
      // printf("i %d -> %d\n", i, e + sums[i] + trapSums[i]);
      ret = max(ret, e + sums[i] + trapSums[i]);
    }
  
  return ret;
}

int main() {
  int t;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    cerr << "tc: " << tc << endl;
    read();
    prepare();
    printf("Case #%d: %d\n", tc, work());
  }
  return 0;
}