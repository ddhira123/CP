#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 8;
const int N = 5e4 + 5;
const int MAX_GRUNDY = 512;

vector<int> multiply(vector<int> &a, vector<int> &b) {
    vector<int> ret(MAX_GRUNDY, 0);

    for(int i = 0 ; i < MAX_GRUNDY ; i++)
        for(int j = 0 ; j < MAX_GRUNDY ; j++)
            ret[i] = (ret[i] + 1ll * a[j] * b[i ^ j]) % MOD;

    return ret;
}

vector<int> power(vector<int> base, int po) {
    vector<int> ret(MAX_GRUNDY, 0);
    ret[0] = 1;

    while(po) {
        if(po & 1) {
            ret = multiply(ret, base);
        }

        base = multiply(base, base);
        po >>= 1;
    }

    return ret;
}

int grundy[N];
vector<int> adj[N];
int n, m, k;

void read() {
    scanf("%d %d %d", &n, &m, &k);

    for(int i = 0 ; i < m ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
    }
}

void prepare() {
    for(int i = 1 ; i <= n ; i++) {
        set<int> s;

        for(int x : adj[i]) {
            s.insert(grundy[x]);
        }

        for(int j = 0 ; ; j++)
            if(!s.count(j)) {
                grundy[i] = j;
                break;
            }
    }
}

int solve() {
    vector<int> ret(MAX_GRUNDY, 0);

    for(int i = 1 ; i <= n ; i++) {
        ret[grundy[i]]++;
    }
    ret = power(ret, k);

    int ans = 0;
    for(int i = 1 ; i < MAX_GRUNDY ; i++) {
        ans = (ans + ret[i]) % MOD;
    }

    return ans;
}

void reset() {
    for(int i = 1 ; i <= n ; i++) {
        adj[i].clear();
    }
}

int main() {
    int t; 
    scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();
        printf("%d\n", solve());
        reset();
    }
    return 0;
}
