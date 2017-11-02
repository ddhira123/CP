#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9;
const int N = 1e5 + 5;
const int BUCKET = 300;

int arr[2][N];
int bucket[2][N];
bool changed[2][N];
int n, q;

int get_id(int x) {
    return x / BUCKET;
}

pair<int, int> get_end_points(int buck_id) {
    int l = buck_id * BUCKET;
    int r = min(n, (buck_id + 1) * BUCKET) - 1;

    return {l, r};
}

void apply_swap(int type, int buck_id) {
    pair<int, int> rng = get_end_points(buck_id);
    int l = rng.first;
    int r = rng.second;

    if(changed[type][buck_id]) {
        for(int i = l ; i <= r ; i++) {
            arr[type][i] = arr[type ^ 1][i];
        }
        changed[type][buck_id] = false;
    }
}

void rebuild_bucket(int type, int buck_id) {
    pair<int, int> rng = get_end_points(buck_id);
    int l = rng.first;
    int r = rng.second;

    apply_swap(type, buck_id);

    bucket[type][buck_id] = 1;
    int &val = bucket[type][buck_id];

    for(int i = l ; i <= r ; i++)
        val = (1ll * val * arr[type][i]) % MOD;
}

void change(int type, int pos, int nval) {
    rebuild_bucket(type ^ 1, get_id(pos));
    rebuild_bucket(type, get_id(pos));
    arr[type][pos] = nval;
    rebuild_bucket(type, get_id(pos));
}

void swap_val(int type, int l, int r) {
    int idx = get_id(l);
    int end_l = get_end_points(idx).second;
    int en = min(end_l, r);

    int i = l;
    rebuild_bucket(type ^ 1, idx);
    rebuild_bucket(type, idx);

    while(i <= en) {
        arr[type][i] = arr[type ^ 1][i];
        i++;
    }

    rebuild_bucket(type, idx);

    if(r > en) {
        idx = get_id(i);
        while(idx < get_id(r)) {
            if(!changed[type ^ 1][idx]) {
                changed[type][idx] = 1;
            }
            idx++;
        }

        rebuild_bucket(type ^ 1, idx);
        rebuild_bucket(type, idx);
        i = get_end_points(idx).first;

        while(i <= r) {
            arr[type][i] = arr[type ^ 1][i];
            i++;
        }

        rebuild_bucket(type, idx);
    }
}

int get_val(int type, int l, int r) {
    int idx = get_id(l);
    int end_l = get_end_points(idx).second;
    int en = min(end_l, r);

    int ret = 1;

    int i = l;
    // rebuild_bucket(type ^ 1, idx);
    // rebuild_bucket(type, idx);

    while(i <= en) {
        if(changed[type][idx]) {
            ret = 1ll * ret * arr[type ^ 1][i] % MOD;
        } else {
            ret = 1ll * ret * arr[type][i] % MOD;
        }
        i++;
    }

    // rebuild_bucket(type, idx);

    if(r > en) {
        idx = get_id(i);
        while(idx < get_id(r)) {
            if(changed[type][idx]) {
                ret = 1ll * ret * bucket[type ^ 1][idx] % MOD;
            } else {
                ret = 1ll * ret * bucket[type][idx] % MOD;
            }
            idx++;
        }

        // rebuild_bucket(type ^ 1, idx);
        // rebuild_bucket(type, idx);
        i = get_end_points(idx).first;

        while(i <= r) {
            if(changed[type][idx]) {
                ret = 1ll * ret * arr[type ^ 1][i] % MOD;
            } else {
                ret = 1ll * ret * arr[type][i] % MOD;
            }
            i++;
        }

        // rebuild_bucket(type, idx);
    }

    return ret;
}

void read() {
    scanf("%d %d", &n, &q);
    for(int i = 0 ; i < 2 ; i++)
        for(int j = 0 ; j < n ; j++)
            scanf("%d", &arr[i][j]);
}

void init() {
    for(int i = 0 ; i <= get_id(n-1) ; i++) {
        rebuild_bucket(0, i);
        rebuild_bucket(1, i);
    }
}

void work() {
    for(int i = 0 ; i < q ; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int idx = (a - 1) / 3;
        int op = (a - 1) % 3;

        if(op == 0) {
            change(idx, b-1, c);
        } else if(op == 1) {
            swap_val(idx, b-1, c-1);
        } else {
            printf("%d\n", get_val(idx, b-1, c-1));
        }
    }
}

int main() {
    read();
    init();
    work();
    return 0;
}