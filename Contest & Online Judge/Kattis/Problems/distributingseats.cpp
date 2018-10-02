#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, r, c;
vector<int> v[N];

void read() {
  scanf("%d %d %d", &n, &r, &c);
  for (int i = 0 ; i < n ; i++) {
    int rr, cc, s;
    scanf("%d %d %d", &rr, &cc, &s);

    v[max(1, rr-s)].push_back(min(r, rr+s));
  }
}

int work() {
  priority_queue<int> pq;
  int ans = 0;

  for (int i = 1 ; i <= r ; i++) {
    while(!pq.empty() && -pq.top() < i) pq.pop();
    for (int x : v[i]) pq.push(-x);

    int seat = c;
    while (!pq.empty() && seat > 0) {
      pq.pop();
      seat--;
      ans++;
    }
  }

  return ans;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}