#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int M = 2e5 + 5;

struct Packet {
  int a, b, p;

  void read() {
    scanf("%d %d %d", &a, &b, &p);
  }
};

int n, m, s;
Packet packets[M];
long long dp[N];

void read() {
  scanf("%d %d %d", &n, &m, &s);
  for (int i = 1 ; i <= m ; i++) {
    packets[i].read();
  }
}

long long work() {
  sort(packets + 1, packets + m + 1, [](Packet a, Packet b) {
    return a.b > b.b;
  });
  priority_queue<pair<long long, int>> pq;
  
  dp[n+1] = 0;
  for (int i = n, j = 1 ; i >= 1 ; i--) {
    while (!pq.empty() && pq.top().second > i) {
      pq.pop();
    }
    while (j <= m && packets[j].b == i) {
      pq.push({-(dp[i+1] + packets[j].p), packets[j].a});
      j++;
    }

    dp[i] = s + dp[i+1];
    if (!pq.empty()) dp[i] = min(dp[i], -pq.top().first);
  }

  return dp[1];
}

int main() {
  read();
  printf("%lld\n", work());
  return 0;
}
