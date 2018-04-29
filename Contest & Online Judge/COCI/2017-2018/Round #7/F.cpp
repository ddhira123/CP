#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int NN = 1005;
const int INF = 8e6 + 5;

struct Point {
    int x, y;

    void read() {
        scanf("%d %d", &x, &y);
    }
};

int sqr(int x) {
    return x * x;
}

int euclid(Point a, Point b) {
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}

struct Dinic {
    struct Edge {
        int from;
        int to;
        int flow;
    };

    vector<Edge> elist;
    vector<int> adj[NN];
    int source;
    int sink;
    int sz;

    int dist[NN];
    int ptr[NN];

    void init(int _source, int _sink, int _sz) {
        source = _source;
        sink = _sink;
        sz = _sz;

        elist.clear();
        for(int i = 0 ; i <= sz ; i++) {
            adj[i].clear();
        }
    }

    void add_edge(int from, int to, int flow) {
        adj[from].push_back(elist.size());
        elist.push_back((Edge){from, to, flow});

        adj[to].push_back(elist.size());
        elist.push_back((Edge){to, from, 0});
    }

    bool bfs() {
        queue<int> q;

        for(int i = 0 ; i <= sz ; i++) {
            dist[i] = -1;
        }

        dist[source] = 0;
        q.push(source);

        while(!q.empty()) {
            int now = q.front();
            q.pop();

            for(int edge : adj[now]) {
                int to = elist[edge].to;
                int flow = elist[edge].flow;

                if(flow > 0 && dist[to] == -1) {
                    dist[to] = dist[now] + 1;
                    q.push(to);
                }
            }
        }

        return dist[sink] != -1;
    }

    int augment(int now, int f) {
        if(now == sink) {
            return f;
        }

        for(int &i = ptr[now] ; i < adj[now].size() ; i++) {
            int idx = adj[now][i];
            int to = elist[idx].to;
            int flow = elist[idx].flow;

            if(dist[to] == dist[now] + 1 && flow > 0) {
                int val = augment(to, min(f, flow));

                if(val > 0) {
                    elist[idx].flow -= val;
                    elist[idx ^ 1].flow += val;

                    return val;
                }
            }
        }

        return 0;
    }

    int max_flow() {
        int ret = 0;

        while(bfs()) {
            for(int i = 0 ; i <= sz ; i++) {
                ptr[i] = 0;
            }

            int val = augment(source, INF);
            while(val > 0) {
                ret += val;
                val = augment(source, INF);
            }
        }

        return ret;
    }
};

int n, m, c, k;

Point students[N];
Point stops[N];
vector<int> bus[N];

Dinic network;

int source, sink;

void make_graph(int lmt) {
    network.init(source, sink, sink);

    for(int i = 0 ; i < n ; i++) {
        network.add_edge(source, i + 1, 1);
    }

    for(int i = 0 ; i < k ; i++) {
        network.add_edge(i + n + 1, sink, c);
    }

    // static bool first = 1;

    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < k ; j++) {
            int mins = INF + 5;

            for(int x : bus[j]) {
                mins = min(mins, euclid(students[i], stops[x]));
            }

            if(mins <= lmt) {
                network.add_edge(i + 1, j + n + 1, 1);
            }
        }
    }

    // first = 0;
}

bool check(int lmt) {
    make_graph(lmt);
    int ret = network.max_flow();

    return ret == n;
}

void read() {
    scanf("%d %d %d %d", &n, &m, &c, &k);

    for(int i = 0 ; i < n ; i++) {
        students[i].read();
    }

    for(int i = 0 ; i < m ; i++) {
        stops[i].read();
    }

    for(int i = 0 ; i < k ; i++) {
        int sz; scanf("%d", &sz);

        for(int j = 0 ; j < sz ; j++) {
            int x; scanf("%d", &x);

            bus[i].push_back(x-1);
        }
    }
}

void work() {
    source = 0, sink = n + k + 1;

    // cout << check(4) << endl;

    if(!check(INF)) {
        cout << "-1\n";
        return;
    }

    int lo = 0, hi = INF;
    while(lo < hi) {
        int mid = (lo + hi) / 2;

        if(check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    check(lo);
    printf("%d\n", lo);

    for(int i = 0 ; i < n ; i++) {
        for(int edge : network.adj[i+1]) {

            if(network.elist[edge].flow == 0) {
                int bus_idx = network.elist[edge].to - n - 1;
                
                for(int stop : bus[bus_idx]) {
                    int dist = euclid(students[i], stops[stop]);

                    if(dist <= lo) {
                        printf("%d\n", stop + 1);
                        break;
                    }
                }

                break;
            }
        }
    }
}

int main() {
    read();
    work();
    return 0;
}