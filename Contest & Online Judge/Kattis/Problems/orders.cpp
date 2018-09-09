#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int MX = 30005;

vector<int> prv[MX];

int n;
int arr[N];

void read() {
  scanf("%d", &n);
  for(int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
  }
}

void prepare() {
  prv[0].push_back(0);

  for(int i = 1 ; i <= n ; i++) {
    for(int j = arr[i] ; j < MX ; j++) {
      if(!prv[j - arr[i]].empty() && prv[j].size() < 2) {
        prv[j].push_back(i);
      }
    }
  }
}

void solve(int x) {
  vector<int> ret;
  
  if(prv[x].empty()) {
    puts("Impossible");
    return;
  }

  while(x > 0) {
    if(prv[x].size() == 2) {
      puts("Ambiguous");
      return;
    }

    ret.push_back(prv[x][0]);
    x -= arr[prv[x][0]];
  }

  for(int i = ret.size()-1 ; i >= 0 ; i--) {
    printf("%d%c", ret[i], i == 0 ? '\n' : ' ');
  }
}

void work() {
  int q; scanf("%d", &q);
  for(int i = 0 ; i < q ; i++) {
    int x; scanf("%d", &x);

    solve(x);
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}