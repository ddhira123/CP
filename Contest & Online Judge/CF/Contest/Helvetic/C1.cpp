#include <bits/stdc++.h>
using namespace std;

int pset[1005];
int n, m;

int finds(int x) {
	return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

bool same(int x,int y) {
	return finds(x) == finds(y);
}

void join(int x,int y) {
	x = finds(x);
	y = finds(y);
	pset[y] += pset[x];
	pset[x] = y;
}

void init() {
	for(int i = 1 ; i <= 1000 ; i++)
		pset[i] = -1;
}

int main() {
	init();
	cin >> n >> m;
	bool ok = 1;
	for(int i = 0 ; i < m && ok ; i++) {
		int a, b;
		cin >> a >> b;
		if(same(a,b))
			ok = 0;
		else 
			join(a,b);
	}
	ok &= (pset[finds(1)] == -n);
	if(ok) cout << "yes" << endl;
	else cout << "no" << endl;
	return 0;
}