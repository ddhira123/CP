#include <bits/stdc++.h>
using namespace std;

int main() {
    int k; cin >> k;

    if(k == 1) {
        cout << "0 0\n";
        return 0;
    }

    k -= 1;
    for(int i = 4 ; ; i += 4) {
        if(i >= k) {
            int step = i / 4;
            int row, col;

            row = 0;
            col = -step;

            if(k == 1) {
                row = 0;
                col = -step;
            } else {
                row = 0;
                col = -step;

                k--;
                // cout << k << endl;
                for(int j = 1 ; ; j++) {
                    int cr = row + j;
                    int cc = col + j;

                    k--;
                    if(k == 0) {
                        row = cr;
                        col = cc;
                        goto hell;
                    }

                    cr = row - j;
                    cc = col + j;

                    if(cr == -step) {
                        break;
                    }

                    k--;
                    if(k == 0) {
                        row = cr;
                        col = cc;
                        goto hell;
                    }
                }

                row = step;
                col = 0;
                for(int j = 1 ; ; j++) {
                    int cr = row - j;
                    int cc = col + j;

                    k--;
                    if(k == 0) {
                        row = cr;
                        col = cc;
                        goto hell;
                    }

                    if(cr == 0) {
                        break;
                    }
                }

                row = 0;
                col = step;
                for(int j = 1 ; ; j++) {
                    int cr = row - j;
                    int cc = col - j;

                    k--;
                    if(k == 0) {
                        row = cr;
                        col = cc;
                        goto hell;
                    }
                }
            }

            hell:
            swap(row, col);
            cout << row << " " << col << endl;
            break;
        } else {
            k -= i;
        }
    }
    return 0;
}