#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

vector<int> adj[3 * N];
int low[3 * N], num[3 * N];
int vis[3 * N];
vector<int> stek;
int components;

int a[N], b[N];
int n, k;


void read() {
  scanf("%d %d", &n, &k);
  for (int i = 0 ; i < n ; i++) scanf("%d", &a[i]);
  for (int i = 0 ; i < n ; i++) scanf("%d", &b[i]);
}

void prepareDummy() {
  for (int i = 1 ; i < n ; i++) {
    adj[i].push_back(i-1);
    adj[n+i].push_back(n+i-1);
  }
}

void prepareA() {
  vector<pair<int, int>> v;
  for (int i = 0 ; i < n ; i++) v.push_back({a[i], i});
  sort(v.begin(), v.end());

  for (int i = 0 ; i < n ; i++) {
    int cur = v[i].second;
    pair<int, int> temp = {v[i].first-k, -1};

    int idx = lower_bound(v.begin(), v.end(), temp) - v.begin();
    if (idx > 0) {
      adj[2 * n + cur].push_back(idx-1);
      // printf("from a %d -> %d\n", cur, idx-1);
    }
  }

  for(int i = 0 ; i < n ; i++) {
    adj[i].push_back(2*n + v[i].second);
  }
}

void prepareB() {
  vector<pair<int, int>> v;
  for (int i = 0; i < n; i++) v.push_back({b[i], i});
  sort(v.begin(), v.end());

  for (int i = 0; i < n; i++) {
    int cur = v[i].second;
    pair<int, int> temp = {v[i].first - k, -1};

    int idx = lower_bound(v.begin(), v.end(), temp) - v.begin();
    if (idx > 0) {
      adj[2 * n + cur].push_back(n + idx - 1);

      // printf("from b %d -> %d\n", cur, idx - 1);
    }
  }

  for (int i = 0; i < n; i++) {
    adj[n+i].push_back(2*n + v[i].second);
  }
}

void prepare() {
  prepareDummy();
  prepareA();
  prepareB();
}

void tarjan(int now) {
  // printf("now %d\n", now);
  static int cnt = 0;

  low[now] = num[now] = cnt++;
  vis[now] = 1;
  stek.push_back(now);

  // printf("low %d num %d\n", low[now], num[now]);

  for (int nex : adj[now]) {
    if (vis[nex] == 0) tarjan(nex);
    if (vis[nex] == 1) {
      low[now] = min(low[now], low[nex]);
    }
  }

  // printf("%d %d %d\n", now, low[now], num[now]);

  if (low[now] == num[now]) {
    bool ada = 0;

    while(1) {
      int bk = stek.back();
      stek.pop_back();
      vis[bk] = 2;
      ada |= (bk >= 2 * n);
      // printf("bk %d\n", bk);

      if (bk == now) {
        break;
      }
    }

    components += ada;
  }
}

int work() {
  for (int i = 2*n ; i < 3*n ; i++)
    if (vis[i] == 0)
      tarjan(i);
  return components;
}

int main() {
  read();
  prepare();
  printf("%d\n", work());
  return 0;
}