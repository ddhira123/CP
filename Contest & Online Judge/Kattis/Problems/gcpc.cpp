#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct Fenwick {
    vector<int> vals;
    vector<int> tree;

    void add_key(int x) {
        vals.push_back(x);
    }

    void make() {
        vals.push_back(-1);
        sort(vals.begin(), vals.end());
        tree = vector<int>(vals.size()+1, 0);
    }

    int get_idx(int x) {
        return (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin()) - 1;
    }

    void update(int x, int val) {
        x = get_idx(x);
        for(; x < tree.size() ; x += x & -x) {
            tree[x] += val;
        }
    }

    int query(int x) {
        x = get_idx(x);
        int ret = 0;

        while(x) {
            ret += tree[x];
            x -= x & -x;
        }

        return ret;
    }

    int query_en() {
        return query(vals.back());
    }
};

Fenwick solves;
Fenwick teams[N];

int t[N], p[N];
int total[N], penalty[N];

int n, m;

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        scanf("%d %d", &t[i], &p[i]);
    }
}

void prepare() {
    for(int i = 0 ; i <= m ; i++) {
        solves.add_key(i);
        teams[i].add_key(0);
    }

    for(int i = 0 ; i < m ; i++) {
        int team = t[i];
        int pen = p[i];

        total[team]++;
        penalty[team] += pen;

        teams[total[team]].add_key(penalty[team]);
    }

    solves.make();
    for(int i = 0 ; i <= m ; i++) {
        teams[i].make();
    }

    for(int i = 1 ; i <= n ; i++) {
        total[i] = 0;
        penalty[i] = 0;
    }
}

void work() {
    for(int i = 1 ; i <= n ; i++) {
        solves.update(total[i], 1);
        teams[total[i]].update(penalty[i], 1);
    }

    for(int i = 0 ; i < m ; i++) {
        int team = t[i];
        int pen = p[i];

        solves.update(total[team], -1);
        teams[total[team]].update(penalty[team], -1);

        total[team]++;
        penalty[team] += pen;

        solves.update(total[team], 1);
        teams[total[team]].update(penalty[team], 1);

        int ret = solves.query_en() - solves.query(total[1]);
        // printf("%d\n", ret);
        ret += teams[total[1]].query(penalty[1]-1);

        printf("%d\n", ret+1);

    }
}

int main() {
    read();
    prepare();
    work();
    return 0;
}