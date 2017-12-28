#include <bits/stdc++.h>
using namespace std;

const int N = 2505;
const double MX = 1e4 + 5;
const double INF = 1e9;
const double EPS = 1e-5;
const int TRIAL = 60;

double dp[N][N];
int p[N], s[N];
int n, k;
int inve[N], ot[N];
vector<int> chld[N];
int cnt;

void dfs(int now) {
    inve[++cnt] = now;
    int cur = cnt;
    for(int nex : chld[now])
        dfs(nex);
    ot[cur] = cnt;
}

bool check(double x) {
    for(int i = 2 ; i <= cnt+1 ; i++) {
        int lmt = min(i-2,k);
        for(int j = 0 ; j <= lmt ; j++)
            dp[i][j] = -INF;
    }
    
    dp[2][0] = 0;
    for(int i = 2 ; i <= cnt ; i++) {
        int skip = ot[i]+1;
        int cur = inve[i];
        int lmt = min(i-2,k);
        for(int j = 0 ; j <= lmt ; j++) {
            dp[skip][j] = max(dp[skip][j],dp[i][j]);
            dp[i+1][j+1] = max(dp[i+1][j+1],dp[i][j] + p[cur] - x*s[cur]);
        }
    }
    
    return dp[cnt+1][k] > -EPS;
}

void read() {
    scanf("%d %d",&k,&n);
    for(int i = 1 ; i <= n ; i++) {
        int x;
        scanf("%d %d %d",&s[i],&p[i],&x);
        chld[x].push_back(i);
    }
}

void solve() {
    dfs(0);
    double lo = 0, hi = MX;
    for(int i = 0 ; i < TRIAL ; i++) {
        double mid = (lo + hi) / 2;
        if(check(mid)) lo = mid;
        else hi = mid;
    }
    printf("%.3lf\n",lo);
}

int main() {
    read();
    solve();
    return 0;
}

