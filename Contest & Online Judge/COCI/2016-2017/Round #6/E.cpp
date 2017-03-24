// fail; totally wrong idea
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int, pii> tri;
const int MX = 1e7 + 5;
const int N = 1e5 + 5;

set<int> seen;
vector<int> haha[2 * N];
int pos[MX];
int pake[MX];
int nxt[MX];
int curPos;
int val[N];
int n;
vector<tri> elist;

int pset[N];

void init() {
	iota(pset, pset + N, 0);
}

int finds(int x) {
	return pset[x] == x ? x : pset[x] = finds(pset[x]);
}

void add(int x,int idx) {
	if(pos[x] == 0) {
		pos[x] = curPos;
		curPos = (curPos + 1);
		if(curPos == 2*N) 
			curPos = 1;
	}
	//cerr << "move " << x << " " << pos[x] << " " << idx << "\n";
	haha[pos[x]].push_back(idx);
}

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; i++) {
		int x; 
		scanf("%d", &x);
		//x = i;
		seen.insert(x);
	}

	int idx = 0;
	curPos = 1;
	for(int x : seen) {
		//printf("%d idx %d\n", x, idx);
		haha[curPos].push_back(idx);
		//cerr << "masuk " << x << " " << curPos << " " << idx << "\n";
		pos[x] = curPos++;
		val[idx++] = x;

		pake[x] = idx-1;
	}

	int lst = 0;
	init();

	for(int i = *(seen.begin()) ; i < MX ; i++) {
		if(pos[i] != 0) {
			//cerr << i << " " << pos[i] << "\n";
			int now = pos[i];
			if(val[haha[now][0]] == i) {
				if(haha[now].size() > 1) {
					for(int j = 1 ; j < haha[now].size() ; j++) {
						pset[finds(haha[now][j])] = finds(haha[now][0]);
					}
				} else {
					//cerr << lst << " " << pos[lst] << "\n";
					for(int x : haha[pos[lst]]) {
						//printf("add %d from %d %d\n", i-lst, haha[pos[lst]][0], x);
						elist.push_back({i - lst, {haha[now][0], x}});
					}
				}
			}

			for(int x : haha[now]) {
				if(i + val[x] < MX) {
					add(i + val[x], x);
				}
			}

			haha[pos[lst]].clear();
			lst = i;
		}
	}

	nxt[MX-1] = -1;
	for(int i = MX-2 ; i >= 0 ; i--) {
		if(pake[i]) {
			nxt[i] = i;
		} else {
			nxt[i] = nxt[i+1];
		}
	}

	for(int i = 0 ; i < idx ; i++) {
		int best = MX;
		vector<int> v;
		if(nxt[val[i]+1] != -1 && nxt[val[i]+1] < 2*val[i]) {
			best = nxt[val[i]+1] % val[i];
			v = {pake[nxt[val[i]+1]]};
		}
		for(int j = val[i] + val[i] ; j < MX ; j += val[i]) {
			if(nxt[j] == -1) {
				break;
			}
			if(nxt[j] >= j + val[i]) continue;

			int lol = nxt[j] % val[i];

			if(lol == best)
				v.push_back(pake[nxt[j]]);
			else if(lol < best) {
				v = {pake[nxt[j]]};
				best = lol;
			}
		}
		for(int x : v) {
			elist.push_back({best, {i, x}});
		}
	}

	sort(elist.begin(), elist.end());
	long long ret = 0;
	for(tri x : elist) {
		int cost = x.first;
		int a = x.second.first;
		int b = x.second.second;

		a = finds(a);
		b = finds(b);

		if(a != b) {
			ret += cost;
			pset[b] = a;
		}
	}

	printf("%lld\n", ret);
	return 0;
}