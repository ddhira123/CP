#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int BIT[N];

void update(int x, int val) {
    for(int i = x ; i < N ; i += i & -i) {
        BIT[i] += val;
    }
}

int query(int x) {
    int ret = 0;
    while(x) {
        ret += BIT[x];
        x -= x & -x;
    }
    return ret;
}

int n;
int arr[N];
int order[N];

int get_val(int x) {
    return min(arr[x]+1, x);
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
    }
}

void prepare() {
    for(int i = 1 ; i <= n ; i++) {
        arr[i] = min(arr[i], n);
        order[i] = i;
    }

    sort(order + 1, order + n + 1, [&](int a, int b) {
        return get_val(a) < get_val(b);
    });
}

long long work() {
    long long ret = 0;
    int lst = 1;

    for(int i = 1 ; i <= n ; ) {
        int j = i;

        while(j <= n && get_val(order[i]) == get_val(order[j])) {
            j++;
        }

        while(lst < get_val(order[i])) {
            update(arr[lst], 1);
            lst++;
        }

        for(int it = i ; it < j ; it++) {
            int idx = order[it];
            ret += (query(n) - query(idx-1));
        }

        i = j;
    }

    return ret;
}

int main() {
    read();
    prepare();
    printf("%lld\n", work());
    return 0;
}