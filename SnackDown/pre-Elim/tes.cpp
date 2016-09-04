#include <bits/stdc++.h>
using namespace std;

int main() {
	int start, n, m;
	cin >> start >> n >> m;
	vector<int> v(n,0);
	v[start] = 1;
	for(int i = 0 ; i < m ; i++) {
		vector<int> ret;
		for(int j = 0 ; j < v.size() ; j++) {
			ret.push_back(v[j]);
			if(j + 1 < v.size()) ret.push_back(v[j] + v[j+1]);
		}
		v = ret;
	}
	for(int x : v) printf("%d ",x);
	puts("");
	return 0;
}