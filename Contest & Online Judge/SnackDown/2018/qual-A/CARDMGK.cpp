#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int arr[N];
bool suf[N], pref[N];
int n;

void read() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++)
    scanf("%d", &arr[i]);
}

bool work() {
  pref[0] = 1;
  for (int i = 1 ; i < n ; i++)
    pref[i] = (pref[i-1] & (arr[i] >= arr[i-1]));
  
  suf[n-1] = 1;
  for (int i = n-2 ; i >= 0 ; i--)
    suf[i] = (suf[i+1] & (arr[i] <= arr[i+1]));
  
  if (suf[0]) return 1;
  if (arr[0] < arr[n-1]) return 0;

  for (int i = 0 ; i+1 < n ; i++)
    if (pref[i] && suf[i+1])
      return 1;
  
  return 0;
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    printf("%s\n", work() ? "YES" : "NO");
  }
  return 0;
}