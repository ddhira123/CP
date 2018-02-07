#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;

vector<int> primes;
int pset[MX];

int finds(int x) {
    return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
    x = finds(x);
    y = finds(y);

    if(x != y) {
        pset[x] += pset[y];
        pset[y] = x;
    }
}

void precompute() {
    vector<bool> flag(MX, 0);

    for(int i = 2 ; i < MX ; i++)
        if(!flag[i]) {
            primes.push_back(i);

            for(int j = i ; j < MX ; j += i)
                flag[j] = true;
        }
}

int work(long long a, long long b, long long p) {
    memset(pset, -1, sizeof pset);

    for(int x : primes) {
        if(x < p) continue;
        long long st = (a + x - 1) / x * x;

        if(st <= b) {
            int cur = st - a;

            for(int i = cur ; i < b-a+1 ; i += x) {
                join(i, cur);
            }
        }
    }

    int ret = 0;
    for(int i = 0 ; i < b-a+1 ; i++) {
        if(finds(i) == i) {
            ret++;
        }
    }

    return ret;
}

int main() {
    precompute();

    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        long long a, b, p;
        cin >> a >> b >> p;

        printf("Case #%d: %d\n", tc, work(a, b, p));
    }
    return 0;
}