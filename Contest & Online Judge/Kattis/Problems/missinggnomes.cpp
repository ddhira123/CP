#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int arr[N];
bool ada[N];
int n, k;

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 1 ; i <= k ; i++) {
    scanf("%d", &arr[i]);
    ada[arr[i]] = true;
  }

  int j = 1;
  for (int i = 1; i <= k ; i++) {
    while(j <= arr[i]) {
      if (!ada[j]) printf("%d\n", j);
      j++;
    }
    printf("%d\n", arr[i]);
  }

  while (j <= n) {
    if (!ada[j]) printf("%d\n", j);
    j++;
  }
  
  return 0;
}