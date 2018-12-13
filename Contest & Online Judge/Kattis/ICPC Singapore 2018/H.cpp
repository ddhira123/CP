#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
char arah[4] = {'^', 'v', '<', '>'};

map<pair<int, int>, int> idxs;
pair<int, int> arr[N];
vector<int> adj[N];
int deg[N];
set<pair<int, int>> byX, byY;
bool vis[N];
int val[N];
int R, C, n;

void addEdge(int from, int to) {
  // printf("%d -> %d\n", from, to);
  deg[to]++;
  adj[from].push_back(to);
}

void dfs(int idx) {
  vis[idx] = true;
  int r = arr[idx].first;
  int c = arr[idx].second;

  for (int i = 0 ; i < 4 ; i++) {
    int nr = dr[i] + r;
    int nc = dc[i] + c;

    if (idxs.count({nr, nc})) {
      int nIdx = idxs[{nr, nc}];

      if (!vis[nIdx]) {
        addEdge(idx, nIdx);

        val[nIdx] = 1 ^ i;
        dfs(nIdx);
      }
    } 
  }
}

void read() {
  scanf("%d %d %d", &R, &C, &n);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d %d", &arr[i].first, &arr[i].second);
  }
}

void prepare() {
  for (int i = 1 ; i <= n ; i++) {
    idxs[arr[i]] = i;
    byX.insert(arr[i]);
    byY.insert({arr[i].second, arr[i].first});
  }

  dfs(1);

  for (int i = 2 ; i <= n ; i++) {
    // printf("i %d val %d\n", i, val[i]);
    if (val[i] == 2) { // cek dari bawah, y++
      auto it = byX.lower_bound(arr[i]);
      it++;

      if (it == byX.end()) continue;
      pair<int, int> cur = *it;

      if (cur.first != arr[i].first) continue;
      int idx = idxs[cur];

      addEdge(i, idx);
    } else if (val[i] == 3) { // cek dari atas, y--
      auto it = byX.lower_bound(arr[i]);
    
      if (it == byX.begin()) continue;
      it--;
      pair<int, int> cur = *it;

      if (cur.first != arr[i].first) continue;
      int idx = idxs[cur];

      addEdge(i, idx);
    } else if (val[i] == 0) { // cek dari kanan, x++
      pair<int, int> tmp = {arr[i].second, arr[i].first};

      auto it = byY.lower_bound(tmp);
      it++;

      if (it == byY.end()) continue;
      pair<int, int> cur = *it;

      if (cur.first != arr[i].second) continue;
      swap(cur.first, cur.second);
      int idx = idxs[cur];

      addEdge(i, idx);
    } else { // cek dari kiri, x--
      pair<int, int> tmp = {arr[i].second, arr[i].first};

      auto it = byY.lower_bound(tmp);
      if (it == byY.begin()) continue;

      it--;
      if (it == byY.end()) continue;
      pair<int, int> cur = *it;

      if (cur.first != arr[i].second) continue;
      swap(cur.first, cur.second);
      int idx = idxs[cur];

      addEdge(i, idx);
    }
  }
}

void work() {
  queue<int> q;
  for (int i = 1 ; i <= n ; i++) 
    if(deg[i] == 0) {
      q.push(i);
    }
  
  vector<pair<int, char>> ans;
  while (!q.empty()) {
    int now = q.front();
    q.pop();

    if (now != 1) {
      if (val[now] < 2) ans.push_back({arr[now].second, arah[val[now]]});
      if (val[now] >= 2) ans.push_back({arr[now].first, arah[val[now]]});
    }

    for (int nex : adj[now]) {
      deg[nex]--;
      if (deg[nex] == 0) {
        q.push(nex);
      }
    }
  }

  if (ans.size() != n-1) {
    puts("impossible");
  } else {
    puts("possible");
    for (auto it : ans) {
      printf("%c %d\n", it.second, it.first);
    }
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}