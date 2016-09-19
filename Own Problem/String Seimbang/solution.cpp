#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int cnt[3 * N];
string str;
int n;

long long solve() {
	long long ret = 0;
	int total = N;
	cnt[total] = 1;

	for(int i = 0 ; i < str.length() ; i++)
		if(str[i] == '(') {
			total++;
			cnt[total] = 1;
		}
		else {
			total--;
			ret += cnt[total];
			cnt[total]++;
		}

	return ret;	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	cin >> n;
	cin >> str;
	cout << solve() << endl;
	return 0;
}