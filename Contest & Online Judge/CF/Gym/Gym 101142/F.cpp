#include <bits/stdc++.h>
using namespace std;

void OPEN(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
}

int solve(int a,int b) {
	int ret = 0;
	while(!(a >= b && b >= (a+1)/2)) {
		ret++;
		a = (a+1) / 2;
	}
	if(a > b) ret++;
	return ret;
}

int main() {
	OPEN("folding");
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	int ans;
	ans = 1000000000;
	if(a >= c && b >= d) ans = solve(a,c) + solve(b,d);
	if(a >= d && b >= c) ans = min(ans, solve(a,d) + solve(b,c));
	if(ans == 1000000000) ans = -1;
	cout << ans << "\n";
	CLOSE();
	return 0;
}