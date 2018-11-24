#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

long long ans[N];
int n, m;
int x[N], y[N];
int u[N], v[N];

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d %d", x + i, y + i);
  }
  for (int i = 0 ; i < m ; i++) {
    scanf("%d %d", u + i, v + i);
  }
}

void rev() {
  for (int i = 1 ; i <= n ; i++)
    swap(x[i], y[i]);
}

void run(bool countSame) {
  vector<pair<int, int>> v;

  for (int i = 1 ; i <= n ; i++) {
    v.push_back({x[i] - y[i], i});
  }

  sort(v.begin(), v.end());

  long long sumY = 0;
  long long sumX = 0;
  for (int i = 1 ; i <= n ; i++)
    sumY += y[i];
  
  for (int i = 0 ; i < v.size() ; ) {
    int j = i;
    while (j < v.size() && v[j].first == v[i].first) {
      sumY -= y[v[j].second];
      j++;
    }

    //  strictly kurang dari
    for (int k = i ; k < j ; k++) {
      int idx = v[k].second;

      // dapet dari bawah
      ans[idx] += sumX;
      ans[idx] += 1ll * i * y[idx];
      // printf("%lld\n", ans[idx]);

      // dapet dari atas
      ans[idx] += sumY;
      ans[idx] += 1ll * (n-j) * x[idx];
      // printf("sumY %lld j %d x %d %lld\n", sumY, j, x[idx], ans[idx]);

      // printf("%d idx %d -> %lld\n", countSame, idx, ans[idx]);
    }

    // yang sama
    if (countSame) {
      long long curY = 0;
      for (int k = i ; k < j ; k++)
        curY += y[v[k].second];
      
      for (int k = i ; k < j ; k++) {
        int idx = v[k].second;

        ans[idx] += 1ll * (j-i-1) * x[idx];
        ans[idx] += (curY - y[idx]);
      }
    }

    for (int k = i ; k < j ; k++)
      sumX += x[v[k].second];
    
    i = j;
  }
}

void work() {
  run(1);
  // rev();
  // run(0);
  // rev();

  for (int i = 0 ; i < m ; i++) {
    int a = u[i];
    int b = v[i];

    long long use = min(x[a] + y[b], x[b] + y[a]);

    ans[a] -= use;
    ans[b] -= use;
  }

  for (int i = 1 ; i <= n ; i++) printf("%lld ", ans[i]);
  puts("");
}

int main() {
  read();
  work();
  return 0;
}