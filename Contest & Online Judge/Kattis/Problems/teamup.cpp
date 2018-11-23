#include <bits/stdc++.h>
using namespace std;

const int MX = 5e5 + 5;

int sz[MX];
vector<int> skill[MX];
vector<int> withClass[MX];

vector<int> chld[MX];
int dominating[MX];

vector<int> ans[MX];

int n, m, p;

void read() {
  scanf("%d %d %d", &n, &m, &p);
  
  for (int i = 1 ; i <= m ; i++) {
    scanf("%d", &sz[i]);

    for (int j = 0 ; j < sz[i] ; j++) {
      int x; scanf("%d", &x);
      skill[i].push_back(x);
    }
  }

  for (int i = 1 ; i <= p ; i++) {
    int x; scanf("%d", &x);
    withClass[x].push_back(i);
  }
}

void prepare() {
  vector<int> v(m+1);
  iota(v.begin(), v.end(), 0);
  sort(v.begin()+1, v.end(), [&](int a, int b) {
    return sz[a] > sz[b];
  });

  for (int i = 1 ; i <= n ; i++) {
    skill[0].push_back(i);
  }

  for (int i = 1 ; i <= m ; i++) {
    // printf("i %d v %d\n", i, v[i]);
    int idx = v[i];
    int dom = dominating[skill[idx][0]];
    chld[dom].push_back(idx);

    for (int x : skill[idx]) {
      assert(dominating[x] == dom);
      dominating[x] = idx;
    }
  }
}

int dfs(int now) {
  int ret = withClass[now].size();

  if (!chld[now].empty()) {
    set<int> sk;
    for (int x : skill[now]) {
      sk.insert(x);
    }

    int mins = 1e9;
    for (int x : chld[now]) {
      mins = min(mins, dfs(x));
      for (int xsk : skill[x]) {
        sk.erase(xsk);
      }
    }

    if (sk.empty())
      ret += mins;
  }

  return ret;
}

void construct(int now, int lft) {
  int mins = min(lft, (int)withClass[now].size());

  for (int i = 0 ; i < mins ; i++) {
    ans[lft-i].push_back(withClass[now][i]);
  }

  lft -= mins;
  for (int nex : chld[now]) {
    construct(nex, lft);
  }

  assert(lft == 0 || !chld[now].empty());
}

void work() {
  int ret = dfs(0);
  construct(0, ret);
  // puts("non");
  printf("%d\n", ret);
  for (int i = 1 ; i <= ret ; i++) {
    printf("%d", (int)ans[i].size());
    sort(ans[i].begin(), ans[i].end());

    for (int x : ans[i]) printf(" %d", x);
    puts("");
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}