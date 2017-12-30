#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int arr[N];
char color[N];
int n;

void read() {
    cin >> n;
    for(int i = 0 ; i < n ; i++) {
        cin >> arr[i] >> color[i];
    }
}

bool green_exist() {
    for(int i = 0 ; i < n ; i++) {
        if(color[i] == 'G') {
            return true;
        }
    }

    return false;
}

int independent() {
    int lst_b = -1;
    int lst_r = -1;
    int ret = 0;

    for(int i = 0 ; i < n ; i++) {
        if(color[i] == 'R') {
            if(lst_r != -1) ret += (arr[i] - lst_r);
            lst_r = arr[i];
        } else if(color[i] == 'B') {
            if(lst_b != -1) ret += (arr[i] - lst_b);
            lst_b = arr[i];
        }
    }

    return ret;
}

pair<int, int> existing_colors(int l, int r) {
    int red = false;
    int blue = false;

    for(int i = l+1 ; i < r ; i++) {
        if(color[i] == 'R') red = true;
        if(color[i] == 'B') blue = true;
    }

    return {blue, red};
}

int solve(int l, int r) {
    pair<int, int> colors = existing_colors(l, r);

    if(colors.first + colors.second == 0) {
        return arr[r] - arr[l];
    }

    if(colors.first + colors.second == 1) {
        int max_diff = arr[l+1] - arr[l];
        max_diff = max(max_diff, arr[r] - arr[r-1]);

        for(int i = l+2 ; i < r ; i++) {
            max_diff = max(max_diff, arr[i] - arr[i-1]);
        }

        return 2 * (arr[r] - arr[l]) - max_diff;
    }

    int ret = 2 * (arr[r] - arr[l]);

    int lst_b = arr[l];
    int lst_r = arr[l];
    int max_diffr = 0;
    int max_diffb = 0;

    for(int i = l+1 ; i <= r ; i++) {
        if(color[i] == 'R' || color[i] == 'G') {
            max_diffr = max(max_diffr, arr[i] - lst_r);
            lst_r = arr[i];
        }
        if(color[i] == 'B' || color[i] == 'G') {
            max_diffb = max(max_diffb, arr[i] - lst_b);
            lst_b = arr[i];
        }
    }

    ret = min(ret, 3 * (arr[r] - arr[l]) - max_diffr - max_diffb);

    return ret;
}

int work() {
    if(!green_exist()) {
        return independent();
    }

    pair<int, int> colors = existing_colors(-1, n);
    if(colors.first + colors.second <= 1) {
        return arr[n-1] - arr[0];
    }

    int lst = -1;
    int ret = 0;

    for(int i = 0 ; i < n ; i++) {
        if(color[i] == 'G') {
            if(lst != -1) ret += solve(lst, i);
            else {
                int b = 0;
                int r = 0;
                for(int j = 0 ; j < i ; j++) {
                    if(color[j] == 'R' && r == 0) {
                        ret += arr[i] - arr[j];
                        r = 1;
                    } else if(color[j] == 'B' && b == 0) {
                        ret += arr[i] - arr[j];
                        b = 1;
                    }
                }
            }
            lst = i;
        }
    }

    {
        int b = 0;
        int r = 0;
        for(int j = n-1 ; j > lst ; j--) {
            if(color[j] == 'R' && r == 0) {
                ret += arr[j] - arr[lst];
                r = 1;
            } else if(color[j] == 'B' && b == 0) {
                ret += arr[j] - arr[lst];
                b = 1;
            }
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    read();
    cout << work() << endl;
    return 0;
}

