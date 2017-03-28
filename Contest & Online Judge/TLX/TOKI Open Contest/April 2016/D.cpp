#include <bits/stdc++.h>
using namespace std;

int arr[2005];
int n;

bool isEven() {
	return n <= 2000 && n % 2 == 0;
}

bool isSorted() {
	if(n > 2000) return 0;
	bool ret = 0;
	for(int i = 1 ; i <= 2 ; i++) {
		bool yes = 1;

		for(int j = 2 ; j <= n ; j++)
			yes &= (arr[j] >= arr[j - 1]);

		ret |= yes;
		for(int j = 1 ; j <= n ; j++)
			arr[j] = -arr[j];
	}
	return ret;
}

long long pwr2(long long x) {
	return x * x;
}

bool hasPythagoras() {
	if(n > 2000) return 0;
	map<long long,int> s;
	for(int i = 1 ; i <= n ; i++)
		s[pwr2(arr[i])]++;
	for(int i = 1 ; i <= n ; i++)
		for(int j = i + 1 ; j <= n ; j++) {
			// apakah pythagoras boleh pake 0?
			// jeng jeng
			// boleh. kampret yang bikin
			if(arr[i] == 0 || arr[j] == 0) {
				if(arr[i] == arr[j] && s[0] >= 3) return 1;
				if(arr[i] == 0 && arr[j] != 0 && s[pwr2(arr[j])] >= 2) return 1;
				if(arr[j] == 0 && arr[i] != 0 && s[pwr2(arr[i])] >= 2) return 1;
				continue;
			}
			long long haha = pwr2(arr[i]) + pwr2(arr[j]);
			if(s.count(haha)) return 1;
		}
	return 0;	
}

int gcd(int a,int b) {
	return b == 0 ? a : gcd(b,a % b);
}

bool hasSolution() {
	if(n > 200) return 0;
	int fpb = arr[1];
	for(int i = 2 ; i <= n ; i++)
		fpb = gcd(arr[i],fpb);
	if(fpb == 0 || 999999999 % fpb != 0)
		return 0;
	return 1;
}

int main() {
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
		cin >> arr[i];
	// ayaz sangat cerdas
	if(isEven() || isSorted() || hasPythagoras() ||hasSolution())
		cout << -1 << endl;
	else {
		int ans = 0;
		for(int i = 1 ; i <= n ; i++) ans += arr[i];
		cout << ans << endl;
	}
	return 0;
}