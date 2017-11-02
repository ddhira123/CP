#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXX = 1e5 + 5;
const int N = 1e5 + 5;

int arr[N];
int cnt[MAXX];
int temp[MAXX];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", arr + i);
    }
}

int solve() {
    for(int i = 0 ; i < n ; i++) {
        cnt[arr[i]]++;
    }

    for(int iter = 0 ; iter < k ; iter++) {

        for(int i = 1 ; i < MAXX ; i++) {
            for(int j = 1 ; j*j <= i ; j++) {
                if(i % j == 0) {
                    if(i != 1) {
                        cnt[j] = (cnt[j] + cnt[i]) % MOD;
                    }

                    if(j != 1 && j != i / j) {
                        cnt[i / j] = (cnt[i / j] + cnt[i]) % MOD;
                    }
                }
            }
        }

        for(int i = MAXX-1 ; i >= 1 ; i--) {
            temp[i] = (temp[i] + 1ll * cnt[i] * cnt[i]) % MOD;

            for(int j = 1 ; j*j <= i ; j++) {
                if(i % j == 0) {
                    if(i != 1) {
                        temp[j] = (temp[j] + MOD - temp[i]) % MOD;
                    }

                    if(j != 1 && j != i / j) {
                        temp[i / j] = (temp[i / j] + MOD - temp[i]) % MOD;
                    }
                }
            }
        }

        for(int i = 0 ; i < MAXX ; i++) {
            cnt[i] = temp[i];
            temp[i] = 0;
        }
    }


    int ret = 0;
    for(int i = 1 ; i < MAXX ; i ++) {
        ret = (ret + 1ll * cnt[i] * i) % MOD;
    }

    return ret;
}

int main() {
    read();
    printf("%d\n", solve());
    return 0;
}
