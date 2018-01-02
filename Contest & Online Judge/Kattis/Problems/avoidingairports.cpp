#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;
const int N = 2e5 + 5;
const long long INF = 4e18;

struct Line {
    long long m;
    long long c;

    long long eval(int x) {
        return m * x + c;
    }

    bool operator <(Line other) const {
        return m > other.m;
    }
};

bool bad(Line p, Line q, Line r) {
    return (r.c - p.c) * (p.m - q.m) < (q.c - p.c) * (p.m - r.m);
}

int a[MX], b[MX], en[MX];
vector<Line> hull[N];
int n, m;

long long get_val(int s, int x) {
    if(hull[s].empty()) return INF;

    int lo = 0, hi = hull[s].size()-1;

    while(lo < hi) {
        int mid = (lo + hi) / 2;
        if(hull[s][mid].eval(x) >= hull[s][mid+1].eval(x)) {
            lo = mid+1;
        } else {
            hi = mid;
        }
    }

    return hull[s][lo].eval(x);
}

void update(int s, Line l) {
    while(hull[s].size() >= 2 && bad(hull[s][hull[s].size()-2], hull[s].back(), l)) {
        hull[s].pop_back();
    }
    hull[s].push_back(l);
}

void read() {
    scanf("%d %d", &n, &m);

    for(int i = 1 ; i <= m ; i++) {
        int u, v, s, e;

        scanf("%d %d %d %d", &u, &v, &s, &e);

        a[s] = u;
        b[s] = v;
        en[s] = e;
    }
}

long long work() {
    priority_queue<pair<int, pair<Line, int>>> pq;

    hull[1].push_back((Line){0, 0});
    long long ret = n == 1 ? 0 : INF;

    for(int i = 0 ; i < MX ; i++) {
        while(!pq.empty() && -pq.top().first <= i) {
            Line l = pq.top().second.first;
            int to = pq.top().second.second;
            pq.pop();

            update(to, l);
        }

        if(en[i] != -1) {
            int e = en[i];
            int from = a[i];
            int to = b[i];

            long long val = get_val(from, i);

            if(val != INF) {
                val += 1ll * i * i;

                if(to == n) {
                    ret = min(ret, val);
                }

                val += 1ll * e * e;

                pq.push({-e, {(Line){-2 * e, val}, to}});
            }
        }
    }

    return ret;
}

int main() {
    memset(en, -1, sizeof en);

    read();
    long long ret = work();
    printf("%lld\n", ret);

    return 0;
}