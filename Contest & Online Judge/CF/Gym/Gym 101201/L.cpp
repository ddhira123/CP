#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

#define fi first
#define se second

int cross(pii p, pii q, pii r) {
	int dx1 = q.fi - p.fi;
	int dy1 = q.se - p.se;

	int dx2 = r.fi - p.fi;
	int dy2 = r.se - p.se;

	return dx1 * dy2 - dx2 * dy1;
}

int sqr(int x) {
	return x * x;
}

int jarak(pii a,pii b) {
	return sqr(a.fi-b.fi) + sqr(a.se-b.se);
}

pii pvt;

bool cmp(pii a,pii b) {
	if(cross(pvt, a, b) == 0) {
		return jarak(pvt, a) <= jarak(pvt, b);
	}
	return cross(pvt, a, b) > 0;
}

vector<pii> convexHull(vector<pii> v) {
	pvt = v[0];
	sort(v.begin()+1, v.end(), cmp);

	vector<pii> ret;
	for(pii x : v) {
		while(ret.size() > 1 && cross(ret[ret.size()-2], ret.back(), x) <= 0) {
			ret.pop_back();
		}
		ret.push_back(x);
	}

	return ret;
}

vector<pii> arr;
int n;
string s;

map<pii, int> idx;

void read() {
	cin >> n;
	for(int i = 0 ; i < n ; i++) {
		pii x;
		cin >> x.fi >> x.se;

		idx[x] = i+1;
		arr.push_back(x);
	}

	cin >> s;
}

void solve() {
	sort(arr.begin(), arr.end());
	pii lst = arr[0];
	printf("%d ", idx[arr[0]]);

	for(int i = 0 ; i < s.length() ; i++) {
		vector<pii> now = convexHull(arr);
		// for(pii x : now)
			// printf("%d %d\n", x.fi, x.se);
		// puts("-------");
		int pake = 1;
		if(s[i] == 'L') {
			pake = 1;
		} else {
			pake = now.size()-1;
		}

		pii used = now[pake];
		printf("%d ", idx[used]);

		for(int j = 0 ; j < arr.size() ; j++)
			if(arr[j] == used) {
				swap(arr[0], arr[j]);
				// printf("tt %d %d %d %d\n", arr[0].fi, arr[0].se, arr[j].fi, arr[j].se);
				arr.erase(arr.begin() + j);
				break;
			}
	}
	
	printf("%d\n", idx[arr[1]]);
}

int main() {
	read();
	solve();
	return 0;
}