#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int n, m;
char s[N][N];

int up[N];

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < n ; i++) {
        scanf("%s", s[i]);
    }
}

int work() {
    int ret = 0;

    for(int i = 0 ; i < n ; i++) {
        vector<pair<int, int>> v;

        for(int j = 0 ; j < m ; j++) {
            up[j] = (s[i][j] == '.' ? up[j] + 1 : 0);
            int lst = j;

            while(!v.empty() && v.back().first >= up[j]) {
                lst = v.back().second;

                int row = v.back().first;
                int col = j - lst;

                if(row > 0) {
                    ret = max(ret, 2 * (row + col));
                }

                v.pop_back();
            }

            v.push_back({up[j], lst});
        }

        while(!v.empty()) {
            int row = v.back().first;
            int col = m - v.back().second;

            if(row > 0) {
                ret = max(ret, 2 * (row + col));
            }

            v.pop_back();
        }
    }

    ret -= 1;

    return ret;
}

int main() {
    read();
    cout << work() << endl;
    return 0;
}