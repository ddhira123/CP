#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int mins[N];
int n, q;
vector<int> v;
int dp[N];
int sums[N];
int pwr[N];

void read() {
    scanf("%d %d", &n, &q);
    // n = 100000;
    // q = 50000;
    for(int i = 0 ; i < q ; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        // l = i + 1;
        // r = i + 50001;

        if(mins[l] == 0) mins[l] = r;
        else mins[l] = min(mins[l], r);
    }
}

void prepare() {
    int ms = N;

    for(int i = n ; i >= 1 ; i--) {
        if(mins[i] == 0) continue;

        if(mins[i] < ms) {
            v.push_back(i);
            ms = mins[i];
        } else {
            mins[i] = 0;
        }
    }

    reverse(v.begin(), v.end());
}

int work() {
    dp[v.size()] = 1;
    pwr[0] = 1;
    for(int i = 1 ; i < N ; i++) {
        pwr[i] = 2ll * pwr[i-1] % MOD;
    }

    int it = v.size()-1;

    for(int i = n ; it >= 0 ; i--) {
        int nex = upper_bound(v.begin(), v.end(), i) - v.begin();
        int ways;

        if(nex == v.size()) ways = pwr[n-i];
        else ways = pwr[v[nex]-i-1];

        sums[i] = 1ll * ways * dp[nex] % MOD;
        sums[i] = (sums[i] + sums[i+1]) % MOD;

        if(v[it] == i) {
            dp[it] = (sums[i] - sums[mins[v[it]]+1] + MOD) % MOD; 
            it--;
        }
    }

    int ret = dp[0];
    for(int i = 1 ; i < v[0] ; i++) {
        ret = 2ll * ret % MOD;
    }

    return ret;
}

int main() {
    read();
    prepare();
    cout << work() << endl;
    return 0;
}