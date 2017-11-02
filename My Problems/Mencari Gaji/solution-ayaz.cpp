// AYAZE'S CODE

#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;

int n, m, k, s, p;
bool differentWithS[N];
vector<int> adj[N];
int longest[N];

bool check(vector<int> &v) {
    if(v.size() != n) return false;
    for(int x : v) {
        if(x < 1 || x > n) {
            return false;
        }
    }
    return true;
}

int getLongestPath(int now, int targetS = -1) {
    if(targetS != -1 && now == s) {
        return longest[now] = targetS;
    }

    int &ret = longest[now];
    if(ret != -1) {
        return ret;
    }

    ret = 0;
    for(int nex : adj[now]) {
        ret = max(ret, getLongestPath(nex, targetS));
    }
    ret++;

    if(differentWithS[now] && targetS == ret) {
        ret++;
    }

    return ret;
}

void read() {
    scanf("%d %d %d %d", &n, &m, &k, &s);
    for(int i = 0 ; i < m ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[v].push_back(u);
    }
    for(int i = 0 ; i < k ; i++) {
        int x; scanf("%d", &x);
        differentWithS[x] = true;
    }
    scanf("%d", &p);
}

void solve() {
    vector<int> ans;
    memset(longest, -1, sizeof longest);

    int mins = getLongestPath(s);

    for(int iter = mins ; iter <= mins + k + 1 ; iter++) {
        vector<int> cur;
        memset(longest, -1, sizeof longest);

        for(int i = 1 ; i <= n ; i++) {
            cur.push_back(getLongestPath(i, iter));
        }

        if(check(cur) && (ans.empty() || cur < ans)) {
            ans = cur;
        }
    }

    for(int i = 0 ; i < ans.size() ; i++) {
        printf("%d%c", ans[i], i+1 == n ? '\n' : ' ');
    }
}

int main() {
    read();
    solve();
    return 0;
}