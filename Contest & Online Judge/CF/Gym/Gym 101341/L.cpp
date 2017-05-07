// WA
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

struct data {
	long long a;
	long long b;
	int idx;

	bool operator <(data other) const {
		if(b-a == other.b-other.a) {
			return b > other.b;
		}
		return b-a > other.b-other.a;
	}
};

int l[N], r[N];
int x[N];
int ans[N];
vector<pair<int,int>> proc;
priority_queue<data> pq;
pair<pair<int,int>, int> magic[N];
int n, m;

void read() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d %d", l + i, r + i);
	scanf("%d", &m);
	for(int i = 1 ; i <= m ; i++)
		scanf("%d", x + i);
}

void preprocess() {
	int maxL = -1;
	int bestL = -1;
	int maxR = -1;
	int bestR = -1;

	for(int i = 1 ; i <= n ; i++) {
		magic[i].first = {l[i], r[i]};
		magic[i].second = i;

		if(l[i] > maxL) {
			maxL = l[i];
			bestL = i;
		}
		if(r[i] > maxR) {
			maxR = r[i];
			bestR = i;
		}
	}

	for(int i = 1 ; i <= m ; i++) {
		if(maxL >= x[i]) {
			ans[i] = bestL;
		} else if(maxR < x[i]) {
			ans[i] = bestR;
		} else {
			proc.push_back({x[i], i});
		}
	}

	sort(magic+1, magic+n+1);
	sort(proc.begin(), proc.end());
}

void solve() {
	int pqsz = 0;
	int i = 1;
	for(pair<int,int> monster : proc) {
		while(i <= n && monster.first >= magic[i].first.first) {
			data dat = (data){magic[i].first.first, magic[i].first.second, magic[i].second};
			pq.push(dat);
			pqsz++;
			i++;
		}

		while(pq.top().b < monster.first) {
			pq.pop();
			pqsz--;
		}

		long long xx = monster.first;
		// printf("%lld\n", xx);
		while(pqsz > 1) {
			data a = pq.top(); pq.pop();
			data b = pq.top(); pq.pop();

			if(a.b < monster.first) {
				pq.push(b);
				pqsz--;
				continue;
			}
			if(b.b < monster.first) {
				pq.push(a);
				pqsz--;
				continue;
			}

			long long withA = (a.b - xx) * (b.b - b.a);
			long long withB = (b.b - xx) * (a.b - a.a);

			// printf("xx %lld idx %d a idx %d witha %lld b idx %d withb %lld\n", xx, monster.second, a.idx, withA, b.idx, withB);

			if(withA >= withB) {
				pq.push(a);
				pq.push(b);
				break;
			} else {
				pq.push(b);
				pqsz--;
			}
		}

		assert(pqsz > 0);
		ans[monster.second] = pq.top().idx;
	}

	for(int i = 1 ; i <= m ; i++)
		printf("%d ", ans[i]);
	puts("");
}

int main() {
	read();
	preprocess();
	solve();
	return 0;
}
