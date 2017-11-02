// Upsolving

#include <bits/stdc++.h>
using namespace std;

const int BASE = 1e9 + 7;
const int MOD = 2e9;
const int N = 3e5 + 5;
const int LOG = 23;

int arr[N];
int nex[N];
int x[N], y[N];
int jump[LOG][N];
int hsh[LOG][N];
int n, m;
int order[N];

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
        assert(0 <= arr[i] && arr[i] <= 1000000000);
    }
    for(int i = 0 ; i < m ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        assert(1 <= u && u <= n);
        assert(nex[u] == 0);
        assert(1 <= v && v <= n);
        nex[u] = v;
    }
    for(int i = 0 ; i < n ; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
}

void init() {
    for(int i = 1 ; i <= n ; i++) {
        arr[i] += 1;
        hsh[0][i] = arr[i];
        jump[0][i] = nex[i];
    }
    arr[0] = 0;
    hsh[0][0] = 0;

    long long base = BASE;
    for(int i = 1 ; i < LOG ; i++) {
        for(int j = 0 ; j <= n ; j++) {
            int par = jump[i-1][j];
            long long add = base * hsh[i-1][par] % MOD;

            jump[i][j] = jump[i-1][par];
            hsh[i][j] = (hsh[i-1][j] + add) % MOD;
        }

        base = base * base % MOD;
    }
}

void make_order() {
    init();
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);

    sort(v.begin(), v.end(), [&](int a, int b) {
        if(arr[a] != arr[b]) {
            return arr[a] < arr[b];
        }
        if(hsh[LOG-1][a] == hsh[LOG-1][b]) {
            return false;
        }

        int u = a, v = b;
        for(int i = LOG-1 ; i >= 0 ; i--) {
            if(hsh[i][u] == hsh[i][v]) {
                u = jump[i][u];
                v = jump[i][v];
            }
        }

        assert(arr[u] != arr[v]);
        return arr[u] < arr[v];
    });

    int val = 1;
    order[v[0]] = 1;

    for(int i = 1 ; i < v.size() ; i++) {
        int cur = v[i];
        int prv = v[i-1];

        if(hsh[LOG-1][cur] != hsh[LOG-1][prv]) {
            val++;
            val %= 4;
        }

        order[cur] = val;
    }

    for(int i = 0 ; i < v.size() ; i++) {
        // printf("%d -> %d order %d\n", i, v[i], order[v[i]]);
    }

    // printf("%d -> %u\n", 15282, hsh[LOG-1][15282]);
    // printf("%d -> %u\n", 7407, hsh[LOG-1][7407]);

    // for(int i = 1 ; i <= n ; i++) {
    //     printf("%d -> %d\n", i, order[i]);
    // }
}

bool is_same_perm() {
    for(int i = 0 ; i < n ; i++) {
        if(order[x[i]] != order[y[i]]) {
            return false;
        }
    }

    return true;
}

int main() {
    read();
    make_order();
    printf("%s\n", is_same_perm() ? "YES" : "NO");
    return 0;
}