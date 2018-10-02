#include <bits/stdc++.h>
using namespace std;

const int N = 35;

int arr[N][N];
int match[N];
bool vis[N];
int n;

int augment(int lim, int now) {
  if (vis[now]) return 0;
  vis[now] = 1;
  for(int i = 1 ; i <= n ; i++)
    if (arr[now][i] >= lim && (match[i] == -1 || augment(lim, match[i]))) {
      match[i] = now;
      return 1;
    }
  return 0;
}

bool allMatch(int lim) {
  memset(match, -1, sizeof match);
  for (int i = 1 ; i <= n ; i++) {
    memset(vis, 0, sizeof vis);
    if (!augment(lim, i)) return false;
  }
  return true;
}

void read() {
  cin >> n;
  for (int i = 1 ; i <= n ; i++)
    for (int j = 1 ; j <= n ; j++)
      cin >> arr[i][j];
}

int work() {
  int lo = 1, hi = 1e7;
  while (lo < hi) {
    int mid = (lo + hi + 1) / 2;
    if (allMatch(mid)) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}