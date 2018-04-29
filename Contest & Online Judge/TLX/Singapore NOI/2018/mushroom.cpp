#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;

string read_string() {
    static char s[MX];
    scanf("%s", s);

    return (string)s;
}

vector<vector<int>> psum;
vector<pair<int, int>> mushroom;

int r, c, d, k;

void read() {
    scanf("%d %d %d %d", &r, &c, &d, &k);

    psum = vector<vector<int>>(r+2, vector<int>(c+2, 0));

    for(int i = 1 ; i <= r ; i++) {
        string cur = read_string();

        for(int j = 1 ; j <= c ; j++) {
            if(cur[j-1] == 'M') {
                mushroom.push_back({i, j});
            } else if(cur[j-1] == 'S') {
                int atas = max(1, i - d);
                int bawah = min(r, i + d);

                int kiri = max(1, j - d);
                int kanan = min(c, j + d);

                psum[atas][kiri]++;
                psum[atas][kanan+1]--;
                psum[bawah+1][kiri]--;
                psum[bawah+1][kanan+1]++;
            }
        }
    }
}

void prepare() {
    for(int i = 1 ; i <= r ; i++)
        for(int j = 1 ; j <= c ; j++) {
            psum[i][j] += psum[i-1][j] + psum[i][j-1];
            psum[i][j] -= psum[i-1][j-1];
        }
}

int work() {
    int ret = 0;

    for(pair<int, int> it : mushroom) {
        if(psum[it.first][it.second] >= k) {
            ret++;
        }
    }

    return ret;
}

int main() {
    read();
    prepare();
    printf("%d\n", work());
    return 0;
}