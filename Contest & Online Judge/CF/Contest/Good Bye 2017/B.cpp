#include <bits/stdc++.h>
using namespace std;

int dr[4] = {-1, 0, 1 ,0};
int dc[4] = {0, 1, 0, -1};

string arr[55];
int n, m;
string s;

void read() {
    cin >> n >> m;
    for(int i = 0 ; i < n ; i++) {
        cin >> arr[i];
    }
    cin >> s;
}

int work() {
    int rs = -1, cs = -1;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++) {
            if(arr[i][j] == 'S') {
                rs = i;
                cs = j;
            }
        }

    int permut[4] = {0, 1, 2, 3};
    int ret = 0;

    do {
        int rr = rs;
        int cc = cs;
        bool ok = false;

        for(int i = 0 ; i < s.length() ; i++) {
            char opt = s[i];

            int nr = rr + dr[permut[opt - '0']];
            int nc = cc + dc[permut[opt - '0']];

            rr = nr;
            cc = nc;

            if(cc < 0 || cc == m || rr == n || rr < 0 || arr[rr][cc] == '#') {
                ok = false;
                break;
            }

            if(arr[rr][cc] == 'E') {
                ok = true;
                break;
            }
        }

        ret += ok;
    } while(next_permutation(permut, permut + 4));

    return ret;
}

int main() {
    read();
    cout << work() << endl;
    return 0;
}

