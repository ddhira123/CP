#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

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

int w, p;
Point wells[N];
int start[N];
Point pipe[N];

int pset[2 * N];

void init() {
    memset(pset, -1, sizeof pset);
}

int finds(int x) {
    return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
    x = finds(x);
    y = finds(y);

    if(x != y) {
        pset[x] += pset[y];
        pset[y] = x;
    }
}

void read() {
    scanf("%d %d", &w, &p);
    for(int i = 0 ; i < w ; i++) {
        scanf("%d %d", &wells[i].x, &wells[i].y);
    }
    for(int i = 0 ; i < p ; i++) {
        scanf("%d %d %d", &start[i], &pipe[i].x, &pipe[i].y);
        start[i]--;
    }
}

// graph has useful characteristic, so we can use DSU to check 2-SAT
void build_graph() {
    for(int i = 0 ; i < p ; i++) {
        for(int j = i+1 ; j < p ; j++) {
            if(start[i] == start[j]) continue;

            if(intersect(wells[start[i]], pipe[i], wells[start[j]], pipe[j])) {
                join(i, j+p);
                join(j, i+p);
            }
        }
    }
}

bool work() {
    init();
    build_graph();

    for(int i = 0 ; i < p ; i++) {
        if(finds(i) == finds(i+p)) {
            return false;
        }
    }

    return true;
}

int main() {
    read();

    printf("%s\n", work() ? "possible" : "impossible");
    return 0;
}