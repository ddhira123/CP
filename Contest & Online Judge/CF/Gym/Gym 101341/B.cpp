#include <bits/stdc++.h>
using namespace std;

string happy = "happiness";

string s;

int main() {
	cin >> s;
	vector<int> v;
	for(int i = 0 ; i +happy.length()-1 < s.length() ; i++) {
		if(s.substr(i, happy.length()) == happy)
			v.push_back(i+1);
	}

	if(v.size() == 2) {
		puts("YES");
		printf("%d %d\n", v[0]+1, v[1]+2);
	}
	else if(v.size() > 1) {
		puts("NO");
	} else if(v.size() == 1) {
		puts("YES");
		printf("%d %d\n", v[0], v[0]+1);
	} else {
		if(s.length() < happy.length()) {
			printf("YES\n%d %d\n", 1, 2);
			return 0;
		}

		for(int i = 0 ; i+1 < s.length() ; i++) {
			swap(s[i], s[i+1]);
			bool ok = 1;
			for(int j = max(0, i - (int)happy.length()+1) ; j <= min(i+1, (int)(s.length()-happy.length())) ; j++) {
				if(s.substr(j, happy.length()) == happy) {
					ok = 0;
					break;
				}
			}
			swap(s[i], s[i+1]);

			if(ok) {
				printf("YES\n");
				printf("%d %d\n", i+1, i+2);
				break;
			}
		}
	}
	return 0;
}