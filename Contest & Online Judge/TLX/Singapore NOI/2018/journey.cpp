#include <bits/stdc++.h>
using namespace std;

const int INF = 500000001;
const int N = 10001;
const int M = 401;
const int H = 101;

int dp[N][M];
vector<pair<int, int>> arr[N];
int n, m, h;

int solve(int now, int sisa) {
    if(sisa < 0) return 0;
    if(now == n-1 && sisa == 0) {
        return 1;
    }

    int &ret = dp[now][sisa];
    if(ret != -1) {
        return ret;
    }

    ret = 0;
    if(now != 0) {
        ret = solve(now, sisa-1);
    }

    for(pair<int, int> nex : arr[now]) {
        int nxt = nex.first;
        int night = nex.second;

        ret = min(INF, ret + solve(nxt, sisa - night));
    }

    return ret;
}

void read() {
    scanf("%d %d %d", &n, &m, &h);

    for(int i = 0 ; i+1 < n ; i++) {
        for(int j = 0 ; j < h ; j++) {
            int a, b;
            scanf("%d %d", &a, &b);

            if(a > i) {
                arr[i].push_back({a, b});
            }
        }
    }
}

void work() {
    memset(dp, -1, sizeof dp);

    for(int i = 0 ; i < m ; i++) {
        printf("%d%c", solve(0, i), i+1 == m ? '\n' : ' ');
    }
}

int main() {
    read();
    work();
    return 0;
}