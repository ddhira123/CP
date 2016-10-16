#include <bits/stdc++.h>
using namespace std;

int n;
int arr[105];

int main() {
	cin >> n;
	for(int i = 0 ; i < n ; i++) cin >> arr[i];
	string s; getline(cin,s);
	bool ok = 1;
	for(int i = 0 ; i < n ; i++) {
		getline(cin,s);
		int chara = 0;
		for(char x : s)
			if(x == 'a' || x == 'i' || x == 'u' || x == 'e' || x == 'o' || x == 'y')
				chara++;

		stringstream ss;
		ss << s;
		string temp;
		int tot = 0;
		while(ss >> temp) {
			for(char x : temp)
				if(x == 'a' || x == 'i' || x == 'u' || x == 'e' || x == 'o' || x == 'y') {
					tot++;
					break;
				}
		}

		ok &= (arr[i] == chara);
	}

	if(ok) cout << "YES\n";
	else cout << "NO\n";
	return 0;
}