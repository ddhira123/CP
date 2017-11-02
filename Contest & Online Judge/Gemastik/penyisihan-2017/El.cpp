#include <bits/stdc++.h>
using namespace std;

const int M = 1e5 + 5;
const int MAGIC = 1e6;
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

        vector<int> v;
        for(int i = 1 ; i < m ; i++) {
            if(b[i] < INF) {
                v.push_back(b[i]);
            }
        }

        sort(v.begin(), v.end());
        long long ret = 4e18;

        for(int i = 1 ; i < m ; i++)
            if(a[i] < INF) {
                long long bound = 1ll * v[0] * a[i];
                long long temp = bound + c[bound % m];

                for(int x : v) {
                    long long cur = 1ll * x * a[i];
                    if(cur > bound + MAGIC) {
                        break;
                    }

                    temp = min(temp, cur + c[cur % m]);
                }

                ret = min(ret, temp);
            }

        if(a[0] < INF) {
            for(int i = 0 ; i < m ; i++) {
                if(b[i] < INF) {
                    long long cur = 1ll * a[0] * b[i];
                    cur += c[cur % m];

                    ret = min(ret, cur);
                }
            }
        }

        if(b[0] < INF) {
            for(int i = 0 ; i < m ; i++) {
                if(a[i] < INF) {
                    long long cur = 1ll * b[0] * a[i];
                    cur += c[cur % m];

                    ret = min(ret, cur);
                }
            }
        }

        cout << ret << endl;
    }
    return 0;
}