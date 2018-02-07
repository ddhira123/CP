#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

struct Data {
    int mx;
    int ways;

    Data(int _m = 0, int _w = 1) {
        mx = _m;
        ways = _w;
    }

    Data operator +(Data other) const {
        Data ret;

        if(mx > other.mx) ret = *this;
        else if(mx < other.mx) ret = other;
        else ret = Data(mx, (ways + other.ways) % MOD);

        return ret;
    }

    bool operator ==(Data other) const {
        return mx == other.mx && ways == other.ways;
    }
};

int n;
Data BIT[N];
int arr[N];

void update(int x, Data val) {
    for(; x <= n ; x += x & -x) {
        BIT[x] = BIT[x] + val;
    }
}

Data query(int x) {
    Data ret;

    while(x) {
        ret = ret + BIT[x];
        x -= x & -x;
    }

    return ret;
}

vector<Data> solve() {
    for(int i = 1 ; i <= n ; i++) {
        BIT[i] = Data(0, 0);
    }

    vector<Data> ret;

    for(int i = 0 ; i < n ; i++) {
        Data val = query(arr[i]);
        val.mx++;

        ret.push_back(val);
        update(arr[i], val);
    }

    return ret;
}

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }
}

vector<int> work() {
    vector<Data> lis = solve();
    Data best = query(n);

    reverse(arr, arr + n);
    for(int i = 0 ; i < n ; i++) {
        arr[i] = n - arr[i] + 1;
    }

    vector<Data> lds = solve();

    reverse(lds.begin(), lds.end());
    reverse(arr, arr + n);

    vector<int> ans;
    for(int i = 0 ; i < n ; i++) {
        arr[i] = n - arr[i] + 1;

        int mx = lis[i].mx + lds[i].mx - 1;
        int ways = 1ll * lis[i].ways * lds[i].ways % MOD;
        Data cur = Data(mx, ways);

        if(cur == best) {
            ans.push_back(arr[i]);
        }
    }

    sort(ans.begin(), ans.end());

    return ans;
}

int main() {
    read();
    vector<int> ans = work();

    if(ans.empty()) {
        puts("-1");
    } else {
        for(int i = 0 ; i < ans.size() ; i++) {
            printf("%d%c", ans[i], i+1 == ans.size() ? '\n' : ' ');
        }
    }
    return 0;
}