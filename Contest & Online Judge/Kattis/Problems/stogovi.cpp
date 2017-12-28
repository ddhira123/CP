#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;
const int LOG = 20;

int anc[N][LOG];
int depth[N];
int idx[N];
int num[N];
int node;
int n;

void build(int pos,int pre) {
    anc[pos][0] = pre;
    depth[pos] = depth[pre]+1;

    for(int i = 1 ; (1<<i) <= depth[pos] ; i++) {
        anc[pos][i] = anc[anc[pos][i-1]][i-1];
    }
}

int getLCA(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    for(int i = LOG-1 ; i >= 0 ; i--)
        if(depth[u] - (1<<i) >= depth[v]) {
            u = anc[u][i];
        }

    if(u == v) return u;

    for(int i = LOG-1 ; i >= 0 ; i--)
        if(depth[u] >= (1<<i) && anc[u][i] != anc[v][i]) {
            u = anc[u][i];
            v = anc[v][i];
        }   

    return anc[u][0];
}

int main() {
    scanf("%d", &n);
    num[node++] = 0;
    idx[0] = 0;

    for(int i = 1 ; i <= n ; i++) {
        char s[5];
        scanf("%s", s);

        if(s[0] == 'a') {
            int x; scanf("%d", &x);
            build(node, idx[x]);
            num[node++] = i;
            idx[i] = node-1;
        }
        else if(s[0] == 'b') {
            int x; scanf("%d", &x);
            x = idx[x];
            printf("%d\n", num[x]);
            x = anc[x][0];
            idx[i] = x;
        }
        else {
            int x, y; scanf("%d %d",&x,&y);
            x = idx[x];
            y = idx[y];

            idx[i] = x;
            printf("%d\n", depth[getLCA(x, y)]);
        }
    }
    return 0;
}

