#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 450;
const int N = 2e5 + 5;

int arr[N];
int add[MAGIC][MAGIC];
int n, q;

void update(int a, int b, int c) {
  if (b >= MAGIC) {
    for (int i = a ; i <= n ; i += b) arr[i] += c;
  } else {
    add[b][a] += c;
  }
}

int query(int x) {
  int ret = arr[x];
  for (int i = 1 ; i < MAGIC ; i++)
    ret += add[i][x % i];
  return ret;
}

int main() {
  scanf("%d %d", &n, &q);

  for (int i = 0 ; i < q ; i++) {
    int opt; scanf("%d", &opt);
    if (opt == 1) {
      int a, b, c;
      scanf("%d %d %d", &a, &b, &c);
      update(a, b, c);
    } else {
      int x; scanf("%d", &x);
      printf("%d\n", query(x));
    }
  }
  return 0;
}