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

typedef long long LL;
const int N = 1e6 + 5;

long long C2(long long x) {
	return x * (x+1) / 2;
}

bool R[N];
bool C[N];
LL rActive;
LL cActive;
LL rSum;
LL cSum;
int n, q;

int main() {
	OPEN("adjustment");
	scanf("%d %d",&n,&q);
	for(int i = 0 ; i < q ; i++) {
		char s[5];
		long long x;

		scanf("%s %lld",s, &x);
		long long ret = 0;

		if(s[0] == 'R') {
			if(!R[x]) {
				ret = x * n + C2(n) - x * cActive - cSum; 
				R[x] = 1;
				rActive++;
				rSum += x;
			} 
		} else {
			if(!C[x]) {
				ret = x * n + C2(n) - x * rActive - rSum;
				C[x] = 1;
				cActive++;
				cSum += x;
			}
		}

		printf("%lld\n", ret);
	}
	CLOSE();
	return 0;
}