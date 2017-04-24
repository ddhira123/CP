#include <bits/stdc++.h>
using namespace std;

void OPEN(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void CLOSE() {
	fclose(stdin);
	fclose(stdout);
}

const int N = 1005;
const double INF = 4e18;

struct data {
	double dist;
	double xOpt;
	double yOpt;

	bool operator <(data other) const {
		return dist > other.dist;
	}
};

data getMiddle(double xa, double ya, double xb, double yb) {
	double dist = hypot(xa - xb, ya - yb);
	data ret;
	ret.dist = dist / 2;
	ret.xOpt = (xa + xb) / 2;
	ret.yOpt = (ya + yb) / 2;
	return ret;
}

data dist[N][2];
bool udah[N][2];
double x[N], y[N];
int n;
double w;

void dijkstra() {
	if(n == 0) {
		printf("%.9lf 1\n", w/2);
		return;
	}
	priority_queue<pair<data,pair<int,int>>> pq;

	for(int i = 1 ; i <= n ; i++) {
		dist[i][1] = (data){x[i], x[i], y[i]};
		dist[i][0] = (data){x[i]/2, x[i]/2, y[i]};

		pq.push({dist[i][1], {i, 1}});
		pq.push({dist[i][0], {i, 0}});
	}

	while(!pq.empty()) {
		data tmp = pq.top().first;
		pair<int,int> state = pq.top().second;
		pq.pop();

		if(udah[state.first][state.second]) continue;

		udah[state.first][state.second] = 1;
		//printf("%d %d dist %.9lf\n", state.first, state.second, tmp.dist);

		for(int i = 1 ; i <= n ; i++) {
			// gak pake
			double dst = hypot(x[i] - x[state.first], y[i] - y[state.first]);
			if(max(dst, tmp.dist) < dist[i][state.second].dist) {
				dist[i][state.second] = {max(dst, tmp.dist), tmp.xOpt, tmp.yOpt};
				pq.push({dist[i][state.second], {i, state.second}});
			}

			// pake
			if(state.second == 1) {
				data haha = getMiddle(x[state.first], y[state.first], x[i], y[i]);
				if(max(haha.dist, tmp.dist) < dist[i][0].dist) {
					dist[i][0] = {max(haha.dist, tmp.dist), haha.xOpt, haha.yOpt};
					pq.push({dist[i][0], {i, 0}});
				}
			}
		}
	}

	data ret = {4e18, -1, -1};
	for(int i = 1 ; i <= n ; i++) {
		dist[i][0].dist = max(dist[i][0].dist, w - x[i]);
		if(dist[i][0].dist < ret.dist) {
			ret = dist[i][0];
		}

		data haha = getMiddle(x[i], y[i], w, y[i]);
		haha.dist = max(haha.dist, dist[i][1].dist);
		if(haha.dist < ret.dist) {
			ret = haha;
		}
	}

	//printf("%.9lf\n", ret.dist);
	printf("%.9lf %.9lf\n", ret.xOpt, ret.yOpt);
}

void read() {
	cin >> w >> n;
	for(int i = 1 ; i <= n ; i++)
		cin >> x[i] >> y[i];
}

int main() {
	OPEN("froggy");
	read();
	dijkstra();
	CLOSE();
	return 0;
}