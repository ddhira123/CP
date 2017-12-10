#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int x[N], y[N], d[N];
int n, r, l;
int dist[N];

long long sqr(long long z) {
    return z * z;
}

void read() {
    scanf("%d %d %d", &n, &r, &l);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d %d %d", x + i, y + i, d + i);
        assert(0 <= y[i] && y[i] <= 1000000000);
        assert(0 <= d[i] && d[i] <= 1000000000);
    }
}

void bfs() {
    memset(dist ,-1, sizeof dist);
    dist[1] = 0;
    queue<int> q;
    q.push(1);

    while(!q.empty()) {
        int now = q.front();
        q.pop();

        long long jarak = r - dist[now] * l;
        if(jarak < 0) continue;
        jarak = sqr(jarak);

        for(int i = 1 ; i <= n ; i++) {
            if(dist[i] == -1) {
                long long cur = -1;

                if(y[now] > y[i]) {
                    cur = sqr(x[now] - x[i]) + sqr(y[now] - y[i]);
                } else if(y[now] + d[now] < y[i]) {
                    cur = sqr(x[now] - x[i]) + sqr(y[now] + d[now] - y[i]);
                } else {
                    cur = sqr(x[now] - x[i]);
                }

                if(cur <= jarak) {
                    dist[i] = dist[now] + 1;
                    q.push(i);
                }
            }
        }
    }
}

long long solve() {
    bfs();
    long long ret = -1e9;
    for(int i = 1 ; i <= n ; i++) {
        if(dist[i] != -1) {
            ret = max(ret, 1ll * y[i] + d[i]);
        }
    }
    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}