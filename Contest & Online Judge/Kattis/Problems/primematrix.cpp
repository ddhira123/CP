#include <bits/stdc++.h>
using namespace std;

int dp[51][101][5001];
bool prime[5001];

int solve(int pos, int val, int sum) {
  if (pos == 0) return sum == 0;
  if (val == 0 || sum < 0) return 0;

  int &ret = dp[pos][val][sum];
  if (ret != -1) return ret;

  ret = solve(pos, val-1, sum);
  ret |= solve(pos-1, val-1, sum-val);

  return ret;
}

int main() {
  memset(dp, -1, sizeof dp);
  for (int i = 2 ; i < 5001 ; i++) prime[i] = 1;

  for (int i = 2 ; i < 5001 ; i++)
    if (prime[i]) {
      for (int j = i+i ; j < 5001 ; j += i)
        prime[j] = false;
    }

  int n, b; cin >> n >> b;
  b = min(b, 100);

  int x = -1;
  for (int i = 1 ; i <= 5000 ; i++)
    if (prime[i] && solve(n, b, i)) {
      x = i;
      break;
    }

  // printf("%d\n", solve(4, 5, 11));

  if (x == -1) {
    puts("impossible");
    return 0;
  }
  
  vector<int> v;
  for (int i = n, val = b ; i >= 1 ; i--) {
    while (solve(i, val-1, x)) val--;
    v.push_back(val);
    x -= val;
    val--;
  }

  for (int i = 0 ; i < n ; i++) {
    for (int j = 0 ; j < n ; j++) {
      printf("%d%c", v[(i + j) % n], j == n-1 ? '\n' : ' ');
    }
  }
  return 0;
}