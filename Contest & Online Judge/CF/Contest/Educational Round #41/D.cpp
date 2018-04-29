#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    bool operator <(Point other) const {
        return x == other.x ? y < other.y : x < other.x;
    }
};

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

long long sqr(long long z) {
    return z * z;
}

long long cross(Point p, Point q, Point r) {
    long long dx1 = q.x - p.x;
    long long dy1 = q.y - p.y;
    long long dx2 = r.x - p.x;
    long long dy2 = r.y - p.y;

    return dx1 * dy2 - dx2 * dy1;
}

long long dist(Point p, Point q) {
    return sqr(p.x - q.x) + sqr(p.y - q.y);
}

const int N = 2e5 + 5;
const pair<int, int> IMPOSSIBLE = {-1, -1};

int n;
Point arr[N];
pair<int, int> pref[N], suf[N];

pair<int, int> get_line(int i, int j) {
    int dy = arr[j].y - arr[i].y;
    int dx = arr[j].x - arr[i].x;

    if(dy < 0) {
        dy = -dy;
        dx = -dx;
    }

    int fpb = gcd(abs(dy), abs(dx));
    dy /= fpb;
    dx /= fpb;

    return {dy, dx};
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d %d", &arr[i].x, &arr[i].y);
    }
}

void prepare() {
    sort(arr + 1, arr + n + 1);
    sort(arr + 2, arr + n + 1, [&](Point a, Point b) {
        if(cross(arr[1], a, b) == 0) {
            return dist(arr[1], a) < dist(arr[1], b);
        }
        
        return cross(arr[1], a, b) > 0;
    });

    for(int i = 2 ; i+1 <= n ; i++) {
        pair<int, int> lin = get_line(i, i+1);
        if(i == 2) {
            pref[i+1] = lin;
        } else {
            if(pref[i] == IMPOSSIBLE || pref[i] != lin) {
                pref[i+1] = IMPOSSIBLE;
            } else {
                pref[i+1] = lin;
            }
        }
    }

    for(int i = n ; i-1 >= 2 ; i--) {
        pair<int, int> lin = get_line(i-1, i);
        if (i == n) {
            suf[i - 1] = lin;
        }
        else {
            if (suf[i] == IMPOSSIBLE || suf[i] != lin) {
                suf[i-1] = IMPOSSIBLE;
            }
            else {
                suf[i-1] = lin;
            }
        }
    }
}

bool work() {
    for (int i = 2; i <= n;) {
        int j = i;

        while (j <= n && cross(arr[1], arr[i], arr[j]) == 0) {
            j++;
        }
        j--;

        if (i == 2) {
            if (j >= n-2) {
                return true;
            }
            if(suf[j+1] != IMPOSSIBLE) {
                return true;
            }
        } else if(i == 3) {
            if(j >= n-1) {
                return true;
            }
            if(suf[j+1] != IMPOSSIBLE && suf[j+1] == get_line(2, n)) {
                return true;
            }
        } else {
            if(pref[i-1] != IMPOSSIBLE) {
                if(j == n) {
                    return true;
                }
                if(j == n-1 && pref[i-1] == get_line(2, n)) {
                    return true;
                }
                if(pref[i-1] == suf[j+1] && pref[i-1] == get_line(2, n)) {
                    return true;
                }
            }
        }

        i = j+1;
    }

    return false;
}

int main() {
    read();
    if(n <= 4) {
        puts("YES");
    } else {
        prepare();
        printf("%s\n", work() ? "YES" : "NO");
    }
    return 0;
}