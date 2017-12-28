#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;
int BUCKET;

inline int io() {
    register char c;
    c = getchar_unlocked();
    while(c == ' ' || c == '\n') c = getchar_unlocked();
    int ret = 0;
    int sign = 1;
    if(c == '-') {
        sign = -1;
    }
    else {
        ret = c - '0';
    }
    
    while(1) {
        c = getchar_unlocked();
        if(!('0' <= c && c <= '9')) return ret;
        ret = (ret << 3) + (ret << 1) + (c - '0');
    }
}

long long get_cumulative(long long n, int orde) {
    if(n <= 0) return 0;
    long long ret;
    if(orde == 1) {
        ret = n * (n + 1) / 2 % MOD;
        ret %= MOD;
    }
    else if(orde == 2) {
        long long var[3] = {n, n+1, 2*n + 1};

        for(int i = 0 ; i < 3 ; i++)
            if(var[i] % 2 == 0) {
                var[i] /= 2;
                break;
            }

        for(int i = 0 ; i < 3 ; i++)
            if(var[i] % 3 == 0) {
                var[i] /= 3;
                break;
            }

        ret = 1;
        for(int i = 0 ; i < 3 ; i++) {
            ret = ret * var[i] % MOD;
        }
    }
    else {
        long long temp = get_cumulative(n, 1);
        ret = temp * temp % MOD;
    }

    return ret;
}

long long cumulative_sum(int l, int r, int orde) {
    long long ret = get_cumulative(r, orde);
    ret -= get_cumulative(l-1, orde);
    ret %= MOD;
    if(ret < 0) ret += MOD;
    return ret;
}

// cnt di 3

int bucket[2][N][4];
int sum[2][N][4];
int arr[2][N][3];
int n, q;

int get_id(int x) {
    return x / BUCKET;
}

pair<int, int> get_ends(int x) {
    int kiri = x * BUCKET;
    int kanan = min(n, (x + 1) * BUCKET) - 1;

    return {kiri, kanan};
}

void rebuild(int tipe, int id) {
    pair<int, int> ends = get_ends(id);
    int kiri = ends.first;
    int kanan = ends.second;

    if(bucket[tipe][id][3] == 0) {
        return;
    }

    for(int i = 0 ; i < 3 ; i++) {
        sum[tipe][id][i] = 0;
    }

    for(int i = kiri ; i <= kanan ; i++) {
        long long rel = i - kiri;
        long long rel2 = rel * rel % MOD;
        long long rel3 = rel2 * rel % MOD;

        // cerr << i << endl;

        long long a;
        a = arr[tipe][i][0];
        a += bucket[tipe][id][0];
        a += bucket[tipe][id][3] * rel % MOD;
        a %= MOD;
        arr[tipe][i][0] = a;

        a = arr[tipe][i][1];
        a += bucket[tipe][id][1];
        a += bucket[tipe][id][0] * 2 * rel; 
        a += bucket[tipe][id][3] * rel2;
        a %= MOD;
        arr[tipe][i][1] = a;

        a = arr[tipe][i][2];
        a +=  bucket[tipe][id][2];
        a += 3 * rel * bucket[tipe][id][1];
        a += 3 * rel2 * bucket[tipe][id][0];
        a += bucket[tipe][id][3] * rel3;
        a %= MOD;
        arr[tipe][i][2] = a;

        for(int j = 0 ; j < 3 ; j++) {
            sum[tipe][id][j] = (sum[tipe][id][j] + arr[tipe][i][j]) % MOD;
        }
    }

    for(int i = 0 ; i < 4 ; i++) {
        bucket[tipe][id][i] = 0;
    }

    // cerr << "done\n";
}

void add(int tipe, int idx, long long x) {
    int buck = get_id(idx);

    // cerr << "add\n";
    long long mul = 1;
    for(int i = 0 ; i <= 2 ; i++) {
        mul = mul * x % MOD;

        arr[tipe][idx][i] += mul;
        arr[tipe][idx][i] %= MOD;

        // printf("%d %d %d -> %lld\n", tipe, idx, i, arr[tipe][idx][i]);

        sum[tipe][buck][i] += mul;
        sum[tipe][buck][i] %= MOD;
    }

    // cerr << "done\n";
}

void update(int tipe, int l, int r) {
    int id_l = get_id(l);
    int en = get_ends(id_l).second;

    rebuild(tipe, id_l);

    int i = l;
    // cerr << i << " " << l << " " << r << endl;
    while(i <= min(en, r)) {
        // cerr << "masuk " << i << endl;
        add(tipe, i, i-l+1);
        i++;
        // cerr << "yay" << i << endl;
    }

    if(r > en) {
        int id = id_l+1;

        while(get_ends(id).second < r) {
            int kiri = get_ends(id).first;
            int kanan = get_ends(id).second;

            // printf("%d kiri %d kanan %d\n", id, kiri, kanan);

            int rel = kiri - l + 1;

            bucket[tipe][id][0] += rel;
            bucket[tipe][id][0] %= MOD;

            int rel2 = 1ll * rel * rel % MOD;

            bucket[tipe][id][1] += rel2;
            bucket[tipe][id][1] %= MOD;

            int rel3 = 1ll * rel2 * rel % MOD;

            bucket[tipe][id][2] += rel3;
            bucket[tipe][id][2] %= MOD;

            bucket[tipe][id][3]++;

            sum[tipe][id][0] += cumulative_sum(rel, rel + kanan - kiri, 1);
            sum[tipe][id][0] %= MOD;

            sum[tipe][id][1] += cumulative_sum(rel, rel + kanan - kiri, 2);
            sum[tipe][id][1] %= MOD;

            sum[tipe][id][2] += cumulative_sum(rel, rel + kanan - kiri, 3);
            sum[tipe][id][2] %= MOD;

            id++;
        }

        i = get_ends(id).first;
        rebuild(tipe, id);

        // printf("id %d i %d r %d\n", id, i, r);
        while(i <= r) {
            add(tipe, i, i-l+1);
            i++;
        }
    }
}

int query_ret[2][3];

void query_bucket(int tipe, int l, int r) {
    // printf("query %d %d\n", l, r);

    int id_l = get_id(l);
    int en = get_ends(id_l).second;

    rebuild(tipe, id_l);

    int i = l;
    while(i <= min(en, r)) {
        // printf("tipe %d i %d:\n", tipe, i);
        for(int j = 0 ; j < 3 ; j++) {
            // printf("%d -> %lld\n", j, arr[tipe][i][j]);
            query_ret[tipe][j] = (query_ret[tipe][j] + arr[tipe][i][j]) % MOD;
        }
        i++;
    }

    if(r > en) {
        int id = id_l+1;

        while(get_ends(id).second < r) {
            for(int j = 0 ; j < 3 ; j++) {
                query_ret[tipe][j] = (query_ret[tipe][j] + sum[tipe][id][j]) % MOD;
            }

            id++;
        }

        // printf("id %d l %d\n", id, get_ends(id).first);
        i = get_ends(id).first;
        rebuild(tipe, id);
        while(i <= r) {
            // printf("tipe %d i %d:\n", tipe, i);
            for(int j = 0 ; j < 3 ; j++) {
                // printf("%d -> %lld\n", j, arr[tipe][i][j]);
                query_ret[tipe][j] = (query_ret[tipe][j] + arr[tipe][i][j]) % MOD;
            }
            i++;
        }
    }
}

int query(int l, int r) {
    memset(query_ret, 0, sizeof query_ret);

    query_bucket(0, l, r);
    query_bucket(1, l, r);

    long long ret = 0;
    ret += 2ll * query_ret[0][0];
    ret += 3ll * query_ret[0][1];
    ret += query_ret[0][2];
    ret %= MOD;

    ret -= 2ll * query_ret[1][0];
    ret -= 3ll * query_ret[1][1];
    ret -= query_ret[1][2];
    ret %= MOD;

    if(ret < 0) {
        ret += MOD;
    }

    return ret;
}

int main() {
    // for(int i = 1 ; i <= 10 ; i++)
    //     for(int j = 1 ; j <= 3 ; j++) {
    //         printf("%d %d sum %lld\n", i, j, cumulative_sum(1, i, j));
    //     }
    // scanf("%d %d", &n, &q);
    n = io();
    q = io();
    BUCKET = 343;

    for(int i = 0 ; i < q ; i++) {
        int opt, l, r;
        // scanf("%d %d %d", &opt, &l, &r);
        opt = io();
        l = io();
        r = io();
        l--; r--;

        if(opt >= 1) {
            update(opt-1, l, r);
        } else {
            printf("%d\n", query(l, r));
        }
    }
    return 0;
}

