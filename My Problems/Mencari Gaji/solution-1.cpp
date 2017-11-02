#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m, k, s;
vector<int> adj[N];
bool differentWithS[N];
int p;

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
    vector<int> permut(n);
    iota(permut.begin(), permut.end(), 1);

    do {
        bool valid = true;
        for(int i = 1 ; i <= n && valid ; i++)
            for(int nex : adj[i]) {
                if(permut[nex-1] > permut[i-1]) {
                    valid = false;
                    break;
                }
            }

        if(valid && (ans.empty() || permut < ans)) {
            ans = permut;
        }
    } while(next_permutation(permut.begin(), permut.end()));

    for(int i = 0 ; i < ans.size() ; i++)
        printf("%d%c", ans[i], i+1 == n ? '\n' : ' ');
}

int main() {
    read();
    solve();
    return 0;
}