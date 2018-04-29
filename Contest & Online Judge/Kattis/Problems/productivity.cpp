#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int INF = 1e9;

pair<int, int> arr[N];
int n, p;

int dp[N][N];
vector<pair<int, int>> v;
vector<int> special;

void read() {
    cin >> n >> p;
    for(int i = 0 ; i < n ; i++) {
        cin >> arr[i].first >> arr[i].second;
    }
}

void prepare() {
    memset(dp, -1, sizeof dp);

    sort(arr, arr + n, [](pair<int, int> a, pair<int, int> b) {
        if(a.first == b.first) {
            return a.second > b.second;
        }
        return a.first < b.first;
    });

    for(int i = 0 ; i < n ; i++) {
        bool contains = false;

        for(int j = i+1 ; j < n ; j++) {
            if(arr[i].first <= arr[j].first && arr[j].second <= arr[i].second) {
                contains = true;
            }
        }

        if(contains) {
            special.push_back(arr[i].second - arr[i].first);
        } else {
            v.push_back(arr[i]);
        }
    }

    sort(special.begin(), special.end(), [](int a, int b) {
        return a > b;
    });
}

int solve(int now, int sisa) {
    if(sisa < 0) return -INF;
    if(now == v.size()) return 0;

    int &ret = dp[now][sisa];
    if(ret != -1) return ret;

    ret = -INF;
    int st = -1;
    int en = INF;

    for(int i = now ; i < v.size() ; i++) {
        st = max(st, v[i].first);
        en = min(en, v[i].second);

        if(st >= en) {
            break;
        }

        ret = max(ret, en - st + solve(i+1, sisa-1));
    }

    return ret;
}

int work() {
    int ret = -INF;
    int add = 0;

    for(int i = 0 ; i <= special.size() ; i++) {
        ret = max(ret, add + solve(0, p - i));

        if(i < special.size()) {
            add += special[i];
        }
    }

    return ret;
}

int main() {
    read();
    prepare();
    cout << work() << endl;
    return 0;
}