#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

int dp[N][2][2];
vector<int> adj[N];
vector<int> rAdj[N];
int deg[N];
int n;

bool isValidStart(int x) {
  for(int i = 0 ; i < 2 ; i++)
    for(int j = 0 ; j < 2 ; j++)
      if (dp[x][i][j] != -1)
        return 0;
  return 1;
}

void read() {
  scanf("%d", &n);
  for(int i = 1 ; i <= n ; i++) {
    int x; scanf("%d", &x);
    adj[i].push_back(x);
    rAdj[x].push_back(i);
  }
}

int solve(int st, int now, int startVal, int val) {
  int &ret = dp[now][startVal][val];
  if (ret != -1) return ret;

  ret = val == 1;
  for (int nex : rAdj[now]) {
    if(nex == st) {
      if (startVal == 1 && val == 1) {
        return ret = -1e9;
      }
    } else {
      if (val == 1) {
        ret += solve(st, nex, startVal, 0);
      } else {
        ret += max(solve(st, nex, startVal, 0), solve(st, nex, startVal, 1));
      }
    }
  }

  return ret;
}

int work() {
  int ret = 0;
  
  for(int i = 1 ; i <= n ; i++)
    for(int x : adj[i])
      deg[x]++;
  
  queue<int> q;
  for(int i = 1 ; i <= n ; i++)
    if(deg[i] == 0)
      q.push(i);
  
  while(!q.empty()) {
    int now = q.front();
    q.pop();

    for(int nex : adj[now]) {
      deg[nex]--;
      if(deg[nex] == 0)
        q.push(nex);
    }
  }

  for(int i = 1 ; i <= n ; i++) {
    if (deg[i] > 0 && isValidStart(i)) {
      // printf("start %d\n", i);
      ret += max(solve(i, i, 0, 0), solve(i, i, 1, 1));
    }
  }

  return ret;
}

int main() {
  read();
  memset(dp, -1, sizeof dp);
  printf("%d\n", work());
  return 0;
}