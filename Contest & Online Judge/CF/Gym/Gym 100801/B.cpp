#include <bits/stdc++.h>
using namespace std;

void OPEN(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

void CLOSE() {
	fclose(stdin);
	fclose(stdout);
}

string ans[2005];

int main() {
	OPEN("black");
	int b, w;
	cin >> b >> w;

	for(int i = 0 ; i < b+w ; i++)
		for(int j = 0 ; j < 3 ; j++)
			ans[i] += (i & 1) ? "." : "@";

	int curB = (b + w + 1) / 2;
	for(int i = b+w-2 ; i >= 0 ; i--)
		if(b > curB && ans[i][0] == '@') {
			ans[i][1] = '.';	
			curB++;
		}
		else if(b < curB && ans[i][0] == '.') {
			ans[i][1] = '@';
			curB--;
		}

	cout << b+w << " " << 3 << "\n";
	for(int i = 0 ; i < b+w ; i++)
		cout << ans[i] << "\n";

	CLOSE();
	return 0;
}