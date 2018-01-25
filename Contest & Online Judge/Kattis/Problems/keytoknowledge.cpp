#include <bits/stdc++.h>
using namespace std;

const int N = 12;
const int M = 30;

map<vector<int>, vector<int>> low, high;
int val[N];
int same[N];
int n, m;

void read() {
    cin >> n >> m;
    for(int i = 0 ; i < n ; i++) {
        string s;
        cin >> s >> same[i];

        val[i] = 0;
        for(int j = 0 ; j < m ; j++) {
            if(s[j] == '1') {
                val[i] |= (1 << j);
            }
        }
    }
}

void rec(map<vector<int>, vector<int>> &mp, int msk, int cur, int en, int st) {
    if(cur == en) {
        vector<int> v;
        for(int i = 0 ; i < n ; i++) {
            int same = 0;

            for(int j = st ; j < en ; j++) {
                int cur_val = msk & (1 << j);
                int i_val = val[i] & (1 << j);

                if(cur_val == i_val) same++;
            }

            v.push_back(same);
        }

        if(mp.count(v)) {
            // int sz = mp[v].size();
            mp[v].push_back(msk);
            // assert(mp[v].size() == sz+1);
        } else {
            mp[v] = {msk};
            // assert(mp[v].size() == 1);
        }
    } else {
        rec(mp, msk, cur+1, en, st);
        rec(mp, msk | (1 << cur), cur+1, en, st);
    }
}

void work() {
    if(m == 1) {
        for(int ans = 0 ; ans < 2 ; ans++) {
            bool ok = true;

            for(int i = 0 ; i < n ; i++) {
                if(ans != val[i] && same[i] == 1) {
                    ok = false;
                } else if(ans == val[i] && same[i] == 0) {
                    ok = false;
                }
            }

            if(ok) {
                cout << ans << endl;
                return;
            }
        }
        cout << "0 solutions\n";
    } else {
        vector<int> v(n, 0);

        // cout << "init rec" << endl;
        rec(low, 0, 0, m/2, 0);
        // cout << "sudah 1" << endl;
        rec(high, 0, m/2, m, m/2);
        // cout << "sudah 2" << endl;

        int ret = 0;
        for(auto it : low) {
            vector<int> v = it.first;
            for(int i = 0 ; i < v.size() ; i++) {
                v[i] = same[i] - v[i];
            }

            if(high.count(v)) {
                ret += it.second.size() * high[v].size();
            }
        }

        if(ret == 1) {
            for(auto it : low) {
                vector<int> v = it.first;
                for(int i = 0 ; i < v.size() ; i++) {
                    v[i] = same[i] - v[i];
                }

                if(high.count(v)) {
                    ret = it.second[0] | high[v][0];
                }
            }

            for(int i = 0 ; i < m ; i++) {
                int cur = ret & (1 << i);
                cur = cur > 0;

                cout << cur;
            }

            cout << endl;
        } else {
            cout << ret << " solutions\n";
        }
    }
}

void reset() {
    low.clear();
    high.clear();
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        work();
        reset();
    }
    return 0;
}