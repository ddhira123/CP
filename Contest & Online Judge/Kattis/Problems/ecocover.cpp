#include <bits/stdc++.h>
using namespace std;

struct Dinic {
  static const int N = 10005;

  struct Edge {
    int from;
    int to;
    int flow;
	};

	vector<Edge> elist;
	vector<int> adj[N];
	int saiz;

	int ptr[N];
	int dist[N];

	int source,sink;
	int num;

	Dinic(int _s = 0,int _t = 0,int _num = 0) {
		source = _s;
		sink = _t;
		num = _num;
		reset();
	}

	void reset() {
		for(int i = 0 ; i <= num ; i++)
			adj[i].clear();
		elist.clear();
		saiz = 0;
	}

	void add_edge(int from,int to,int flow) {
		adj[from].push_back(saiz++);
		adj[to].push_back(saiz++);

		elist.push_back((Edge){from,to,flow});
		elist.push_back((Edge){to,from,flow});

    // printf("add edge %d -> %d flow %d\n", from, to, flow);
	}

	bool BFS() {
		for(int i = 0 ; i <= num ; i++)
			dist[i] = -1;
		queue<int> q;
		q.push(source);
		dist[source] = 0;

		while(!q.empty() && dist[sink] == -1) {
			int now = q.front();
			q.pop();
			for(int idx : adj[now]) {
				int to = elist[idx].to;
				int flow = elist[idx].flow;

				if(dist[to] == -1 && flow > 0) {
					dist[to] = dist[now] + 1;
					q.push(to);
				}
			}
		}

		return dist[sink] != -1;
	}

	int augment(int now,int f) {
		if(now == sink)
			return f;

		for(int &i = ptr[now] ; i < adj[now].size() ; i++) {
			int idx = adj[now][i];
			int to = elist[idx].to;
			int flow = elist[idx].flow;

			if(dist[to] == dist[now] + 1 && flow > 0) {
				int res = augment(to,min(f,flow));
				if(res > 0) {
					elist[idx].flow -= res;
					elist[idx ^ 1].flow += res;
					return res;
				}
			}
		}

		return 0;
	}

	int maxFlow() {
		int mf = 0;
		while(BFS()) {
			for(int i = 0 ; i <= num ; i++)
				ptr[i] = 0;
			int add = augment(source,(int)1e9);
			while(add > 0) {
				mf += add;
				add = augment(source,(int)1e9);
			}
		}
		return mf;
	} 
};

const int N = 45;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

int arr[N][N];
int n, m, k;

Dinic network;

int getID(int r, int c) {
  return r * m + c;
}

void read() {
  cin >> n >> m >> k;
  for (int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < m ; j++)
      cin >> arr[i][j];
}

void prepare() {
  int source = getID(n-1,m-1)+1;
  int sink = source+1;
  network = Dinic(source, sink, sink);

  for (int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < m ; j++) {
      if ((i + j) % 2 == 0) {
        network.add_edge(source, getID(i, j), arr[i][j]);

        for (int it = 0 ; it < 4 ; it++) {
          int ni = i + dr[it];
          int nj = j + dc[it];

          if (ni >= 0 && nj >= 0 && ni < n && nj < m) {
            network.add_edge(getID(i, j), getID(ni, nj), k);
          }
        }
      } else {
        network.add_edge(getID(i, j), sink, arr[i][j]);
      }
    }
}

int main() {
  read();
  prepare();
  printf("%d\n", network.maxFlow());
  return 0;
}