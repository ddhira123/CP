#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

int dr[6] = {-1,-1,0,0,1,1};
int dc[6] = {-1,0,-1,1,0,1};
int dr2[6] = {-1,-1,0,0,1,1};
int dc2[6] = {-1,0,-1,1,-1,0};
int dr3[6] = {-1,-1,0,0,1,1};
int dc3[6] = {0,1,-1,1,-1,0};

const int INF = 1e9;

int arr[80][80];
int lens[80];
int dist[80][80][16];
int h;

bool read() {
	if(!(cin >> h)) return 0;
	if(h == 0) return 0;

	int len = h;
	int diff = 1;
	for(int i = 0 ; i < 2*h-1 ; i++) {
		for(int j = 0 ; j < len ; j++) {
			char x; cin >> x;
			//cout << x << " ";
			if(x == '.') arr[i][j] = -2;
			else arr[i][j] = x - 'A';
		}
		//cout << "\n";

		lens[i] = len;
		if(len + diff > 2*h-1) diff = -1;
		len += diff;
	}
}

int dijkstra() {
	for(int i = 0 ; i < 2*h-1 ; i++)
		for(int j = 0 ; j < lens[i] ; j++)
			for(int k = 0 ; k < 16 ; k++)
				dist[i][j][k] = INF;

	priority_queue<pair<pii,pii>> pq;

	for(int i = 0 ; i < 2*h-1 ; i++)
		for(int j = 0 ; j < lens[i] ; j++)
			if(arr[i][j] == -2) {
				dist[i][j][0] = 1;
				pq.push({{-1,0},{i,j}});
			}
			else {
				dist[i][j][1<<arr[i][j]] = 0;
				pq.push({{0,-(1<<arr[i][j])},{i,j}});
			}

	while(!pq.empty()) {
		pair<pii,pii> now = pq.top();
		pq.pop();

		int rr = now.se.fi;
		int cc = now.se.se;
		int bm = -now.fi.se;
		int dst = -now.fi.fi;

		//cout << dst << " " << rr << " " << cc << " " << bm << "\n";

		if(dst != dist[rr][cc][bm]) continue;

		for(int i = 0 ; i < 6 ; i++) {
			int transr, transc;
			if(rr == h-1) {
				transr = dr2[i];
				transc = dc2[i];
			}
			else if(rr < h-1) {
				transr = dr[i];
				transc = dc[i];
			}
			else {
				transr = dr3[i];
				transc = dc3[i];
			}
			int nr = rr + transr;
			int nc = cc + transc;

			//cout << nr << " " << nc << " " << lens[nr] << "\n";
			if(nr >= 0 && nr < 2*h-1 && nc >= 0 && nc < lens[nr]) {
				for(int msk = 0 ; msk < 16 ; msk++) {
					int ndis = dst + dist[nr][nc][msk];
					int nbm = bm | msk;

					if(ndis < dist[nr][nc][nbm]) {
						dist[nr][nc][nbm] = ndis;
						pq.push({{-ndis,-nbm},{nr,nc}});
					}
				}
			}
		}
	}	

	int mins = INF;
	for(int i = 0 ; i < 2*h-1 ; i++)
		for(int j = 0 ; j < lens[i] ; j++)
			mins = min(mins,dist[i][j][15]);

	return mins;			
}

int main() {
	while(read()) {
		cout << "You have to buy " << dijkstra() << " parcels.\n";
	}
	return 0;
}