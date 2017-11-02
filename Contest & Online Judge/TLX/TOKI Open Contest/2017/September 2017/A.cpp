#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> precompute() {
    vector<int> num(8);
    iota(num.begin(), num.end(), 1);

    vector<vector<int>> ret;
    do {
        int a = num[0] * 10 + num[1];
        int b = num[2] * 10 + num[3];
        int c = num[4] * 1000 + num[5] * 100 + num[6] * 10 + num[7];

        if(a * b == c) {
            ret.push_back(vector<int>({a, b, c}));
        }
    } while(next_permutation(num.begin(), num.end()));

    return ret;
}

int main() {
    vector<vector<int>> ans = precompute();

    int n; cin >> n;

    for(int i = 0 ; i < n ; i++) {
        cout << ans[i][0] << "x" << ans[i][1] << "=" << ans[i][2] << endl;
    }
    return 0;
}