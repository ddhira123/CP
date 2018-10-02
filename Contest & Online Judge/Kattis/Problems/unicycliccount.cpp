#include <bits/stdc++.h>
using namespace std;

const int N = 17;
const int MOD = 1e9 + 7;

int dp[N][1 << N];
int adj[N];
int n, m;

int modPow(int x, int po) {
  int ret = 1;
  while (po) {
    if (po & 1) ret = 1ll * ret * x % MOD;
    x = 1ll * x * x % MOD;
    po >>= 1;
  }
  return ret;
}


// actually this include contracted cycle
// however, as cofactor only needs minor
// i throw that row and column :P
vector<vector<int>> createLaplacianMatrix(vector<int> v) {
  vector<vector<int>> ret(v.size(), vector<int>(v.size(), 0));

  for (int i = 0 ; i < v.size() ; i++)
    for (int j = 0 ; j < v.size() ; j++)
      if (i == j)
        ret[i][j] = __builtin_popcount(adj[v[i]]);
      else {
        if (adj[v[i]] & (1 << v[j]))
          ret[i][j] = MOD-1;
        else
          ret[i][j] = 0;
      }
  
  return ret;
}

int gauss(vector<vector<int>> v) {
  int d = 1;

  for (int i = 0 ; i < v.size() ; i++) {
    int pos = -1;
    for (int j = i ; j < v.size() ; j++)
      if (v[j][i] != 0) {
        pos = j;
        break;
      }
    
    if (pos == -1) return 0;
    
    if (pos != i) {
      d = 1ll * d * (MOD-1) % MOD;
      swap(v[i], v[pos]);
    }

    int invert = modPow(v[i][i], MOD-2);
    d = 1ll * d * invert % MOD;

    for (int j = i ; j < v.size() ; j++) {
      v[i][j] = 1ll * invert * v[i][j] % MOD;
    }

    for (int j = i+1 ; j < v.size() ; j++)
      if (v[j][i] != 0) {
        int muls = (MOD - v[j][i]) % MOD;

        for (int k = i ; k < v.size() ; k++) {
          v[j][k] = (v[j][k] + 1ll * muls * v[i][k]) % MOD; 
        }
      }
  }

  int ret = 1;
  for (int i = 0 ; i < v.size() ; i++) ret = 1ll * ret * v[i][i] % MOD;

  return 1ll * ret * modPow(d, MOD-2) % MOD;
}

void read() {
  scanf("%d %d", &n, &m);

  for (int i = 0 ; i < m ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    u--; v--;

    adj[u] |= (1 << v);
    adj[v] |= (1 << u);
  }
}

int solve(int st, int cur, int mask) {
    if (mask == 0) return (adj[cur] & (1 << st)) > 0;

    int &ret = dp[cur][mask];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 0 ; i < n ; i++)
      if ((adj[cur] & (1 << i)) > 0 && (mask & (1 << i)) > 0) {
        ret = (ret + solve(st, i, mask ^ (1 << i))) % MOD;
      }
    
    return ret;
}

int work() {
  int ret = 0;
  for (int i = 0 ; i < n ; i++) {
    memset(dp, -1, sizeof dp);

    for (int mask = 0 ; mask < (1 << n) ; mask++)
      if (__builtin_popcount(mask) > 2 && (mask & -mask) == (1 << i)) {
        int ways = solve(i, i, mask ^ (1 << i));

        vector<int> v;
        for (int j = 0 ; j < n ; j++) 
          if ((mask & (1 << j)) == 0)
            v.push_back(j);
        
        vector<vector<int>> laplace = createLaplacianMatrix(v);
        int det = gauss(laplace);

        ret = (ret + 1ll * det * ways) % MOD;
      }
  }

  ret = 1ll * ret * modPow(2, MOD-2) % MOD;
  return ret;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}