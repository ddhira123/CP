#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

vector<int> chld[N];
int in[N], ot[N];
int par[N];
int n;

void dfs(int now) {
    static int cnt = 0;

    in[now] = ++cnt;
    for(int nex : chld[now]) {
        dfs(nex);
    }
    ot[now] = cnt;
}

int calc(vector<int> v) {
    sort(v.begin(), v.end(), [&](int a, int b) {
        return in[a] < in[b];
    });

    int mx = -1;
    int ret = 0;
    for(int x : v) {
        if(in[x] > mx) {
            ret += (ot[x] - in[x] + 1);
            mx = ot[x];
        }
    }

    return ret;
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &par[i]);
        chld[par[i]].push_back(i);
    }
}

void prepare() {
    dfs(0);
}

void work() {
    int q; scanf("%d", &q);

    for(int i = 0 ; i < q ; i++) {
        int sz; scanf("%d", &sz);
        vector<int> v(sz);

        for(int &x : v) {
            scanf("%d", &x);
        }

        printf("%d\n", calc(v));
    }
}

int main() {
    read();
    prepare();
    work();
    return 0;
}