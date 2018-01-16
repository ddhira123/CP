#include <bits/stdc++.h>
using namespace std;

const int N = 2505;

int n;
int a[N], b[N];

int paired[3 * N];
int vis[N];
vector<int> adj[N];

vector<long long> results;
long long ans[N];

int get_index(long long x) {
    return lower_bound(results.begin(), results.end(), x) - results.begin();
}

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
}

void prepare() {
    for(int i = 0 ; i < n ; i++) {
        results.push_back(a[i] + b[i]);
        results.push_back(a[i] - b[i]);
        results.push_back(1ll * a[i] * b[i]);
    }

    sort(results.begin(), results.end());
    results.erase(unique(results.begin(), results.end()), results.end());

    for(int i = 0 ; i < n ; i++) {
        adj[i].push_back(get_index(a[i] + b[i]));
        adj[i].push_back(get_index(a[i] - b[i]));
        adj[i].push_back(get_index(1ll * a[i] * b[i]));
    }
}

int augment(int x) {
    if(vis[x]) return 0;
    vis[x] = 1;

    for(int nex : adj[x]) {
        if(paired[nex] == -1 || augment(paired[nex])) {
            paired[nex] = x;
            return 1;
        }
    }

    return 0;
}

bool perfect_match() {
    memset(paired, -1, sizeof paired);

    for(int i = 0 ; i < n ; i++) {
        memset(vis, 0, sizeof vis);

        if(!augment(i)) {
            return false;
        }
    }

    return true;
}

void solve() {
    if(perfect_match()) {
        for(int i = 0 ; i < results.size() ; i++) {
            if(paired[i] != -1) {
                ans[paired[i]] = results[i];
            }
        }

        for(int i = 0 ; i < n ; i++) {
            char op = '*';

            if(a[i] + b[i] == ans[i]) op = '+';
            else if(a[i] - b[i] == ans[i]) op = '-';

            printf("%d %c %d = %lld\n", a[i], op, b[i], ans[i]);
        }
    } else {
        puts("impossible");
    }
}

int main() {
    read();
    prepare();
    solve();
    return 0;
}