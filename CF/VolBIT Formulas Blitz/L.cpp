#include <bits/stdc++.h>
using namespace std;

int main() {
	char s[10]; scanf("%s",s);
	long long val = (s[1] - '0') + 10 * (s[3] - '0') + 100 * (s[4] - '0') + 1000 * (s[2] - '0') + 10000 * (s[0] - '0');
	long long mod = 100000;
	long long res = 1;
	for(int i = 0 ; i < 5 ; i++)
		res = (res * val) % mod;
	int ans =res;
	printf("%05d\n",ans);
	return 0;
}