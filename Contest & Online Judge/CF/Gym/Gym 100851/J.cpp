#include <bits/stdc++.h>
using namespace std;

string getRandom(int n) {
	string ret = "";
	for(int i = 0 ; i < n ; i++)
		ret += (char)(rand() % 2 + '0');
	return ret;
}

char flip(char x) {
	return x == '0' ? '1' : '0';
}

vector<int> group[2];

int main() {
	int n; cin >> n;
	int ret = 0;

	string s = "";
	while(ret == 0) {
		s = getRandom(n);
		cout << s << endl;
		cin >> ret;
	}

	if(ret == n) {
		return 0;
	}

	group[0].push_back(0);

	for(int i = 1 ; i < n ; i++) {
		string tmp = s;
		tmp[0] = flip(tmp[0]);
		tmp[i] = flip(tmp[i]);

		cout << tmp << endl;
		int haha; cin >> haha;

		if(haha == n) {
			return 0;
		} else if(haha == n/2) {
			group[1].push_back(i);
		} else {
			group[0].push_back(i);
		}
	}

	for(int i = 0 ; i < 2 ; i++) {
		string tmp = s;
		for(int x : group[i])
			tmp[x] = flip(tmp[x]);

		cout << tmp << endl;
		int haha ; cin >> haha;

		if(haha == n) {
			return 0;
		}
	}

	assert(0);
	
	return 0;
}