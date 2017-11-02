#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int INF = 1e9 + 5;
const int BUCKET = 333;

vector<int> bucket[2][BUCKET];
vector<long long> sum[2][BUCKET];
int mins[2][BUCKET];
int val[2][N + 5];

bool udah[N + 5];

set<int> active[2];

int q;

void update_bucket(int id) {
    for(int i = 0 ; i < 2 ; i++) {
        bucket[i][id].clear();
        sum[i][id].clear();

        int atas = min(id * BUCKET + BUCKET - 1, N-1);
        for(int j = id * BUCKET ; j <= atas ; j++) {
            if(udah[j])
                bucket[i][id].push_back(min(mins[i][id], val[i][j]));
        }

        sort(bucket[i][id].begin(), bucket[i][id].end());
        for(int x : bucket[i][id]) {
            long long cur = x;
            if(!sum[i][id].empty()) cur += sum[i][id].back();
            sum[i][id].push_back(cur);
        }
    }
}

void add_to_bucket(int pos) {
    int id = pos / BUCKET;
    update_bucket(id);
}

void update(int l, int r, int vals) {
    int tipe = 0;

    if(vals < 0) {
        vals = -vals;
        tipe = 1;
    }

    int i = l;
    int nex = i / BUCKET * BUCKET + BUCKET - 1;
    nex = min(nex, r);

    while(i <= nex) {
        val[tipe][i] = min(val[tipe][i], vals);
        i++;
    }

    update_bucket(l / BUCKET);

    if(nex < r) {
        int pos = i / BUCKET;
        while(pos * BUCKET + BUCKET - 1 < r) {
            mins[tipe][pos] = min(mins[tipe][pos], vals);
            i += BUCKET;
            pos++;
        }

        while(i <= r) {
            val[tipe][i] = min(val[tipe][i], vals);
            i++;
        }

        update_bucket(r / BUCKET);
    }

    while(1) {
        auto it = active[tipe].lower_bound(l);
        if(it == active[tipe].end() || *it > r) {
            break;
        }
        int pos = *it;

        // printf("pos %d tipe %d\n", pos, tipe);

        if(!udah[pos] && !active[tipe ^ 1].count(pos)) {
            udah[pos] = true;
            // printf("add %d\n", pos);
            add_to_bucket(pos);
        }

        active[tipe].erase(pos);
    }
}

long long query(int l, int r) {
    int i = l;
    int nex = i / BUCKET * BUCKET + BUCKET - 1;
    nex = min(nex, r);
    long long ret = 0;

    int buck = i / BUCKET;

    // printf("l %d r %d i %d nex %d\n", l, r, i, nex);
    while(i <= nex) {
        // printf("i %d %d\n", i, udah[i]);
        if(udah[i]) {
            // printf("proses %d\n", i);
            int atas = min(val[0][i], mins[0][buck]);
            int bawah = min(val[1][i], mins[1][buck]);
            
            // printf("atas %d bawah %d\n", atas, bawah);
            ret += atas;
            ret += bawah;
        }

        i++;
    }

    if(nex < r) {
        int pos = i / BUCKET;
        while(pos * BUCKET + BUCKET - 1 < r) {
            if(!bucket[0][pos].empty()) {
                vector<int> &v = bucket[0][pos];
                int lb = lower_bound(v.begin(), v.end(), mins[0][pos]) - v.begin();

                if(lb > 0) {
                    ret += sum[0][pos][lb-1];
                }
                ret += 1ll * mins[0][pos] * (v.size() - lb);

                vector<int> &y = bucket[1][pos];
                lb = lower_bound(y.begin(), y.end(), mins[1][pos]) - y.begin();

                if(lb > 0) {
                    ret += sum[1][pos][lb-1];
                }
                ret += 1ll * mins[1][pos] * (y.size() - lb);
            }

            i += BUCKET;
            pos++;
        }

        buck = i / BUCKET;
        while(i <= r) {
            if(udah[i]) {
                ret += min(val[0][i], mins[0][buck]);
                ret += min(val[1][i], mins[1][buck]);
            }

            i++;
        }
    }

    return ret;
}

void init() {
    for(int i = 0 ; i < 2 ; i++)
        for(int j = 0 ; j < N ; j++) {
            active[i].insert(j);
            int idx = j / BUCKET;

            mins[0][idx] = INF;
            mins[1][idx] = INF;
            val[0][j] = INF;
            val[1][j] = INF;
        }
}

int main() {
    init();
    scanf("%d", &q);

    for(int i = 0 ; i < q ; i++) {
        int tipe;
        scanf("%d", &tipe);

        if(tipe == 1) {
            int l, r, k;
            scanf("%d %d %d", &l, &r, &k);
            l--; r -= 2;
            update(l, r, k);
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--; r -= 2;
            printf("%lld\n", query(l, r));
        }
    }
    return 0;
}