// WA
#include <bits/stdc++.h>
using namespace std;

const int N = 305;

int n, k;
int a[N], b[N];
char s[N][N];
int inA[N];

void read() {
  scanf("%d %d", &n, &k);
  for(int i = 0 ; i < k ; i++) {
    scanf("%d", &a[i]);
    inA[a[i]] = i+1;
  }
  for (int i = 0; i < k; i++) {
    scanf("%d", &b[i]);
  }
  for(int i = 0 ; i < n ; i++) {
    scanf("%s", s[i]);
  }
}

int can[N][N];

void dfsMake(int st, int now) {
  if (can[st][now]) return;
  can[st][now] = true;
  // printf("can %d %d\n", st, now);

  for (int i = 0 ; i < n ; i++)
    if(s[now-1][i] == '1') {
      dfsMake(st, i+1);
    }
}

void prepare() {
  for (int i = 1 ; i <= n ; i++)
    dfsMake(i, i);
}

bool vis[N];
int match[N];

int augment(int now) {
  if (vis[now]) return 0;
  vis[now] = 1;

  for (int i = 0 ; i < k ; i++)
    if(can[now][b[i]] && (match[i] == -1 || augment(match[i]))) {
      match[i] = now;
      return 1;
    }
  
  return 0;
}

int dfsPar[N];

void dfs(int now) {
  for (int i = 0; i < n; i++)
    if (s[now - 1][i] == '1' && dfsPar[i+1] == -1) {
      dfsPar[i+1] = now;
      dfs(i+1);
    }
}

int mcbm() {
  memset(match, -1, sizeof match);
  int ret = 0;

  for (int i = 0 ; i < k ; i++) {
    memset(vis, 0, sizeof vis);
    int asd = augment(a[i]);

    // printf("%d %d %d\n", i, a[i], asd);
    ret += asd;
  }
  return ret;
}

void work() {
  if (mcbm() != k) {
    puts("NO");
  } else {
    puts("YES");
    vector<pair<int, int>> ans;

    vector<int> adj[k+1];
    vector<int> paths[k+1];
    int deg[k+1];
    memset(deg, 0, sizeof deg);

    for(int i = 0 ; i < k ; i++) {
      int st = match[i];
      memset(dfsPar, -1, sizeof dfsPar);
      dfs(st);

      vector<int> path;
      int now = b[i];
      while (now != st) {
        path.push_back(now);
        now = dfsPar[now];
      }
      path.push_back(now);

      reverse(path.begin(), path.end());
      
      int idxa = inA[st];
      paths[idxa] = path;
    }

    while(1) {
      bool yey = true;
      for (int i = 0 ; i < k ; i++)
        for(int j = i+1 ; j < k ; j++) {
          if (i != j) {
            bool ada1 = false;
            bool ada2 = false;
            for (int x : paths[j + 1]) ada1 |= (x == paths[i + 1].back());
            for (int x : paths[i + 1]) ada2 |= (x == paths[j + 1].back());

            if (ada1 && ada2) {
              yey = false;
              int a = paths[i+1].back();
              int b = paths[j+1].back();

              while (paths[i + 1].back() != b) paths[i + 1].pop_back();
              while (paths[j + 1].back() != a) paths[j + 1].pop_back();
            }
          }
        }
      if (yey) {
        break;
      }
    }

    for (int i = 0 ; i < k ; i++) {
      for (int x : paths[i+1]) {
        if (x != a[i] && inA[x] != 0) {
          adj[inA[x]].push_back(i+1);
          deg[i+1]++;

          // printf ("masuk %d %d\n", i+1, inA[x]);
        }
      }
    }

    for (int i = 0 ; i < k ; i++)
      for (int j = 0 ; j < k ; j++)
        if (i != j) {
          bool ada = false;
          for (int x : paths[j+1])
            ada |= (x == paths[i+1].back());
          if (ada) {
            adj[i+1].push_back(j+1);
          }
        }

    queue<int> q;
    for(int i = 0 ; i < k ; i++) {
      if (deg[i+1] == 0)
        q.push(i+1);
    }

    for (int it = 0 ; it < k ; it++) {
      assert(!q.empty());
      int now = q.front();
      q.pop();

      for (int i = 1 ; i < paths[now].size() ; i++) {
        ans.push_back({paths[now][i-1], paths[now][i]});
      }

      for (int nex : adj[now]) {
        deg[nex]--;
        if (deg[nex] == 0)
          q.push(nex);
      }
    }

    cout << ans.size() << endl;
    for (auto it : ans) {
      printf("%d %d\n", it.first, it.second);
    }
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}