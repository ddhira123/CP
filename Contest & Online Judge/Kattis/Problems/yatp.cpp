#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long m;
    long long c;

    bool operator <(Line other) const {
        return m == other.m ? c < other.c : m > other.m;
    }

    long long eval(int x) {
        return m * x + c;
    }
};

bool bad(Line p, Line q, Line r) {
    return (p.c - q.c) * (r.m - p.m) >= (p.c - r.c) * (q.m - p.m);
}

const int N = 2e5 + 5;
const long long INF = 4e18;

int p[N];
vector<pair<int, int>> adj[N];

int sz[N];
int worst[N];

bool blocked[N];

long long mins[N];

int n;

void dfs_size(int now, int prv, vector<int> &seen) {
    seen.push_back(now);

    sz[now] = 1;
    worst[now] = 0;

    for(pair<int, int> nex : adj[now]) {
        if(nex.first == prv || blocked[nex.first]) continue;
        dfs_size(nex.first, now, seen);

        sz[now] += sz[nex.first];
        worst[now] = max(worst[now], sz[nex.first]);
    }
}

void fetch_tree(int now, int prv, long long dist, vector<pair<Line, int>> &v) {
    v.push_back({(Line){p[now], dist}, now});

    for(pair<int, int> nex : adj[now]) {
        if(nex.first == prv || blocked[nex.first]) continue;

        fetch_tree(nex.first, now, dist + nex.second, v);
    }
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &p[i]);
    }
    for(int i = 1 ; i < n ; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

void solve(int root) {
    vector<int> seen;

    dfs_size(root, -1, seen);

    int min_worst = root;
    for(int x : seen) {
        worst[x] = max(worst[x], sz[root] - sz[x]);
        if(worst[x] < worst[min_worst]) {
            min_worst = x;
        }
    }

    root = min_worst;

    vector<pair<Line, int>> lines;
    fetch_tree(root, -1, 0, lines);
    sort(lines.begin(), lines.end());

    vector<Line> stek;

    for(pair<Line, int> data : lines) {
        Line line = data.first;

        // printf("root %d idx %d line %lld %lld\n", root, idx ,line.m, line.c);

        while(stek.size() >= 2 && bad(stek[stek.size()-2], stek.back(), line)) {
            stek.pop_back();
        }
        stek.push_back(line);
    }

    for(pair<Line, int> data : lines) {
        int idx = data.second;
        Line line = data.first;

        int lo = 0, hi = stek.size()-1;

        while(lo < hi) {
            int mid = (lo + hi) / 2;

            if(stek[mid].eval(line.m) >= stek[mid+1].eval(line.m)) {
                lo = mid+1;
            } else {
                hi = mid;
            }
        }

        mins[idx] = min(mins[idx], stek[lo].eval(line.m) + line.c);
    }

    blocked[root] = 1;
    for(pair<int, int> nex: adj[root]) {
        if(!blocked[nex.first]) {
            solve(nex.first);
        }
    }
}

long long work() {
    for(int i = 1 ; i <= n ; i++) {
        mins[i] = INF;
    }

    solve(1);

    long long ret = 0;
    for(int i = 1 ; i <= n ; i++) {
        ret += mins[i];
        // printf("%d -> %lld\n", i, mins[i]);
    }

    return ret;
}

int main() {
    read();
    printf("%lld\n", work());
    return 0;
}