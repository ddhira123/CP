#include <bits/stdc++.h>
using namespace std;

const int N = 55;

bool vis[N];
int arr[N];
int n;

void read() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++)
    scanf("%d", &arr[i]);
}

void dfs(int now) {
  // printf("now %d vis %d\n", now, vis[now]);
  if (vis[now]) return;
  vis[now] = 1;

  // cout << now << endl;

  for (int i = 0; i < n; i++) {
    // cout << i << " " << __gcd(arr[i], arr[now]) << endl;
    if (__gcd(arr[i], arr[now]) == 1) {
      // printf("masuk %d -> %d\n", now, i);
      dfs(i);
    }
  }
}

void work() {
  memset(vis, 0, sizeof vis);

  dfs(0);

  int ans = 0;
  for (int i = 0 ; i < n ; i++) {
    if (!vis[i]) {
      ans = 1;
      if (arr[i] != 47) arr[i] = 47;
      else arr[i] = 43;

      break;
    }
  }

  printf("%d\n", ans);
  for (int i = 0 ; i < n ; i++)
    printf("%d%c", arr[i], i+1 == n ? '\n' : ' ');
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    work();
  }
  return 0;
}