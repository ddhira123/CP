#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

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
            int add = augment(source,(int)1e9);
            while(add > 0) {
                mf += add;
                add = augment(source,(int)1e9);
            }
        }
        return mf;
    } 
};

Dinic network;
int n;
int start, g, s;
int m;

int source, sink;

int get_id(int pos, int t) {
    return t * n + pos;
}

void init() {
    scanf("%d %d %d %d", &n, &start, &g, &s);
    start--;

    source = get_id(n-1, s) + 1;
    sink = source + 1;

    network = Dinic(source, sink, sink);
    network.add_edge(source, get_id(start, 0), g);

    scanf("%d", &m);
    for(int i = 0 ; i < m ; i++) {
        int x; scanf("%d", &x);
        x--;

        for(int j = 0 ; j <= s ; j++) {
            network.add_edge(get_id(x, j), sink, g);
        }
    }

    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < s ; j++) {
            network.add_edge(get_id(i, j), get_id(i, j+1), g);
        }

    int r; scanf("%d", &r);
    for(int i = 0 ; i < r ; i++) {
        int a, b, p, t;
        scanf("%d %d %d %d", &a, &b, &p, &t);
        a--; b--;

        for(int j = 0 ; j + t <= s ; j++) {
            network.add_edge(get_id(a, j), get_id(b, j+t), p);
        }
    }
}

int work() {
    return network.maxFlow();
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        init();
        printf("%d\n", work());
    }
    return 0;
}