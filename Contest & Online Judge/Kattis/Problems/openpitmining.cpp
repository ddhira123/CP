#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int INF = 1e9;

struct Dinic {
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
        elist.push_back((Edge){to,from,0});
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
            int add = augment(source, INF);
            while(add > 0) {
                mf += add;
                add = augment(source, INF);
            }
        }
        return mf;
    } 
};

Dinic network;
int sink, source;

int v[N], c[N];
vector<int> blocks[N];
int n;

void read() {
    scanf("%d", &n);

    for(int i = 1 ; i <= n ; i++) {
        scanf("%d %d", &v[i], &c[i]);
        int m; scanf("%d", &m);

        for(int j = 0 ; j < m ; j++) {
            int x; scanf("%d", &x);
            blocks[i].push_back(x);
        }
    }
}

void prepare() {
    source = 0;
    sink = n+1;

    network = Dinic(source, sink, sink);

    for(int i = 1 ; i <= n ; i++) {
        int w = v[i] - c[i];

        if(w >= 0) {
            network.add_edge(source, i, w);
        } else {
            network.add_edge(i, sink, -w);
        }
    }

    for(int i = 1 ; i <= n ; i++) {
        for(int x : blocks[i]) {
            network.add_edge(x, i, INF);
        }
    }
}

int work() {
    int ret = 0;

    for(int i = 1 ; i <= n ; i++) {
        int w = v[i] - c[i];

        if(w >= 0) {
            ret += w;
        }
    }

    int min_cut = network.maxFlow();

    return ret - min_cut;
}

int main() {
    read();
    prepare();
    printf("%d\n", work());
    return 0;
}