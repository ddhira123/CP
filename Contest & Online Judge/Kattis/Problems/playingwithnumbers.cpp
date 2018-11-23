#include <bits/stdc++.h>
using namespace std;

double LOG2 = log(2);
double LOG3 = log(3);

const int N = 5e4 + 5;

double eval(pair<int, int> a) {
  return a.first * LOG2 + a.second * LOG3;
}

int a[N], b[N];
int prefixMinA[N], prefixMinB[N];
int suffixMinA[N], suffixMinB[N];
int prefixMaxA[N], prefixMaxB[N];
int suffixMaxA[N], suffixMaxB[N];
pair<int, int> ansMin[N], ansMax[N];
int n;

void read() {
  scanf("%d", &n);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d %d", &a[i], &b[i]);
  }
}

void prepare() {
  prefixMinA[0] = prefixMinB[0] = 1e9;
  prefixMaxA[0] = prefixMaxB[0] = 0;

  for (int i = 1 ; i <= n ; i++) {
    prefixMinA[i] = min(prefixMinA[i - 1], a[i]);
    prefixMinB[i] = min(prefixMinB[i - 1], b[i]);
    prefixMaxA[i] = max(prefixMaxA[i - 1], a[i]);
    prefixMaxB[i] = max(prefixMaxB[i - 1], b[i]);
  }

  suffixMinA[n + 1] = suffixMinB[n + 1] = 1e9;
  suffixMaxA[n + 1] = suffixMaxB[n + 1] = 0;
  for (int i = n ; i >= 1 ; i--) {
    suffixMinA[i] = min(suffixMinA[i + 1], a[i]);
    suffixMinB[i] = min(suffixMinB[i + 1], b[i]);
    suffixMaxA[i] = max(suffixMaxA[i + 1], a[i]);
    suffixMaxB[i] = max(suffixMaxB[i + 1], b[i]);
  }
}

void answerMin() {
  ansMin[1] = {prefixMaxA[n], prefixMaxB[n]};
  for (int i = 3 ; i <= n ; i++) {
    ansMin[i] = {prefixMinA[n], prefixMinB[n]};
  }

  if (n >= 2) {
    ansMin[2] = {1e9, 1e9};
    for (int i = 1 ; i <= n ; i++) {
      pair<int, int> cur = {0, 0};
      cur.first = max(prefixMaxA[i-1], suffixMaxA[i+1]);
      cur.second = max(prefixMaxB[i-1], suffixMaxB[i+1]);
      cur.first = min(cur.first, a[i]);
      cur.second = min(cur.second, b[i]);

      if (eval(cur) < eval(ansMin[2])) ansMin[2] = cur;
    }
  }
}

void answerMax() {
  ansMax[n] = {prefixMinA[n], prefixMinB[n]};
  for (int i = n-2 ; i >= 1 ; i--) {
    ansMax[i] = {prefixMaxA[n], prefixMaxB[n]};
  }

  if (n >= 2) {
    ansMax[n-1] = {0, 0};
    for (int i = 1; i <= n; i++) {
      pair<int, int> cur = {0, 0};
      cur.first = min(prefixMinA[i - 1], suffixMinA[i + 1]);
      cur.second = min(prefixMinB[i - 1], suffixMinB[i + 1]);
      cur.first = max(cur.first, a[i]);
      cur.second = max(cur.second, b[i]);

      if (eval(cur) > eval(ansMax[n-1])) ansMax[n-1] = cur;
    }
  }
}

void work() {
  answerMin();
  answerMax();

  for (int i = 1 ; i <= n ; i++) {
    printf("%d %d %d %d\n", ansMax[i].first, ansMax[i].second, ansMin[i].first, ansMin[i].second);
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}