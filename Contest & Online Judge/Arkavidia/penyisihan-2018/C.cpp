#include <bits/stdc++.h>
using namespace std;

const int LOG = 31;
const int N = 200005;

int psum[LOG][N];
int arr[N];
int n, q;

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", arr + i);
    }
}

void prepare() {
    for(int i = 0 ; i < LOG ; i++) {
        for(int j = 1 ; j <= n ; j++) {
            psum[i][j] = psum[i][j-1] + ((arr[j] & (1 << i)) > 0);
        }
    }
}

int query(int l, int r) {
    int ret = 0;

    for(int i = 0 ; i < LOG ; i++) {
        if(psum[i][r] - psum[i][l-1] == r - l + 1) {
            ret |= (1 << i);
        }
    }

    return ret;
}

void work() {
    scanf("%d", &q);
    for(int i = 0 ; i < q ; i++) {
        int l, r;
        scanf("%d %d", &l, &r);

        printf("%d\n", query(l, r));
    }
}

int main() {
    int t; scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();
        work();
    }
    return 0;
}