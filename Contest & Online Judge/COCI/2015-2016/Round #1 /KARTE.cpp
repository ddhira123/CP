#include <bits/stdc++.h>
using namespace std;

int ID(char x){
	if(x == 'P')
		return 0;
	if(x == 'K')
		return 1;
	if(x == 'H')
		return 2;
	return 3;			
}

set<int> ada[4];

int main(){
	string s; cin >> s;
	for(int i = 0 ; i < s.length() ; i += 3){
		int idx = ID(s[i]);
		int val = 10 * (s[i + 1] - '0') + (s[i + 2] - '0');
		if(ada[idx].count(val)) {
			cout << "GRESKA" << endl;
			return 0;
		}
		ada[idx].insert(val);
	}
	for(int i = 0 ; i < 4 ; i++){
		cout << 13 - ada[i].size();
		if(i == 3) cout << "\n";
		else cout << " ";
	}
	return 0;
}
