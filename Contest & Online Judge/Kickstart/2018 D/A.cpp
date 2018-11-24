#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
const long long INF = 1e16;

int x[N], s[N];
long long sum[N];
int odds[N];
int n;
int o;
long long d;
int a, b, c, m, l;

void read() {
  scanf("%d %d %lld", &n, &o, &d);
  scanf("%d %d %d %d %d %d %d", &x[1], &x[2], &a, &b, &c, &m, &l);
}

void prepare() {
  for(int i = 3 ; i <= n ; i++) {
    x[i] = (1ll * x[i-1] * a + 1ll * x[i-2] * b + c) % m;
  }
  for(int i = 1 ; i <= n ; i++) {
    s[i] = x[i] + l;
    odds[i] = (odds[i-1]) + (s[i] % 2 != 0);
    sum[i] = sum[i-1] + s[i];

    // cout << i << " " << s[i] << endl;
  }
}

long long work() {
  multiset<long long> st;
  st.insert(d);
  int j = 0;
  long long ret = -INF;

  for (int i = 1; i <= n; i++) {
    // cout << "asd " << i << endl;
    while(odds[i] - odds[j] > o) {
      auto it = st.lower_bound(d + sum[j]);
      st.erase(it);
      j++;
    }

    // cout << i << " " << sum[i] << endl;
    // cout << j << endl;
    // cout << "isi :";
    // for(auto x : st) cout << x << " ";
    // cout << endl;

    auto it = st.lower_bound(sum[i]);
    if(it != st.end() && (sum[i] - *it + d <= d)) {
      ret = max(ret, sum[i] - *it + d);
    }
    st.insert(d + sum[i]);
  }

  return ret;
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    cerr << "now " << tc << endl;
    read();
    prepare();

    printf("Case #%d: ", tc);
    long long ret = work();
    if(ret == -INF) printf("IMPOSSIBLE\n");
    else printf("%lld\n", ret);
  }
  return 0;
}