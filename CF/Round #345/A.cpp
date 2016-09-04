#include <bits/stdc++.h>
using namespace std;

map<pair<int,int>,int > titik;
map<int,int> X;
map<int,int> Y;

long long C(long long x) {
	return x * (x - 1) / 2;
}

int main() {
	int n; scanf("%d",&n);
	for(int i = 0 ; i < n ; i++) {
		int x,y;
		scanf("%d %d",&x,&y);
		titik[{x,y}]++;
		X[x]++;
		Y[y]++;
	}

	long long ret = 0;
	for(auto it = X.begin(); it != X.end() ; it++) {
		ret += C(it -> second);
	}
	for(auto it = Y.begin(); it != Y.end() ; it++) {
		ret += C(it -> second);
	}	
	for(auto it = titik.begin(); it != titik.end() ; it++) {
		ret -= C(it -> second);
	}
	cout << ret << endl;	
	return 0;
}