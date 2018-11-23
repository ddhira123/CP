#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int n;
char s[N][N];
int arr[N];

void read() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++) {
    scanf("%s", s[i]);
  }
}

bool work() {
  for (int j = 0 ; j < n ; j++) {
    int opened = 0;
    for (int i = 0 ; i < n ; i++)
      opened += (s[i][j] == '(');
    
    for (int i = 0 ; i < opened ; i++) {
      arr[i]++;
    }
    for (int i = opened ; i < n ; i++) {
      arr[i]--;
    }

    sort(arr, arr + n);
    if (arr[0] < 0) {
      return 0;
    }
  }

  if (arr[n-1] > 0) return 0;
  return 1;
}

int main() {
  read();
  printf("%s\n", work() ? "Yes" : "No");
  return 0;
}