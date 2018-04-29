#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int M = 102;
const int T = 2001;

struct Pokemon {
    int idx;
    int val;
    int t;

    void read() {
        scanf("%d %d %d", &idx, &val, &t);
    }

    bool operator <(Pokemon other) const {
        return idx < other.idx;
    }
};

int n, k, m;
int dp[M][M][2][T+1];
Pokemon arr[M];

int solve(int l, int r, int cur, int t) {
    int &ret = dp[l][r][cur][t];
    if(ret != -1) return ret;

    int pos = cur ? r : l;
    ret = 0;
    
    // ke kiri
    if(l-1 >= 0){
        int next_t = t + abs(arr[pos].idx - arr[l-1].idx);
        next_t = min(next_t, T);

        int val = solve(l-1, r, 0, next_t);

        ret = max(ret, val);
    }

    // ke kanan
    if(r+1 < m) {
        int next_t = t + abs(arr[pos].idx - arr[r+1].idx);
        next_t = min(next_t, T);

        int val = solve(l, r+1, 1, next_t);

        ret = max(ret, val);
    }

    ret += (t < arr[pos].t ? arr[pos].val : 0);

    return ret;
}

void read() {
    scanf("%d %d %d", &n, &k, &m);
    for(int i = 0 ; i < m ; i++) {
        arr[i].read();
    }
}

void prepare() {
    memset(dp, -1, sizeof dp);
    bool exist = 0;

    for(int i = 0 ; i < m ; i++) {
        if(arr[i].idx == k) {
            exist = 1;
        }
    }

    if(!exist) {
        arr[m++] = (Pokemon){k, 0, 1};
    }

    sort(arr, arr + m);
}

int work() {
    for(int i = 0 ; i < m ; i++) {
        if(arr[i].idx == k) {
            // cout << m << " " << i << endl;
            return solve(i, i, 0, 0);
        }
    }

    return -1;
}

int main() {
    read();
    prepare();
    printf("%d\n", work());
    return 0;
}