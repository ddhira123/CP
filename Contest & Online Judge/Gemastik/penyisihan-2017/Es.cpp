#include <bits/stdc++.h>
using namespace std;

const int M = 1e5 + 5;
const int INF = 1e9;

int a[M], b[M], c[M];
int n, m;

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        scanf("%d %d", &n, &m);

        for(int i = 0 ; i < m ; i++) {
            a[i] = b[i] = INF;
        }

        for(int i = 0 ; i < n ; i++) {
            int x; scanf("%d", &x);
            a[x % m] = min(a[x % m], x);
        }
        for(int i = 0 ; i < n ; i++) {
            int x; scanf("%d", &x);
            b[x % m] = min(b[x % m], x);
        }
        for(int i = 0 ; i < m ; i++) {
            scanf("%d", &c[i]);
        }

        long long ret = 4e18;
        for(int i = 0 ; i < m ; i++)
            for(int j = 0 ; j < m ; j++)
                if(a[i] < INF && b[j] < INF) {
                    long long mul = 1ll * a[i] * b[j];
                    // cout << i << " " << mul << endl;
                    ret = min(ret, mul + c[mul % m]);
                }

        cout << ret << endl;
    }
    return 0;
}