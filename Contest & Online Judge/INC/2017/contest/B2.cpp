#include <bits/stdc++.h>
using namespace std;

const int M = 1e5 + 5;

int n, m, k;
vector<int> arr;

set<int> nope;
set<int> active;
priority_queue<pair<int, int>> pq;

map<int, int> batas_kiri;
map<int, int> batas_kanan;

void read() {
    scanf("%d %d %d", &n, &m, &k);
    arr = vector<int>(m);

    for(int &x : arr) {
        scanf("%d", &x);
    }
}

void prepare() {
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());

    for(int i = 0 ; i < arr.size() ; i++) {
        nope.insert(arr[i]);
    }
}

pair<int, int> get_limit(int x) {
    int l = 1;
    int r = n;

    auto it = nope.upper_bound(x);
    if(it != nope.end()) {
        r = min(1ll * r, (1ll * (*it) + x) / 2);
    }

    it = nope.lower_bound(x);
    if(it != nope.begin()) {
        it--;
        l = max(1ll * l, (1ll * (*it) + x + 1) / 2);
    }

    it = active.upper_bound(x);
    if(it != active.end()) {
        r = min(r, batas_kiri[*it] - 1);
    }

    it = active.lower_bound(x);
    if(it != active.begin()) {
        it--;
        l = max(l, batas_kanan[*it] + 1);
    }

    return {l, r};
}

int get_length(int x) {
    pair<int, int> ret = get_limit(x);
    // printf("x %d: %d %d\n", x, ret.first, ret.second);
    return max(0, ret.second - ret.first + 1);
}

int solve() {
    if(k >= arr.size()) {
        return n;
    }

    int ret = 0;

    for(int i = 0 ; i < arr.size() ; i++) {
        pq.push({get_length(arr[i]), arr[i]});
    }

    for(int i = 1 ; i < arr.size() ; i++) {
        int mid = (1ll * arr[i] + arr[i-1]) / 2;

        for(int j = -1 ; j <= 1 ; j++) {
            int cur = mid + j;
            cur = max(cur, 1);
            cur = min(cur, n);

            pq.push({get_length(cur), cur});
        }
    }

    for(int i = 0 ; i < k ; i++) {
        while(!pq.empty() && (active.count(pq.top().second) || get_length(pq.top().second) != pq.top().first)) {
            int cur = pq.top().second;
            // printf("%d expect %d get %d\n", cur, get_length(pq.top().second), pq.top().first);
            pq.pop();

            if(!active.count(cur)) {
                pq.push({get_length(cur), cur});
            }
        }

        if(pq.empty() || pq.top().first == 0) {
            break;
        }

        pair<int, int> now = pq.top();
        pq.pop();

        if(now.first == 0) {
            break;
        }

        ret += now.first;
        int idx = now.second;
        pair<int, int> lmt = get_limit(idx);

        // printf("%d -> %d %d\n", idx, lmt.first, lmt.second);

        batas_kiri[idx] = lmt.first;
        batas_kanan[idx] = lmt.second;
        active.insert(idx);
    }

    return ret;
}

int main() {
    read();
    prepare();
    printf("%d\n", solve());
    return 0;
}