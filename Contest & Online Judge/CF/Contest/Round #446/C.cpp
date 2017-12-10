#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

typedef pair<pair<int, int>, int> tri;
#define fi first
#define se second

int pset[N];
int rnk[N];
vector<pair<int, int>> roll;

vector<tri> edges;
int u[N], v[N], w[N];
bool ok[N];

int n, m, q;

vector<tri> que;

int finds(int x) {
    return pset[x] == x ? x : finds(pset[x]);
}

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 1 ; i <= m ; i++) {
        scanf("%d %d %d", u + i, v + i, w + i);
    }
}

void read_que() {
    scanf("%d", &q);
    for(int i = 0 ; i < q ; i++) {
        int k; scanf("%d", &k);
        for(int j = 1 ; j <= k ; j++) {
            int x; scanf("%d", &x);
            que.push_back({{w[x], x}, i});
        }
        ok[i] = 1;
    }
}

void init() {
    for(int i = 1 ; i <= n ; i++) {
        pset[i] = i;
    }

    for(int i = 1 ; i <= m ; i++) {
        edges.push_back({{u[i], v[i]}, w[i]});
    }

    sort(que.begin(), que.end(), [](tri a, tri b) {
        return a.fi.fi == b.fi.fi ? a.se < b.se : a.fi.fi < b.fi.fi;
    });

    sort(edges.begin(), edges.end(), [](tri a, tri b) {
        return a.se < b.se;
    });

}

void work() {
    int it = 0;
    for(int i = 0 ; i < edges.size() ; i++) {
        if(it < que.size() && que[it].fi.fi == edges[i].se) {
            while(it < que.size() && que[it].fi.fi == edges[i].se) {
                int it2 = it;
                while(it2 < que.size() && que[it2].fi.fi == edges[i].se && que[it2].se == que[it].se) {
                    it2++;
                }

                int qid = que[it].se;

                for(int j = it ; j < it2 ; j++) {
                    int eid = que[j].fi.se;
                    int uu = u[eid];
                    int vv = v[eid];

                    // printf("qid %d uu %d vv %d\n", qid, uu, vv);

                    uu = finds(uu);
                    vv = finds(vv);

                    // printf("%d %d\n", uu, vv);

                    if(uu == vv) {
                        ok[qid] = false;
                    } else {
                        if(rnk[uu] < rnk[vv]) {
                            roll.push_back({uu, rnk[uu]});
                            pset[uu] = vv;
                        } else if(rnk[uu] > rnk[vv]) {
                            roll.push_back({vv, rnk[vv]});
                            pset[vv] = uu;
                        } else {
                            roll.push_back({uu, rnk[uu]});
                            roll.push_back({vv, rnk[vv]});
                            pset[vv] = uu;
                            rnk[uu] += 1;
                        }
                    }
                }

                for(int j = (int)roll.size()-1 ; j >= 0 ; j--) {
                    int uu = roll[j].fi;
                    int ruu = roll[j].se;

                    pset[uu] = uu;
                    rnk[uu] = ruu;
                }

                roll.clear();

                it = it2;
            }
        }

        int uu = edges[i].fi.fi;
        int vv = edges[i].fi.se;

        uu = finds(uu);
        vv = finds(vv);

        if(uu != vv) {
            if(rnk[uu] < rnk[vv]) {
                pset[uu] = vv;
            } else if(rnk[uu] > rnk[vv]) {
                pset[vv] = uu;
            } else {
                pset[vv] = uu;
                rnk[uu] += 1;
            }
        }
    }

    for(int i = 0 ; i < q ; i++) {
        printf("%s\n", ok[i] ? "YES" : "NO");
    }
}

int main() {
    read();
    read_que();
    init();
    work();
    return 0;
}