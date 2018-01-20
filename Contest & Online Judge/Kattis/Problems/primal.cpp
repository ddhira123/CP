#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;
const int N = 20005;

int max_prime[MX];

int pset[N];

int arr[N];
int n, k;

int finds(int x) {
    return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
    x = finds(x);
    y = finds(y);

    if(x != y) {
        pset[x] = -__gcd(-pset[x], -pset[y]);
        pset[y] = x;
    }
}

void precompute() {
    for(int i = 2 ; i < MX ; i++) {
        if(max_prime[i] == 0) {
            for(int j = i ; j < MX ; j += i) {
                max_prime[j] = i;
            }
        }
    }
}

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    } 
}

int solve() {
    priority_queue<pair<int, int>> pq;

    int ret = MX;
    for(int i = 0 ; i < n ; i++) {
        ret = min(ret, max_prime[arr[i]]);
        pset[i] = -arr[i];

        if(i+1 < n) {
            pq.push({max_prime[__gcd(arr[i], arr[i+1])], i});
        }
    }

    for(int i = 0 ; i < n-k ; i++) {
        while(1) {
            int mp = pq.top().first;
            int idx = pq.top().second;

            int x = finds(idx);
            int y = finds(idx+1);

            int cur_mp = max_prime[__gcd(-pset[x], -pset[y])];

            if(mp != cur_mp) {
                pq.pop();
                pq.push({cur_mp, idx});
            } else {
                break;
            }
        }

        ret = min(ret, pq.top().first);
        join(pq.top().second, pq.top().second+1);
        pq.pop();
    }

    return ret;
}

int main() {
    precompute();
    read();
    printf("%d\n", solve());
    return 0;
}