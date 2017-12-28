#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

long long squared[N];
long long sum[N];
int arr[N];

long long dp[N][N];

int n, g, k;

void read() {
    scanf("%d %d %d", &n, &g, &k);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
    }
}

void prepare() {
    for(int i = 1 ; i <= n ; i++) {
        sum[i] = arr[i] + sum[i-1];
        squared[i] = squared[i-1] + 1ll * arr[i] * arr[i];
    }
}

long long calc(int l, int r) {
    if(k == 1) {
        int m = (l + r) / 2;

        int cb = m - l + 1;
        int ca = r - m;

        long long med = arr[m];

        long long ret = 0;
        ret += cb * med - (sum[m] - sum[l-1]);
        ret += (sum[r] - sum[m]) - ca * med;

        return ret;
    } else {
        long long sums = sum[r] - sum[l-1];
        long long avg = sums / (r - l + 1);

        long long ret = 4e18;
        for(int i = -1 ; i <= 1 ; i++) {
            long long iavg = avg + i;

            long long cur = squared[r] - squared[l-1];
            cur -= 2 * sums * iavg;
            cur += iavg * iavg * (r - l + 1);

            ret = min(ret , cur); 
        }

        return ret;
    }
}

void recurse(int person, int l, int r, int optl, int optr) {
    if(l > r) return;

    int m = (l + r) / 2;
    dp[person][m] = 4e18;

    int best = max(optl, m);
    for(int i = max(optl, m) ; i <= optr ; i++) {
        long long cur = dp[person-1][i+1] + calc(m, i);

        if(cur < dp[person][m]) {
            dp[person][m] = cur;
            best = i;
        }
    }

    recurse(person, l, m-1, optl, best);
    recurse(person, m+1, r, best, optr);
}

long long solve() {
    for(int i = 1 ; i <= n ; i++) {
        dp[0][i] = 4e18;
    }
    dp[0][n+1] = 0;

    for(int i = 1 ; i <= g ; i++) {
        recurse(i, 1, n, 1, n);
        dp[i][n+1] = 0;
    }

    return dp[g][1];
}

int main() {
    read();
    prepare();
    cout << solve() << endl;
    return 0;
}