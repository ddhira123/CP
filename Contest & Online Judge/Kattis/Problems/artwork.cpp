#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int Q = 1e4 + 5;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

int pset[N * N];
int color[N][N];
int ans[Q];

vector<pair<int, pair<int, int>>> v;

int n, m, q;

int finds(int x) {
    return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

int get_num(int a, int b) {
    a--; b--;
    return m * a + b;
}

void colorize(int time, int x1, int x2, int y1, int y2) {
    for(int i = x1 ; i <= x2 ; i++)
        for(int j = y1;  j <= y2 ; j++) {
            if(color[i][j] == 0) {
                v.push_back({time, {i, j}});
                color[i][j] = 1;
            }
        }
}

void update(int r, int c, int &ret) {
    ret++;
    color[r][c] = 0;

    for(int i = 0 ; i < 4 ; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if(nr >= 1 && nr <= n && nc >= 1 && nc <= m && color[nr][nc] == 0) {
            int a = get_num(r, c);
            int b = get_num(nr, nc);

            a = finds(a);
            b = finds(b);

            if(a != b) {
                pset[a] += pset[b];
                pset[b] = a;

                ret--;
            }
        }
    }
}

void init() {
    scanf("%d %d %d", &n, &m, &q);

    for(int i = 0 ; i < q ; i++) {
        int x1, x2, y1, y2;

        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        colorize(i, x1, x2, y1, y2);
    }

    colorize(q, 1, n, 1, m);
}

void work() {
    memset(pset, -1, sizeof pset);

    int it = v.size() - 1;
    int ret = 0;

    for(int i = q ; i >= 1 ; i--) {
        while(it >= 0 && v[it].first >= i) {
            update(v[it].second.first, v[it].second.second, ret);
            it--;
        }

        ans[i] = ret;
    }

    for(int i = 1 ; i <= q ; i++) {
        printf("%d\n", ans[i]);
    }
}

int main() {
    init();
    work();
    return 0;
}