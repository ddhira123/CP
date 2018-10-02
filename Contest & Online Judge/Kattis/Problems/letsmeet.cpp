#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 500;
const double EPS = 1e-9;
const int N = 22;

vector<int> adj[N];
double probs[2][N][N];
int n, m, s, t;

void read() {
  cin >> n >> m;
  for (int i = 0 ; i < m ; i++) {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  cin >> s >> t;
}

pair<bool, double> work() {
  pair<bool, double> ret = {0, 0.0};
  probs[0][s][t] = 1.0;

  for (int it = 0 ; it <= MAGIC ; it++) {
    int parity = it & 1;
    int nexpar = parity ^ 1;

    for (int i = 0 ; i < n ; i++)
      for (int j = 0 ; j < n ; j++)
        probs[nexpar][i][j] = 0;

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) 
        if (probs[parity][i][j] > 0) {
          if (i == j) {
            ret.first = true;
            ret.second += probs[parity][i][j] * it;
          } else {
            for (int iNex : adj[i])
              for (int jNex : adj[j])
                probs[nexpar][iNex][jNex] += probs[parity][i][j] / (adj[i].size() * adj[j].size());
          }
        }
  }
  
  return ret;
}

int main() {
  read();
  pair<bool, double> ret = work();

  if (ret.first) printf("%.9lf\n", ret.second);
  else printf("never meet\n");

  return 0;
}