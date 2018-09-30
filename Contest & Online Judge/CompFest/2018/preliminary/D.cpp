#include <bits/stdc++.h>
using namespace std;

const int N = 205;

int BIT[N * N];
vector<int> v;
int arr[N * N];
int n;

int get_idx(int x) {
  return lower_bound(v.begin(), v.end(), x) - v.begin();
}

int get_rev_idx(int x) {
  return v.size() - get_idx(x);
}

void update(int x, int val) {
  for(; x <= n * n ; x += x & -x)
    BIT[x] = max(BIT[x], val);
}

int query(int x) {
  int ret = 0;
  while(x > 0) {
    ret = max(BIT[x], ret);
    x -= x & -x;
  }
  return ret;
}

pair<int, int> lis() {
  memset(BIT, 0, sizeof BIT);
  pair<int, int> ret = {-1, 2e9};

  for(int i = 1 ; i <= n * n ; i++) {
    int idx = get_idx(arr[i]);
    int mx = query(idx - 1) + 1;

    if(ret.first < mx)
      ret = {mx, 2e9};
    if(ret.first == mx)
      ret.second = min(ret.second, arr[i] + 1);
    
    update(idx, mx);
  }

  return ret;
}

pair<int, int> lds() {
  memset(BIT, 0, sizeof BIT);
  pair<int, int> ret = {-1, -2e9};

  for (int i = 1; i <= n * n; i++) {
    int idx = get_rev_idx(arr[i]);
    int mx = query(idx - 1) + 1;

    if (ret.first < mx) ret = {mx, -2e9};
    if (ret.first == mx) ret.second = max(ret.second, arr[i] - 1);

    update(idx, mx);
  }

  return ret;
}

void read() {
  scanf("%d", &n);

  for(int i = 1 ; i <= n * n ; i++) {
    scanf("%d", &arr[i]);
  }
}

void prepare() {
  v.clear();
  v.push_back(-2e9);
  for(int i = 1 ; i <= n * n ; i++) {
    v.push_back(arr[i]);
  }
  sort(v.begin(), v.end());
}

void work() {
  pair<int, int> up = lis();
  pair<int, int> dw = lds();

  if(up.first > n || dw.first > n)
    puts("0");
  else {
    int ans = 2e9;
    set<int> st;
    for(int i = 1 ; i <= n * n ; i++) st.insert(arr[i]);
    if(up.first == n)  {
      int i = max(1, up.second);
      while(st.count(i)) i++;
      ans = min(ans, i);
    }
    if(dw.first == n && dw.second >= 1) {
      int i = 1;
      while(i <= dw.second && st.count(i)) i++;
      if(i <= dw.second) ans = min(ans, i);
    }
    assert(up.first == n || dw.first == n);
    printf("1\n%d\n", ans);
  }
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    prepare();
    work();
  }
  return 0;
}