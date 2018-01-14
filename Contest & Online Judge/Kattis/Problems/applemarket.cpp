#include <bits/stdc++.h>
using namespace std;

const long long INF = 4e18;

struct Dinic {
    struct Edge {
        int from;
        int to;
        long long flow;
    };

    const static int N = 120005;

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

    void add_edge(int from,int to, long long flow) {
        if(flow == 0) return;

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
                long long flow = elist[idx].flow;

                if(dist[to] == -1 && flow > 0) {
                    dist[to] = dist[now] + 1;
                    q.push(to);
                }
            }
        }

        return dist[sink] != -1;
    }

    long long augment(int now, long long f) {
        if(now == sink)
            return f;

        for(int &i = ptr[now] ; i < adj[now].size() ; i++) {
            int idx = adj[now][i];
            int to = elist[idx].to;
            long long flow = elist[idx].flow;

            if(dist[to] == dist[now] + 1 && flow > 0) {
                long long res = augment(to, min(f,flow));

                if(res > 0) {
                    elist[idx].flow -= res;
                    elist[idx ^ 1].flow += res;
                    return res;
                }
            }
        }

        return 0;
    }

    long long maxFlow() {
        long long mf = 0;
        while(BFS()) {
            for(int i = 0 ; i <= num ; i++)
                ptr[i] = 0;
            long long add = augment(source,INF);

            while(add > 0) {
                mf += add;
                add = augment(source,INF);
            }
        }
        return mf;
    } 
};

const int SOURCE = 0;
const int SINK = 1;
const int N = 65;

Dinic network;

int node_cnt = 1;
int node_num[N][N][N][N];
int arr[N][N];

int n, m, k;

void make_inner_num(int r1, int r2, int c1, int c2) {
    node_num[r1][r2][c1][c2] = ++node_cnt;

    if(c1 < c2) {
        int m = (c1 + c2) / 2;

        make_inner_num(r1, r2, c1, m);
        make_inner_num(r1, r2, m+1, c2);
    }
}

void make_outer_num(int r1, int r2) {
    make_inner_num(r1, r2, 1, m);

    if(r1 < r2) {
        int m = (r1 + r2) / 2;

        make_outer_num(r1, m);
        make_outer_num(m+1, r2);
    }
}

void make_inner_flow(int r1, int r2, int c1, int c2) {
    if(r1 < r2) {
        int m = (r1 + r2) / 2;

        network.add_edge(node_num[r1][r2][c1][c2], node_num[r1][m][c1][c2], INF);
        network.add_edge(node_num[r1][r2][c1][c2], node_num[m+1][r2][c1][c2], INF);
    } else {
        if(c1 == c2) {
            network.add_edge(node_num[r1][r2][c1][c2], SINK, arr[r1][c1]);
        } else {
            int m = (c1 + c2) / 2;

            network.add_edge(node_num[r1][r2][c1][c2], node_num[r1][r2][c1][m], INF);
            network.add_edge(node_num[r1][r2][c1][c2], node_num[r1][r2][m+1][c2], INF);
        }
    }

    if(c1 < c2) {
        int m = (c1 + c2) / 2;

        make_inner_flow(r1, r2, c1, m);
        make_inner_flow(r1, r2, m+1, c2);
    }
}

void make_outer_flow(int r1, int r2) {
    make_inner_flow(r1, r2, 1, m);

    if(r1 < r2) {
        int m = (r1 + r2) / 2;

        make_outer_flow(r1, m);
        make_outer_flow(m+1, r2);
    }
}

void add_inner_flow(int src, int r1, int r2, int c1, int c2, int lc, int rc, int val) {
    if(lc <= c1 && c2 <= rc) {
        network.add_edge(src, node_num[r1][r2][c1][c2], val);
    } else {
        int m = (c1 + c2) / 2;

        if(lc <= m) add_inner_flow(src, r1, r2, c1, m, lc, rc, val);
        if(rc > m)  add_inner_flow(src, r1, r2, m+1, c2, lc, rc, val);
    }
}

void add_outer_flow(int src, int r1, int r2, int lr, int rr, int lc, int rc, int val) {
    if(lr <= r1 && r2 <= rr) {
        add_inner_flow(src, r1, r2, 1, m, lc, rc, val);
    } else {
        int m = (r1 + r2) / 2;

        if(lr <= m) add_outer_flow(src, r1, m, lr, rr, lc, rc, val);
        if(rr > m)  add_outer_flow(src, m+1, r2, lr, rr, lc, rc, val);
    }
}

void adder(int src, int r1, int r2, int c1, int c2, int val) {
    add_outer_flow(src, 1, n, r1, r2, c1, c2, val);
}

void init() {
    make_outer_num(1, n);

    // cout << "num done\n";
    // cout << node_cnt << endl;

    network = Dinic(SOURCE, SINK, node_cnt + k);

    make_outer_flow(1, n);

    // cout << "flows done\n";

    for(int i = 1 ; i <= k ; i++) {
        int r1, r2, c1, c2, x;
        scanf("%d %d %d %d %d", &r1, &r2, &c1, &c2, &x);

        node_cnt++;

        network.add_edge(SOURCE, node_cnt, x);
        adder(node_cnt, r1, r2, c1, c2, x);
    }
}

long long work() {
    return network.maxFlow();
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++) {
            scanf("%d", &arr[i][j]);
        }

    init();
    printf("%lld\n", work());
    return 0;
}