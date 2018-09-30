#include <bits/stdc++.h>
using namespace std;

const int N = 15;

int n;
int arr[N+5];
int dp[N][1 << N];

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", arr + i);
    }
}

int awal;

int solve(int lst, int msk) {
    if(__builtin_popcount(msk) == n) {
        return arr[lst+1] == arr[awal+1];
    }

    int &ret = dp[lst][msk];
    if(ret != -1) {
        return ret;
    }

    ret = 1e9;
    for(int i = 0 ; i < n ; i++)
        if((msk & (1 << i)) == 0) {
            ret = min(ret, solve(i, msk | (1 << i)) + (arr[lst+1] == arr[i+1]));
        }

    return ret;
}

int calc(vector<int> &v) {
    int ret = 0;

    for(int i = 0 ; i < v.size() ; i++) {
        int j = (i + 1) % v.size();

        ret += (arr[v[i]] == arr[v[j]]);
    }

    return ret;
}

vector<int> coba(int st) {
    memset(dp, -1, sizeof dp);
    awal = st;

    vector<int> ret;
    ret.push_back(st+1);

    int msk = 1 << st;
    int lst = st;

    for(int i = 1 ; i < n ; i++) {
        int mins = -1;
        int use = -1;

        for(int j = 0 ; j < n ; j++) {
            if(msk & (1 << j)) continue;
            int val = solve(j, msk | (1 << j)) + (arr[lst+1] == arr[j+1]);

            if(use == -1 || val < mins) {
                use = j;
                mins = val;
            }
        }

        ret.push_back(use+1);
        msk |= (1 << use);
        lst = use;
    }

    return ret;
}

void solve() {
    vector<int> ans(n);
    iota(ans.begin(), ans.end(), 1);

    for(int i = 0 ; i < n ; i++) {
        vector<int> temp = coba(i);
        if(calc(temp) < calc(ans)) {
            ans = temp;
        }
    }

    for(int i = 0 ; i < ans.size() ; i++) {
        printf("%d%c", ans[i], i+1 == ans.size() ? '\n' : ' ');
    }
}

int main() {
    read();
    solve();
    return 0;
}
