#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int f[N], p[N], m[N], s[N];
int profit[N][2];
int from[N];
bool vis[N];
int n;

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d %d %d %d", &f[i], &p[i], &m[i], &s[i]);
    }
}

long long work() {
    for(int i = 1 ; i <= n ; i++) {
        from[i] = i;
    }

    for(int i = 1 ; i <= n ; i++) {
        int nex = f[i];
        int cur_profit = m[nex] - p[i];

        if(cur_profit >= profit[nex][0]) {
            profit[nex][1] = profit[nex][0];
            profit[nex][0] = cur_profit;
            from[nex] = i;
        } else if(cur_profit >= profit[nex][1]) {
            profit[nex][1] = cur_profit;
        }
    }

    long long ret = 0;
    
    for(int i = 1 ; i <= n ; i++) {
        ret += 1ll * s[i] * profit[i][0];
    }

    for(int i = 1 ; i <= n ; i++) {
        if(vis[i]) continue;

        vector<int> seen;
        int j = i;

        while(!vis[j]) {
            seen.push_back(j);
            vis[j] = 1;
            j = from[j];
        }

        // cycle
        if(j == i) {
            // cycle > 1, must resolve to chain
            if(seen.size() > 1) {
                int mins = 1e9;

                for(int x : seen) {
                    mins = min(mins, profit[x][0] - profit[x][1]);
                }

                ret -= mins;
            }
        }
    }

    return ret;
}

int main() {
    read();
    printf("%lld\n", work());
    return 0;
}