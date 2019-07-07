#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, m;
int a[N], b[N];
int ans[N];

vector<pair<int, int>> aSorted;
vector<pair<int, int>> bSorted;

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d %d", &a[i], &b[i]);
  }
}

void solveBLessThanA() {
  for (int i = 0, j = 0 ; i < aSorted.size() ; i++) {
    while (j < bSorted.size() && bSorted[j].first < aSorted[i].first) {
      j++;
    }

    ans[aSorted[i].second] -= j;
  }
}

void solveAMoreThanB() {
  for (int i = bSorted.size()-1, j = aSorted.size()-1 ; i >= 0 ; i--) {
    while (j >= 0 && aSorted[j].first > bSorted[i].first) {
      j--;
    }

    ans[bSorted[i].second] -= ((int)aSorted.size() - 1 - j);
  }
}

void prepare() {
  for (int i = 1 ; i <= n ; i++) {
    aSorted.push_back({a[i], i});
    bSorted.push_back({b[i], i});
    ans[i] = n-1;
  }

  sort(aSorted.begin(), aSorted.end());
  sort(bSorted.begin(), bSorted.end());
}

void work() {
  solveBLessThanA();
  solveAMoreThanB();

  for (int i = 1 ; i <= n ; i++) {
    printf("%d\n", ans[i]);
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}
