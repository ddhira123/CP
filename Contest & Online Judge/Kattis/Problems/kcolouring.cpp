#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;
const int BASE = 4;
const int LEN = 3;
const int BASE3 = 64;

int dp[N][BASE][BASE3];
bool done[N][BASE][BASE3];

vector<int> adj[N];
vector<int> tree[N];
bool vis[N];
int depth[N];

vector<pair<int, int>> spec;

int special_num[N];
int special_anc[N];

int n, m, k, mod;

void dfs(int now, int prv) {
    vis[now] = 1;

    for(int nex : adj[now]) {

        if(!vis[nex]) {
            tree[now].push_back(nex);
            depth[nex] = depth[now] + 1;
            dfs(nex, now);
        } else if(nex != prv && depth[nex] < depth[now]) {
            spec.push_back({now, nex});
        }
    }
}

void prepare(int root) {
    spec.clear();
    dfs(root, -1);

    vector<int> special;
    for(pair<int, int> x : spec) {
        special.push_back(x.second);
    }

    sort(special.begin(), special.end());
    special.erase(unique(special.begin(), special.end()), special.end());

    sort(special.begin(), special.end(), [&](int a, int b) {
        return depth[a] < depth[b];
    });

    for(int i = 0 ; i < special.size() ; i++) {
        special_num[special[i]] = i;
    }

    for(pair<int, int> x : spec) {
        for(int i = 0 ; i < special.size() ; i++) {
            if(x.second == special[i]) {
                special_anc[x.first] |= (1 << i);
                break;
            }
        }
    }
}

vector<int> translate(int x) {
    vector<int> ret;
    for(int i = 0 ; i < LEN ; i++) {
        ret.push_back(x % BASE);
        x /= BASE;
    }
    return ret;
}

int reverse_translate(vector<int> x) {
    int ret = 0;
    int mul = 1;

    for(int i = 0 ; i < LEN ; i++) {
        ret += x[i] * mul;
        mul *= BASE;
    }

    return ret;
}

int solve(int now, int tipe, int mask) {
    vector<int> vmask = translate(mask);
    int maks = -1;
    for(int x : vmask) {
        if(x != BASE-1) {
            maks = max(maks, x);
        } 
    }

    if(special_num[now] != -1) {
        if(tipe == 3) {
            vmask[special_num[now]] = maks+1;
            maks++;
            tipe = maks;
        } else {
            vmask[special_num[now]] = tipe;
        }
    }

    if(special_anc[now] > 0 && tipe != 3) {
        for(int i = 0 ; i < LEN ; i++) {
            if((special_anc[now] & (1 << i)) > 0 && vmask[i] == tipe) {
                return 0;
            }
        }
    }

    mask = reverse_translate(vmask);

    if(done[now][tipe][mask]) {
        return dp[now][tipe][mask];
    }
    done[now][tipe][mask] = 1;

    long long ret = 1;
    for(int nex : tree[now]) {
        long long ways = 0;

        for(int j = 0 ; j <= maks ; j++) {
            if(tipe == 3 || tipe != j) {
                ways = (ways + solve(nex, j, mask)) % mod;
           }
        }

        if(tipe == 3) {
            ways = (ways + 1ll * (k-1-maks-1) * solve(nex, 3, mask)) % mod;
        } else {
            ways = (ways + 1ll * (k-maks-1) * solve(nex, 3, mask)) % mod;
        }

        ret = ret * ways % mod;
    }

    return dp[now][tipe][mask] = ret;
}

int process(int root) {
    prepare(root);
    int ret = solve(root, BASE-1, BASE3-1);
    ret = 1ll * ret * k % mod;

    return ret;  
}

void read() {
    scanf("%d %d %d %d", &n, &m, &k, &mod);
    for(int i = 0 ; i < m ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
} 

int work() {
    memset(special_num, -1, sizeof special_num);

    int ret = 1;
    for(int i = 1 ; i <= n ; i++) {
        if(!vis[i]) {
            int ways = process(i);
            ret = 1ll * ret * ways % mod;
        }
    }
    return ret;
}

int main() {
    read();
    printf("%d\n", work());
    return 0;
}