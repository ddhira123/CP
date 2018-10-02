#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int arr[N];
int pset[N];
vector<int> v[N];
int n, k;

int finds(int x) {
  return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
  x = finds(x);
  y = finds(y);

  if (x != y) {
    pset[x] += pset[y];
    pset[y] = x;
  }
}

int main() {
  scanf("%d %d", &n, &k);

  memset(pset, -1, sizeof pset);
  iota(arr + 1, arr + n + 1, 1);
  reverse(arr + 1, arr + n + 1);

  for (int i = 0 ; i < k ; i++) {
    int u, v; scanf("%d %d", &u, &v);

    join(u, v);
  }

  // for (int i = 1 ; i <= n ; i++) cout << i << " " << finds(i) << "\n";
  for (int i = 1 ; i <= n ; i++) v[finds(i)].push_back(i);
  for (int i = 1 ; i <= n ; i++)
    if (!v[i].empty()) {
      for (int j = 0 ; j < v[i].size() / 2 ; j++) {
        int a = v[i][j];
        int b = v[i][v[i].size()-j-1];
        swap(arr[a], arr[b]);
      }
    }
  
  for (int i = 1 ; i <= n ; i++) if (arr[i] != i) {
    puts("No");
    return 0;
  }
  puts("Yes");
  return 0;
}