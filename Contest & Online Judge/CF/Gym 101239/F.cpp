#include <bits/stdc++.h>
using namespace std;

const int N = 52;
const int MX = 1e4 + 2;

struct data {
	int pos;
	int r;
	int c;
};

string arr[N];
string s;
int dist[MX][N][N];
int r, c;

int atas[N][N], bawah[N][N], kiri[N][N], kanan[N][N];

void read() {
	cin >> r >> c;
	for(int i = 0 ; i < r ; i++)
		cin >> arr[i];
	cin >> s;

	// for(int i = 0 ; i < r ; i++)
		// cout << arr[i] << endl;
}

void prepare() {
	s += "*";
	// kiri kanan
	for(int i = 0 ; i < r ; i++) {
		for(int j = 0; j < c; ) {
			int k = j;
			while(k < c && arr[i][j] == arr[i][k]) k++;

			for(int it = j ; it < k ; it++) {
				kiri[i][it] = j-1;
				kanan[i][it] = k;
			}

			j = k;
		}
	}
	// atas bawah
	for(int j = 0 ; j < c ; j++) {
		for(int i = 0 ; i < r ; ) {
			int k = i;
			while(k < r && arr[i][j] == arr[k][j]) k++;

			for(int it = i ; it < k ; it++) {
				atas[it][j] = i-1;
				bawah[it][j] = k;
			}

			i = k;
		}
	}

	// for(int i = 0 ; i < r ; i++)
	// 	for(int j = 0 ; j < c ; j++) {
	// 		printf("%d %d: %d %d %d %d\n", i, j, kiri[i][j], kanan[i][j], atas[i][j], bawah[i][j]);
	// 	}

	for(int i = 0 ; i < MX ; i++)
		for(int j = 0 ; j < N ; j++)
			for(int k = 0 ; k < N ; k++)
				dist[i][j][k] = -1;
}

int bfs() {
	queue<data> q;

	dist[0][0][0] = 0;
	q.push((data){0, 0, 0});

	while(!q.empty()) {
		data now = q.front();
		q.pop();

		int rr = now.r;
		int cc = now.c;
		int pos = now.pos;
		int ndis = dist[pos][rr][cc];

		// printf("%d %d %d\n", rr, cc, pos);

		if(pos == s.length()) {
			return dist[pos][rr][cc];
		}

		if(s[pos] == arr[rr][cc]) {
			int &nex = dist[pos+1][rr][cc];
			if(nex == -1) {
				nex = ndis + 1;
				q.push((data){pos+1, rr, cc});
			}
		}

		if(kiri[rr][cc] >= 0) {
			int nc = kiri[rr][cc];
			int &nex = dist[pos][rr][nc];
			if(nex == -1) {
				nex = ndis + 1;
				q.push((data){pos, rr, nc});
			}
		}

		if(kanan[rr][cc] < c) {
			int nc = kanan[rr][cc];
			int &nex = dist[pos][rr][nc];
			if(nex == -1) {
				nex = ndis + 1;
				q.push((data){pos, rr, nc});
			}
		}

		if(atas[rr][cc] >= 0) {
			int nr = atas[rr][cc];
			int &nex = dist[pos][nr][cc];
			if(nex == -1) {
				nex = ndis + 1;
				q.push((data){pos, nr, cc});
			}
		}

		if(bawah[rr][cc] < r) {
			int nr = bawah[rr][cc];
			int &nex = dist[pos][nr][cc];
			if(nex == -1) {
				nex = ndis + 1;
				q.push((data){pos, nr, cc});
			}
		}
	}

	assert(0);
}

int main() {
	read();
	prepare();
	cout << bfs() << endl;
	return 0;
}