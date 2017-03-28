#include <bits/stdc++.h>
using namespace std;

struct Node {
	int lazy;
	int mins;

	Node() {
		lazy = mins = 0;
	}

	Node operator +(Node other) const {
		Node ret;
		ret.mins = min(mins, other.mins);
		return ret;
	}

	void add(int val) {
		lazy += val;
		mins += val;
	}
};

struct Chunk {
	int id;
	int l;
	int r;
	int mins;

	void print() {
		printf("id: %d l: %d r: %d mins: %d\n", id, l, r, mins);
	}
};

struct Request {
	int l;
	int r;
	int val;

	void read() {
		scanf("%d %d %d", &l, &r, &val);
	}

	bool operator <(Request other) const {
		return val < other.val;
	}
};

const int N = 1e5 + 5;

int minRange[N];
int maxRange[N];
int ans[N];
int n, q;

vector<Request> requests;
Node stree[4*N];

void propagate(int id) {
	int chld = id << 1;
	int lazy = stree[id].lazy;

	for(int i = 0 ; i < 2 ; i++) {
		stree[chld + i].add(lazy);
	}

	stree[id].lazy = 0;
}

void update(int id, int l, int r, int x, int y, int add) {
	if(x <= l && r <= y) {
		stree[id].add(add);
	} else {
		int m = (l + r) / 2;
		int chld = id << 1;

		propagate(id);
		if(x <= m) 	update(chld, l, m, x, y, add);
		if(y > m)	update(chld+1, m+1, r, x, y, add);

		stree[id] = stree[chld] + stree[chld+1];
	}
}

void getChunks(int id, int l, int r, int x, int y, vector<Chunk> &chunks) {
	if(x <= l && r <= y) {
		int mins = stree[id].mins;
		Chunk chunk = (Chunk){id, l, r, mins};
		chunks.push_back(chunk);
	} else {
		int m = (l + r) / 2;
		int chld = id << 1;

		propagate(id);
		if(x <= m) 	getChunks(chld, l, m, x, y, chunks);
		if(y > m)	getChunks(chld+1, m+1, r, x, y, chunks);
	}
}

int getIndex(Chunk chunk) {
	int id = chunk.id;
	int l = chunk.l;
	int r = chunk.r;
	int mins = chunk.mins;

	while(l < r) {
		int m = (l + r) / 2;
		int chld = id << 1;

		propagate(id);
		if(stree[chld].mins == mins) {
			r = m;
			id = chld;
		} else {
			l = m+1;
			id = chld+1;
		}
	}

	return l;
}

void read() {
	scanf("%d %d", &n, &q);
	for(int i = 0 ; i < q ; i++) {
		Request request;
		request.read();

		requests.push_back(request);
	}
}

void prepare() {
	for(int i = 0 ; i < n ; i++) {
		minRange[i] = 0;
		maxRange[i] = N;
	}

	for(Request request : requests) {
		int l = request.l;
		int r = request.r;
		int val = request.val;

		update(1, 0, n-1, l, r, 1);
		minRange[val] = max(minRange[val], l);
		maxRange[val] = min(maxRange[val], r);
	}

	sort(requests.begin(), requests.end());
}

void fail() {
	for(int i = 0 ; i+1 < n ; i++)
		printf("-1 ");
	puts("-1");
	exit(0);
}

void solve() {
	int iter = 0;
	for(int i = 0 ; i < n ; i++) {
		while(iter < q && requests[iter].val <= i) {
			int l = requests[iter].l;
			int r = requests[iter].r;

			update(1, 0, n-1, l, r, -1);
			iter++;
		}

		if(maxRange[i] == N) {
			minRange[i] = 0;
			maxRange[i] = n-1;
		}
		// printf("%d %d %d\n", i, minRange[i], maxRange[i]);
		if(minRange[i] > maxRange[i]) {
			fail();
		}

		vector<Chunk> chunks;
		getChunks(1, 0, n-1, minRange[i], maxRange[i], chunks);

		bool exist = 0;
		for(Chunk chunk : chunks) {
			// chunk.print();
			if(chunk.mins == 0) {
				int pos = getIndex(chunk);

				ans[pos] = i;
				update(1, 0, n-1, pos, pos, N);
				// printf("put %d to %d\n", i, pos);
				exist = 1;
				break;
			}
		}

		if(!exist) {
			fail();
		}
	}

	for(int i = 0 ; i+1 < n ; i++)
		printf("%d ", ans[i]);
	printf("%d\n", ans[n-1]);
}

int main() {
	read();
	prepare();
	solve();
	return 0;
}