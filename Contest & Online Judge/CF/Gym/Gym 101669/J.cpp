#include <bits/stdc++.h>
using namespace std;

map<pair<vector<int>, int>, int> dp;

int solve(vector<int> v, int pos) {
    int tot = accumulate(v.begin(), v.end(), 0);
    if (tot == 0) return pos != 0;

    pair<vector<int>, int> state = {v, pos};
    if (dp.count(state)) return dp[state];

    for (int i = 0 ; i < v.size() ; i++) {
        for (int j = 1 ; j <= v[i] ; j++) {
            vector<int> tmp = v;
            tmp[i] -= j;

            int val = solve(tmp, (pos + 1) % 3);
            if (pos == 0 && val == 1) {
                return dp[state] = 1;
            }
            if (pos != 0 && val == 0) {
                return dp[state] = 0;
            }
        }
    }

    if (pos == 0) return dp[state] = 0;
    return dp[state] = 1;
}

void dfs(int sz, vector<int> v, int lim) {
    if (v.size() == sz) {
        for (int i = 1 ; i < sz ; i++)
            if (v[i] < v[i-1]) return;
        int yey = solve(v, 0);
        if (!yey) return;
        
        // int zero = 0;
        // for (int i = 0 ; i < sz ; i++) zero += v[i] == 0;
        // printf("")

        for (int i = 0 ; i < sz ; i++)
            printf("%d ", v[i]);
        printf("-> %s\n", yey ? "WIN" : "LOSE");
    } else {
        for (int i = 0 ; i <= lim ; i++) {
            vector<int> tmp = v;
            tmp.push_back(i);

            dfs(sz, tmp, lim);
        }
    }
}

int main() {
    int sz = 10;
    int lim = 2;
    vector<int> tmp;

    dfs(sz, tmp, lim);
    return 0;
}