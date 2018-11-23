#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;
const int MAGIC = 20;

long long ways[MX];
int prime[MX];
int mobius[MX];
int solo[MX];

void precompute() {
    for (int i = 2 ; i <= MAGIC ; i++) {
        int lst = 1;

        for (; ; lst++) {
            long long temp = 1;
            bool ok = 1;
            for (int j = 1 ; j <= i ; j++) {
                if (MX / lst < temp) {
                    ok = false;
                    break;
                }
                temp *= lst;
            }
            if (temp >= MX || !ok) {
                break;
                lst--;
            }
        }

        for (int j = 1 ; j <= lst ; j++)
            for (int k = j+1 ; k <= lst ; k++) {
                if (__gcd(j, k) != 1) continue;

                long long sum = 0;
                long long jj = 1;
                long long kk = 1;

                for (int it = 1 ; it <= i ; it++) jj *= j;

                for (int it = 0 ; it <= i ; it++) {
                    sum += jj * kk;
                    jj /= j;
                    kk *= k;
                }

                if (sum < MX) ways[sum]++;
            }
    }

    for (int i = 2 ; i < MX ; i++) {
        prime[i] = 1;
        mobius[i] = 1;
    }

    for (int i = 2 ; i < MX ; i++)
        if (prime[i]) {
            mobius[i] = -1;

            for (int j = i + i ; j < MX ; j += i) {
                prime[j] = 0;
                mobius[j] = -mobius[j];

                if ((j / i) % i == 0) {
                    mobius[j] = 0;
                }
            }
        }

    mobius[1] = 1;
    for (int i = 1 ; i < MX ; i++) {
        for (int j = i ; j < MX ; j += i) {
            int val = ((j / i) - 1) / 2;
            solo[j] += mobius[i] * val;

            // if (j == 18) {
            //     printf("i %d mobius %d val %d\n", i, mobius[i], val);
            // }
        }
    }
}

long long calc(int x) {
    int ret = ways[x];
    int add = 0;
    // for (int i = 1 ; i < x ; i++) {
    //     int j = x - i;
    //     if (i < j && __gcd(i, j) == 1) add++;
    // }
    // printf("x %d add %d solo %d\n", x, add, solo[x]);
    add = solo[x];
    assert(add == solo[x]);
    return ret + add;
}

int main() {
    precompute();
    // long long ret = 0;
    // for(int i = 1 ; i < MX ; i++) ret += ways[i];
    // cout << ret << endl;

    // calc(18);
    // for (int i = 1 ; i < MX ; i++) printf("%d\n", i), calc(i);
    int t; cin >> t;

    for (int tc = 1 ; tc <= t ; tc++) {
        int s; cin >> s;

        long long ret = 1;
        for (int i = 1 ; i * i <= s ; i++)
            if (s % i == 0) {
                ret += calc(s / i);
                if (i != s / i) ret += calc(i);
            }

        printf("%lld%c", ret, tc == t ? '\n' : ' ');
    }
    return 0;
}