#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const long long INF = 4e18;

int arr[N][N];
int ans[N][N];
int n, m;

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 1 ; i <= n ; i++) {
        for(int j = 1 ; j <= m ; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

long long solve() {
    long long ret = 4e18;

    if(n == 1 || m == 1) {
        ret = 0;

        for(int i = 1 ; i <= n ; i++)
            for(int j = 1 ; j <= m ; j++) {
                if(arr[i][j] == 0) {
                    ans[i][j] = max(ans[i-1][j], ans[i][j-1]) + 1;
                } else {
                    if(arr[i][j] <= max(ans[i-1][j], ans[i][j-1])) {
                        return -1;
                    } else {
                        ans[i][j] = arr[i][j];
                    }
                }

                ret += ans[i][j];
            }

        return ret;
    } else {
        for(int parity1 = 0 ; parity1 < 2 ; parity1++) {
            for(int parity2 = 0 ; parity2 < 2 ; parity2++) {
                long long tot = 0;

                for(int i = 1 ; i <= n ; i++) {
                    for(int j = 1 ; j <= m ; j++) {
                        int paritas = (i + j) & 1;
                        int cur_parity = parity1 ^ ((j-1) & 1);

                        if(paritas == 1) {
                            cur_parity = parity2 ^ ((j-1) & 1);
                        }

                        if(arr[i][j] != 0) {
                            if(arr[i][j] % 2 != cur_parity || arr[i][j] <= max(ans[i-1][j], ans[i][j-1])) {
                                tot = INF;
                                goto hell;
                            } else {
                                ans[i][j] = arr[i][j];
                            }
                        } else {
                            ans[i][j] = max(ans[i-1][j], ans[i][j-1]) + 1;
                            if(ans[i][j] % 2 != cur_parity) ans[i][j]++;
                        }

                        tot += ans[i][j];
                    }
                }

                hell:
                ret = min(ret, tot);
            }
        }
    }

    return ret == INF ? -1 : ret;
}

int main() {
    read();
    printf("%lld\n", solve());
    return 0;
}