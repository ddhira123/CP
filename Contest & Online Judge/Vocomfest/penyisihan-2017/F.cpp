#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL, LL> pll;

const int N = 1e4 + 5;

pll arr[N];
int n;
double nearest;
long long nearestDoubled;
set<pll> st;
pll ans;
LL r;

LL sqr(LL x) {
	return x * x;
}

LL getSquaredDistance(pll a, pll b) {
	return sqr(a.first - b.first) + sqr(a.second - b.second);
}

void fetch(pair<LL,LL> lol) {
	LL mins = lol.second - nearest - 1;

	auto it = st.lower_bound({mins, -1});

	while(it != st.end() && lol.second + nearest + 1 > (*it).first) {
		LL y = (*it).first;
		LL x = (*it).second;

		LL dst = getSquaredDistance({x, y}, lol);
		if(dst < nearestDoubled) {
			nearestDoubled = dst;
			nearest = sqrt(dst);

			ans = {x + lol.first, y + lol.second};
		} else if(dst == nearestDoubled) {
			pll temp = {x + lol.first, y + lol.second};

			ans = min(ans ,temp);
		}

		it++;
	}
}

void read() {
	scanf("%d %lld", &n, &r);
	for(int i = 0 ; i < n ; i++) {
		scanf("%lld %lld", &arr[i].first, &arr[i].second);
	}
}

pll solve() {
	sort(arr, arr + n);
	st.clear();

	nearestDoubled = 4e18;
	nearest = 4e18;

	int j = 0;
	for(int i = 0 ; i < n ; i++) {
		// printf("process %d\n", i);
		while(j < i && sqr(arr[j].first - arr[i].first) > nearestDoubled) {
			LL x = arr[j].first;
			LL y = arr[j].second;
			st.erase({y, x});

			j++;
		}

		fetch(arr[i]);
		// printf("%lld\n", nearestDoubled);

		st.insert({arr[i].second, arr[i].first});
	}

	return ans;
}

int main() {
	int t; cin >> t;

	for(int tc = 1 ; tc <= t ; tc++) {
		read();

		pll ret = solve();

		if(nearestDoubled <= sqr(2 * r)) {
			LL a = ret.first;
			LL b = ret.second;

			printf("Case #%d: %lld.%lld %lld.%lld\n", tc, a / 2, 5 * (a & 1), b / 2, 5 * (b & 1));
		} else {
			printf("Case #%d: -1\n", tc);
		}
	}
	return 0;
}