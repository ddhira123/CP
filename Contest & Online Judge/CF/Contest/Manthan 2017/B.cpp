#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const long long INF = 4e18;

long long dp[3][N];
bool vis[3][N];
long long val[3];
long long arr[N];
int n;

long long solve(int pos, int idx) {
    if(pos == 3) return 0;
    if(idx == n) return -INF;

    if(vis[pos][idx]) return dp[pos][idx];

    vis[pos][idx] = true;
    long long ret = val[pos] * arr[idx] + solve(pos+1, idx);
    ret = max(ret, solve(pos, idx+1));

    return dp[pos][idx] = ret;
}

int main() {
    scanf("%d", &n);
    for(int i = 0 ; i < 3 ; i++) {
        scanf("%lld", &val[i]);
    }
    for(int i = 0 ; i < n ; i++) {
        scanf("%lld", &arr[i]);
    }

    long long ret = solve(0, 0);
    cout << ret << endl;
    return 0;
}