#include <bits/stdc++.h>
using namespace std;

char s[200005];
int n;

int main() {
  scanf("%d", &n);
  scanf("%s", s);

  int rem = n-1;
  for (int i = 0 ; i+1 <= n-1 ; i++) {
    // printf("%c %c\n", s[i], s[i+1]);
    if (s[i] > s[i+1]) {
      rem = i;
      break;
    }
  }

  // cout << rem << endl;

  for (int i = 0 ; i < n ; i++)
    if (i != rem) printf("%c", s[i]);
  puts("");
  return 0;
}