#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 0 ; tc < t ; tc++) {
		vector<string> v;
		for(int i = 0 ; i < 10 ; i++) {
			string x; cin >> x;
			v.push_back(x);
		}
		string s = "";
		int a,b;
		for(int i = 0 ; i < 10 ; i++)
			for(int j = 0 ; j < 10 ; j++)
				if(i != j) {
					for(int en = 0 ; en < 4 ; en++) {
						bool ok = 1;
						for(int k = 0 ; k + en < 4 ; k++)
							if(v[i][en+k] != v[j][k])
								ok = 0;
						if(ok) {
							a = i;
							b = j;
							for(int k = 0 ; k < en ; k++)
								s += v[i][k];
							for(int k = 0 ; k < 4 ; k++)
								s += v[j][k];
							goto hell;
						}	
					}
				}
		hell:
		assert(s != "");
		for(int i = 0 ; i < 10 ; i++)
			if(i != a && i != b)
				s += v[i];
		while(s.length() < 39) s += "A";
		cout << s << endl;	
	}
	return 0;
}