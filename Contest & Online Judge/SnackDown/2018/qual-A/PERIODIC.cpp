#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;
const int N = 1e5 + 5;

int arr[N];
int n;

void read() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++)
    scanf("%d", &arr[i]);
}

void work() {
  vector<pair<int, int>> v;
  for (int i = 0 ; i < n ; i++) {
    if (arr[i] != -1) {
      v.push_back({arr[i]-1, i});
    }
  }

  if (v.size() <= 1) {
    puts("inf");
    return;
  }

  map<int, int> mx;
  for (int i = 1 ; i < v.size() ; i++) {
    int dst = v[i].second - v[i-1].second;
    int prv = v[i-1].first;
    int now = v[i].first;

    if (dst + prv < now) {
      puts("impossible");
      return;
    }

    if (dst + prv > now) {
      int key = dst + prv - now;

      if (mx.count(key)) mx[key] = max(mx[key], max(prv, now));
      else mx[key] = max(prv, now);
    }
  }

  if (mx.empty()) {
    puts("inf");
    return;
  }

  bool isFirst = true;
  set<int> possible;

  for (auto it : mx) {
    // printf("%d %d\n", it.first , it.second);
    set<int> nextPossible;
    for (int i = 1 ; i*i <= it.first ; i++)
      if (it.first % i == 0) {
        int a = i;
        int b = it.first / i;

        if (a > it.second && (isFirst || possible.count(a))) {
          nextPossible.insert(a);
        }
        if (b > it.second && (isFirst || possible.count(b))) {
          nextPossible.insert(b);
        }
      }
    
    isFirst = false;
    possible = nextPossible;
  }

  if (possible.empty()) {
    puts("impossible");
  } else {
    printf("%d\n", *possible.rbegin());
  }
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    work();
  }
  return 0;
}