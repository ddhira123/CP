#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int MX = 5005;

int dp[N][MX];
int arr[N];
int t, n;

int solve(int now, int sisa) {
  if(sisa == 0) return 1;
  if(sisa < 0 || now == n) return 0;

  int &ret = dp[now][sisa];
  if(ret != -1) return ret;

  ret = solve(now+1, sisa);
  ret |= solve(now+1, sisa - arr[now]);

  return ret;
}

void read() {
  cin >> t >> n;
  for(int i = 0 ; i < n ; i++) {
    cin >> arr[i];
  }
}

void work() {
  memset(dp, -1, sizeof dp);
  int cur = -1;

  for(int i = t ; cur == -1 ; i--) {
    if(solve(0, i)) {
      cur = i;
    }
  }

  int a = 0, b = 0;
  for(int i = 0 ; i < n ; i++) {
    if(solve(i+1, cur)) {
      printf("%d%c", b, i+1 == n ? '\n' : ' ');
      b += arr[i];
    } else {
      printf("%d%c", a, i + 1 == n ? '\n' : ' ');
      a += arr[i];
      cur -= arr[i];
    }
  }
}

int main() {
  read();
  work();
  return 0;
}