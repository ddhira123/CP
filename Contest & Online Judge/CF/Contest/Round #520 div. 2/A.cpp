#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int arr[N];
int n;

int main() {
  cin >> n;

  for (int i = 1 ; i <= n ; i++) {
    cin >> arr[i];
  }
  arr[n+1] = 1001;

  int ans = 0;
  for (int i = 1 ; i <= n ; i++) {
    for (int j = i ; j <= n ; j++) {
      bool ok = 1;
      for (int k = i+1 ; k <= j ; k++)
        ok &= (arr[k] == arr[k-1]+1);
      ok &= (arr[j+1] - arr[i-1] == j-i+2);
      // printf("%d i %d j %d arr %d %d\n", ok, i, j, arr[i-1], arr[j+1]);
      if (ok) ans = max(ans, j - i + 1);
    }
  }

  cout << ans << endl;
  return 0;
}