#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

struct Dinic {
    struct Edge {
        int from;
        int to;
        int flow;
    };

    vector<Edge> elist;
    vector<int> adj[2*N];
    int saiz;

    int ptr[2*N];
    int dist[2*N];

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
bool prime[N];
int nodeNum[N];

int v[N];
int c[N];

void read() {
    cin >> n;
    for (int i = 1 ; i <= n ; i++) {
        cin >> v[i];
    }
    for (int i = 1 ; i <= n ; i++) {
        cin >> c[i];
    }
}

void prepare() {
    for (int i = 2 ; i <= n ; i++) prime[i] = true;

    int cnt = n+2;
    for (int i = 2 ; i <= n ; i++) {
        if (prime[i]) {
            for (int j = i + i ; j <= n ; j += i) {
                prime[j] = 0;
            }

            for (int mul = i ; mul <= n ; mul *= i) {
                nodeNum[mul] = cnt++;
            }
        }
    }

    network = Dinic(0, 1, cnt-1);

    for (int i = 1 ; i <= n ; i++) {
        network.add_edge(i + 1, 1, v[i]);
    }
    for (int i = 2 ; i <= n ; i++)
        if (prime[i]) {
            for (int mul = i, step = 1 ; mul <= n ; mul *= i, step++) {
                network.add_edge(0, nodeNum[mul], (step * 2 - 1) * c[i]);

                for (int j = mul ; j <= n ; j += mul)
                    if ((j / mul) % i != 0 || 1) {
                        // printf("%d -> %d\n", mul, j);
                        network.add_edge(nodeNum[mul], j+1, 1e9);
                    }
            }
        }
}

int work() {
    int ret = accumulate(v + 1, v + n + 1, 0);
    ret -= network.maxFlow();
    return ret;
}

int work2(int cur, long long lcm, int val) {
    if (cur > n) {
        for (int i = 1 ; i <= n ; i++) {
            if (lcm % i == 0) val += v[i];
        }
        return val;
    }

    if (!prime[cur]) return work2(cur+1, lcm, val);

    int ret = 0;
    for (int mul = 1, step = 0 ; mul <= n ; mul *= cur, step++) {
        ret = max(ret, work2(cur+1, lcm * mul, val - step * step * c[cur]));
    }

    return ret;
}

int main() {
    read();
    prepare();
    printf("%d\n", work());
    // srand(time(NULL));
    // while(1) {
    //     static int tc = 1;

    //     printf("TRIAL %d\n", tc++);

    //     n = rand() % 10 + 1;
    //     for (int i = 1 ; i <= n ; i++) v[i] =rand() % 5;
    //     for (int i = 1 ; i <= n ; i++) c[i] = prime[i] ? rand() % 5 : 0;

    //     prepare();

    //     int a = work();
    //     int b = work2(1, 1, 0);

    //     if (a != b) {
    //         printf("%d\n", n);
    //         for (int i = 1 ; i <= n ; i++) printf("%d ", v[i]);
    //         puts("");
    //         for (int i = 1 ; i <= n ; i++) printf("%d ", c[i]);
    //         puts("");

    //         printf("%d %d\n", a, b);
    //         break;
    //     }
    // }
    return 0;
}