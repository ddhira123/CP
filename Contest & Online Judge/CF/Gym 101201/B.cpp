#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

typedef pair<int, int> pii;

struct data {
	int rr;
	int cc;
	int com;
	int dst;
};

pii translate(char c) {
	if(c == 'U') return {-1, 0};
	if(c == 'D') return {1, 0};
	if(c == 'L') return {0, -1};
	return {0, 1};
}

int ch[4] = {'U', 'D', 'L', 'R'};

int dist[MAXN][MAXN][MAXN];
string arr[MAXN];
int r, c;
string cmd;

void read() {
	cin >> r >> c;
	for(int i = 0 ; i < r ; i++)
		cin >> arr[i];
	cin >> cmd;
}

int solve() {
	for(int i = 0 ; i < MAXN ; i++)
		for(int j = 0 ; j < MAXN ; j++)
			for(int k = 0 ; k < MAXN ; k++)
				dist[i][j][k] = 1e9;

	int rs, cs;
	int re, ce;

	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			if(arr[i][j] == 'R') {
				rs = i;
				cs = j;
			} else if(arr[i][j] == 'E') {
				re = i;
				ce = j;
			}

	dist[rs][cs][0] = 0;
	deque<data> q;
	q.push_back((data){rs, cs, 0, 0});

	while(!q.empty()) {
		data now = q.front();
		q.pop_front();

		int rr = now.rr;
		int cc = now.cc;
		int com = now.com;
		int dst = now.dst;

		if(dist[rr][cc][com] != dst) continue;
		if(rr == re && cc == ce) return dst;

		if(com < cmd.length()) {
			pii add = translate(cmd[com]);
			int nr = rr + add.first;
			int nc = cc + add.second;
			int ndst = dst;

			if(nr >= 0 && nr < r && nc >= 0 && nc < c && arr[nr][nc] != '#') {
				
			} else {
				nr = rr;
				nc = cc;
			}

			if(ndst < dist[nr][nc][com+1]) {
				dist[nr][nc][com+1] = ndst;
				q.push_front((data){nr, nc, com+1, ndst});
			}
		}

		for(int i = 0 ; i < 4 ; i++) {
			pii add = translate(ch[i]);
			int nr = rr + add.first;
			int nc = cc + add.second;
			int ndst = dst+1;

			if(nr >= 0 && nr < r && nc >= 0 && nc < c && arr[nr][nc] != '#') {
				
			} else {
				nr = rr;
				nc = cc;
			}

			if(ndst < dist[nr][nc][com]) {
				dist[nr][nc][com] = ndst;
				q.push_back((data){nr, nc, com, ndst});
			}
		}
	}
}

int main() {
	read();
	cout << solve() << endl;
	return 0;
}