#include <bits/stdc++.h>
using namespace std;

typedef pair<double, long long> pdl;

const int N = 15;

int n;
double p[4];
int use[4];
long long fak[N+5];
priority_queue<pdl, vector<pdl>, greater<pdl>> pq;

void precompute() {
	fak[0] = 1;
	for(int i = 1 ; i <= N ; i++)
		fak[i] = fak[i-1] * i;
}

void rec(int now, int udah, double probs) {
	if(now == 3) {
		use[3] = n - udah;
		for(int i = 0 ; i < use[3] ; i++)
			probs *= p[3];

		long long ways = 1;
		int mx = max(use[0], use[1]);
		mx = max(mx, use[2]);
		mx = max(mx, use[3]);

		for(int i = n ; i > mx ; i--)
			ways *= i;

		int temp[4];
		for(int i = 0 ; i < 4 ; i++)
			temp[i] = use[i];

		for(int i = 0 ; i < 4 ; i++)
			if(use[i] == mx) {
				temp[i] = 0;
				break;
			}

		for(int i = 0 ; i < 4 ; i++)
			ways /= fak[temp[i]];

		pq.push({probs, ways});
	} else {
		double tempP = probs;
		for(int i = 0 ; i <= n-udah ; i++) {
			use[now] = i;
			rec(now+1, udah+i, tempP);
			tempP *= p[now];
		}
	}
}

double solve() {
	rec(0, 0, 1);

	double ret = 0;
	while(1) {
		pdl cur = pq.top();
		pq.pop();

		// printf("%.9lf\n", cur.first);

		long long occ = cur.second;
		double expected = cur.first;

		if(occ / 2 > 0) {
			ret += 2 * expected * (occ / 2);
			pq.push({2 * expected, occ / 2});
			occ %= 2;
		}

		if(occ == 1) {
			if(pq.empty()) {
				break;
			}

			pdl lol = pq.top();
			pq.pop();

			lol.second--;

			ret += (lol.first + expected);

			if(lol.second > 0) {
				pq.push(lol);
			}

			pq.push({lol.first + expected, 1});
		}
	}

	return ret;
}

int main() {
	precompute();

	cin >> n;
	for(int i = 0 ; i < 4 ; i++)
		cin >> p[i];

	printf("%.10lf\n", solve());
	return 0;
}