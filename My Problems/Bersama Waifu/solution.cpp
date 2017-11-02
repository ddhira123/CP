#include <bits/stdc++.h>
using namespace std;

const int N = 205;

struct Point {
    int x;
    int y;
};

int cross(Point p, Point q, Point r) {
    int dx1 = q.x - p.x;
    int dy1 = q.y - p.y;
    int dx2 = r.x - p.x;
    int dy2 = r.y - p.y;

    return dx1 * dy2 - dy1 * dx2;
}


// check pq -> r
int orientation(Point p, Point q, Point r) {
    if(cross(p, q, r) == 0) {
        return 0;
    }

    return cross(p, q, r) < 0 ? -1 : 1;
}


// check whether q is in pr segment
bool on_segment(Point p, Point q, Point r) {
    if(orientation(p, q, r) != 0) {
        return false;
    }

    bool inside_x = min(p.x, r.x) <= q.x && q.x <= max(p.x, r.x);
    bool inside_y = min(p.y, r.y) <= q.y && q.y <= max(p.y, r.y);

    return inside_x && inside_y;
}

// taken from http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool intersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && on_segment(p1, p2, q1)) return true;

    if (o2 == 0 && on_segment(p1, q2, q1)) return true;
 
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;
 
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;
 
    return false;
}

vector<int> adj[N];
bool vis[N];
int match[N];

Point arr[N];
Point a, b;
int n;

int augment(int now) {
    if(vis[now]) return 0;
    vis[now] = true;

    for(int nex : adj[now]) {
        if(match[nex] == -1 || augment(match[nex])) {
            match[nex] = now;
            return 1;
        }
    }

    return 0;
}

int mcbm(int _n) {
    memset(match, -1, sizeof match);

    int ret = 0;
    for(int i = 0 ; i < _n ; i++) {
        memset(vis, false, sizeof vis);
        ret += augment(i);
    }

    return ret;
}

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d %d", &arr[i].x, &arr[i].y);
    }
    scanf("%d %d %d %d", &a.x, &a.y, &b.x, &b.y);
}

int solve() {
    vector<Point> cw, ccw;
    int in_segment = 0;
    int out_segment = 0;

    for(int i = 0 ; i < n ; i++) {
        int ori = orientation(a, b, arr[i]);

        if(ori == 0) {
            if(on_segment(a, arr[i], b)) {
                in_segment++;
            } else {
                out_segment++;
            }
        } else if(ori == -1) {
            cw.push_back(arr[i]);
        } else {
            ccw.push_back(arr[i]);
        }
    }

    for(int i = 0 ; i < cw.size() ; i++)
        for(int j = 0 ; j < ccw.size() ; j++) {

            // intersect ab
            if(intersect(cw[i], ccw[j], a, b)) {
                // but laser will cut through a or b
                if(on_segment(cw[i], a, ccw[j]) || on_segment(cw[i], b, ccw[j])) {
                    adj[i].push_back(j);
                }
            } else {
                adj[i].push_back(j);
            }
        }

    int delete_in_segment = in_segment;
    int keep_in_segment = out_segment + mcbm(cw.size());

    return min(delete_in_segment, keep_in_segment);
}

void reset() {
    for(int i = 0 ; i < N ; i++) {
        adj[i].clear();
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("%d\n", solve());
        reset();
    }
    return 0;
}
