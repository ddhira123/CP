#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n[2];
vector<int> adj[2][N];
long long sub[2][N];

long long squared[2][N];
long long sum[2][N];

void dfs1(int id, int now, int prv) {
    sub[id][now] = 1;

    for(int nex : adj[id][now]) {
        if(nex == prv) continue;
        dfs1(id, nex, now);

        sub[id][now] += sub[id][nex];
        sum[id][now] += sum[id][nex] + sub[id][nex];
        squared[id][now] += squared[id][nex] + 2 * sum[id][nex] + sub[id][nex];
    }
}

void dfs2(int id, int now, int prv) {
    for(int nex : adj[id][now]) {
        if(nex == prv) continue;

        long long tsub = n[id] - sub[id][nex];
        long long tsum = sum[id][now] - (sum[id][nex] + sub[id][nex]);
        long long tsq = squared[id][now] - (squared[id][nex] + 2 * sum[id][nex] + sub[id][nex]);

        sum[id][nex] += tsum + tsub;
        squared[id][nex] += tsq + 2 * tsum + tsub;

        dfs2(id, nex, now);
    }
}

vector<pair<long long, long long>> va, vb;

long long solve(int l, int r, int optl, int optr) {
    if(l > r) return 4e18;

    long long ret = 4e18;
    int m = (l + r) / 2;
    int best = optl;

    for(int i = best ; i <= optr ; i++) {
        long long am = va[i].first;
        long long ac = va[i].second;

        long long cur = am * vb[m].first;
        cur += ac * n[1];
        cur += (vb[m].second) * n[0];
        cur += 1ll * n[0] * n[1];

        if(cur < ret) {
            ret = cur;
            best = i;
        }
    }

    ret = min(ret, solve(l, m-1, optl, best));
    ret = min(ret, solve(m+1, r, best, optr));

    return ret;
}

void read() {
    for(int i = 0 ; i < 2 ; i++) {
        scanf("%d", &n[i]);
        for(int j = 1 ; j < n[i] ; j++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[i][u].push_back(v);
            adj[i][v].push_back(u);
        }
    }
}

void prepare() {
    for(int i = 0 ; i < 2 ; i++) {
        dfs1(i, 1, 0);
        dfs2(i, 1, 0);
    }

    for(int i = 1 ; i <= n[0] ; i++) {
        // cout << i << " " << squared[0][i] << endl; 
        va.push_back({2 * sum[0][i], squared[0][i] + 2 * sum[0][i]});
    }

    // cout << "===\n";

    for(int i = 1 ; i <= n[1] ; i++) {
        // cout << i << " " << squared[1][i] << endl;
        vb.push_back({sum[1][i], squared[1][i] + 2 * sum[1][i]});
    }

    sort(va.begin(), va.end());
    reverse(va.begin(), va.end());

    sort(vb.begin(), vb.end());
    // reverse(vb.begin(), vb.end());
}

long long work() {
    long long solo = 0;
    for(int i = 0 ; i < 2 ; i++) {
        long long tot = 0;
        for(int j = 1 ; j <= n[i] ; j++) {
            tot += squared[i][j];
        }
        solo += tot / 2;
    }

    long long combine = solve(0, n[1]-1, 0, n[0]-1);

    return combine + solo;
}

int main() {
    read();
    prepare();
    cout << work() << endl;
    return 0;
}