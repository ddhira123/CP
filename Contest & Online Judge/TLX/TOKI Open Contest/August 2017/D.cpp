#include <bits/stdc++.h>
using namespace std;

const int N = 205;

struct point {
	int x;
	int y;
};

long long cross(point p, point q, point r) {
	long long dx1 = q.x - p.x;
	long long dy1 = q.y - p.y;
	long long dx2 = r.x - p.x;
	long long dy2 = r.y - p.y;

	return dx1 * dy2 - dx2 * dy1;
}

bool is_ccw(point p, point q, point r) {
	return cross(p, q, r) > 0;
}

point arr[N];
point pivot;
int n;

bool cmp(point a, point b) {
	return is_ccw(pivot, a, b);
}

int main() {
	scanf("%d", &n);
	assert(4 <= n && n <= 200);
	for(int i = 0 ; i < n ; i++) {
		scanf("%d %d", &arr[i].x, &arr[i].y);
	}

	int ret = 0;
	for(int mid = 0 ; mid < n ; mid++) {
		for(int i = 0 ; i < n ; i++)
			if(mid != i) {
				vector<point> cw, ccw;

				for(int j = 0 ; j < n ; j++)
					if(j != mid && j != i) {
						if(is_ccw(arr[mid], arr[i], arr[j]))
							ccw.push_back(arr[j]);
						else
							cw.push_back(arr[j]);
					}

				pivot = arr[mid];
				sort(cw.begin(), cw.end(), cmp);

				if(!cw.empty()) {
					for(point x : ccw) {
						int lo = 0;
						int hi = (int)cw.size()-1;

						while(lo < hi) {
							int m = (lo + hi + 1) / 2;
							if(!is_ccw(x, arr[mid], cw[m]))
								lo = m;
							else
								hi = m-1;
						}

						if(!is_ccw(x, arr[mid], cw[lo])) {
							ret += lo+1;
						}
					}
				}
			}
	}

	printf("%d\n", ret / 3);
	return 0;
}