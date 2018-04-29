#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int off(int x) {
    return x + rand() % 3 - 1;
}

// pair<int, int> get_random(int x, int y) {
//     return {off(x), off(y)};
// }
pair<int, int> get_gopher(int x, int y) {
    // return get_random(x, y);

    printf("%d %d\n", x, y);
    fflush(stdout);

    scanf("%d %d", &x, &y);
    return {x, y};
}

int arr[N][N];
int a;

int area(int x) {
    int ret = 0;

    for(int i = x-1 ; i <= x+1 ; i++) {
        for(int j = 1 ; j <= 3 ; j++) {
            ret += arr[i][j];
        }
    }

    return ret;
}

vector<int> recalculate(int lmt) {
    vector<int> ret;

    for(int i = 2 ; i <= lmt ; i++) {
        ret.push_back(i);
    }

    sort(ret.begin(), ret.end(), [&](int a, int b) {
        if(area(a) == area(b)) {
            return a < b;
        }
        return area(a) > area(b);
    });

    return ret;
}

void read() {
    scanf("%d", &a);
}

void work() {
    memset(arr, 0, sizeof(arr));

    int lmt = (a + 2) / 3 - 1;

    vector<int> v = recalculate(lmt);

    for(int i = 1 ; i <= 1001 ; i++) {
        // printf("%d %d\n", v.back(), area(v.back()));
        assert(i < 1001);

        int pos = v.back();

        pair<int, int> cur = get_gopher(pos, 2);
        // printf("pos %d r %d c %d\n", pos, cur.first, cur.second);
        if(cur.first == 0) {
            break;
        }
        
        if(!arr[cur.first][cur.second]) {
            arr[cur.first][cur.second] = 1;
            v = recalculate(lmt);

            if(area(v.back()) == 9) {
                break;
            }
        }
    }
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        work();
    }
    return 0;
}