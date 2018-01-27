#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int stree[4 * N];
int arr[N];
int n, q;

int mx;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void build(int id, int l, int r) {
    if(l == r) {
        stree[id] = arr[l];
    } else {
        int m = (l + r) / 2;
        int chld = id << 1;

        build(chld, l, m);
        build(chld+1, m+1, r);

        stree[id] = gcd(stree[chld], stree[chld+1]);
    }
}

void update(int id, int l, int r, int x) {
    if(l == r) {
        stree[id] = arr[x];
    } else {
        int m = (l + r) / 2;
        int chld = id << 1;

        if(x <= m) {
            update(chld, l, m, x);
        } else {
            update(chld+1, m+1, r, x);
        }

        stree[id] = gcd(stree[chld], stree[chld+1]);
    }
}

int query(int id, int l, int r, int x, int y) {
    if(x <= l && r <= y) {
        return stree[id];
    } else {
        int m = (l + r) / 2;
        int chld = id << 1;

        int ret = 0;
        if(x <= m) {
            ret = gcd(ret, query(chld, l, m, x, y));
        }
        if(y > m) {
            ret = gcd(ret, query(chld+1, m+1, r, x, y));
        }

        return ret;
    }
}

int inner(int id, int l, int r, int modd) {
    while(l < r) {
        int chld = id << 1;
        int m = (l + r) / 2;

        if(stree[chld] % modd != 0) {
            r = m;
            id = chld;
        } else {
            l = m+1;
            id = chld+1;
        }
    }

    return l;
}

int fetch(int id, int l, int r, int x ,int y, int modd) {
    if(x <= l && r <= y) {
        if(stree[id] % modd != 0) {
            return inner(id, l, r, modd);
        }
        return -1;
    } else {
        int m = (l + r) / 2;
        int chld = id << 1;

        if(x <= m) {
            int temp = fetch(chld, l, m, x, y, modd);
            if(temp != -1) {
                return temp;
            }
        }

        if(y > m) {
            return fetch(chld+1, m+1, r, x, y, modd);
        }

        return -1;
    }
}

void print(int id, int l, int r) {
    // printf("id %d l %d r %d val %d\n", id, l, r, stree[id]);
    if(l < r) {
        int m = (l + r) / 2;
        int chld = id << 1;

        print(chld, l, m);
        print(chld+1, m+1, r);
    }
}

bool solve(int l, int r, int x) {
    if(l == r) {
        return 1;
    }

    // print(1, 1, n);

    // printf("1 %d\n", stree[1]);
    if(arr[l] % x != 0) {
        return query(1, 1, n, l+1, r) % x == 0;
    }

    if(query(1, 1, n, l, r) % x == 0) {
        return 1;
    }

    int lo = fetch(1, 1, n, l, r, x);

    // printf("lo %d l %d r %d x %d\n", lo, l, r, x);

    if(lo == r) {
        return 1;
    }

    return query(1, 1, n, lo+1, r) % x == 0;
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
    }
}

void work() {
    build(1, 1, n);
    scanf("%d", &q);

    for(int i = 0 ; i < q ; i++) {
        int opt; scanf("%d", &opt);

        if(opt == 1) {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);

            printf("%s\n", solve(l, r, x) ? "YES" : "NO");
        } else {
            int pos, x;
            scanf("%d %d", &pos, &x);

            arr[pos] = x;
            update(1, 1, n, pos);

            // for(int j = 1 ; j <= n ; j++) {
            //     printf("cur %d %d\n", j, arr[j]);
            // }
        }
    }
}

int main() {
    read();
    work();
    return 0;
}