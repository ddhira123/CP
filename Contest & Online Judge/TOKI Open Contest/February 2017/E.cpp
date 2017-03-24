#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1e5 + 5;
const LL MOD = 1e9 + 7;

LL extended_euclid(LL a, LL b, LL &x, LL &y) {
	LL xx = y = 0;
	LL yy = x = 1;
	while (b) {
		LL q = a/b;
		LL t = b; b = a%b; a = t;
		t = xx; xx = x-q*xx; x = t;
		t = yy; yy = y-q*yy; y = t;
	}
	return a;
}

int n;
LL arr[N];
LL A[N];
LL B[N];

LL inveA[N];
LL inveB[N];

LL getVal(int idx, LL a, LL b) {
	LL ret = a * A[idx] % MOD;
	ret = (ret + b * B[idx]) % MOD;
	ret = (ret + MOD) % MOD;
	return ret;
}

LL getInverseVal(int idx, LL a, LL b) {
	//printf("idx %d iA %lld iB %lld a %lld b %lld\n", idx, inveA[idx], inveB[idx], a, b);
	LL ret = a * inveA[idx] % MOD;
	ret = (ret + b * inveB[idx]) % MOD;
	ret = (ret + MOD) % MOD;
	return ret;
}

void init() {
	A[1] = 1;
	B[1] = 0;
	A[2] = 0;
	B[2] = 1;

	inveA[1] = 1;
	inveB[1] = 0;
	inveA[2] = 0;
	inveB[2] = 1;

	for(int i = 3 ; i < N ; i++) {
		A[i] = (A[i-1] + A[i-2]) % MOD;
		B[i] = (B[i-1] + B[i-2]) % MOD; 

		inveA[i] = (inveA[i-2] - inveA[i-1] + MOD) % MOD;
		inveB[i] = (inveB[i-2] - inveB[i-1] + MOD) % MOD;
	}
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%lld",arr + i);
}

void solve() {
	LL sumA = 0;
	LL sumB = 0;

	vector<LL> ansA, ansB, ansC;

	// for(int i = n ; i > 2 ; i--){
	// 	LL val = (arr[i] - (sumA * A[i] % MOD) - (sumB * B[i] % MOD)) % MOD;
	// 	val = (val + MOD) % MOD;
	// 	if(val != 0) {
	// 		LL x, y;
	// 		extended_euclid(A[i], B[i], x, y);
	// 		//printf("A %lld b %lld x %lld y %lld ret %lld\n", A[i], B[i], x, y, A[i] * x + B[i] * y);

	// 		x = (x * val) % MOD;
	// 		x = (x + MOD) % MOD;

	// 		y = (y * val) % MOD;
	// 		y = (y + MOD) % MOD;

	// 		ansA.push_back(x);
	// 		ansB.push_back(y);
	// 		ansC.push_back(i);

	// 		sumA = (sumA + x) % MOD;
	// 		sumB = (sumB + y) % MOD;
	// 	}
	// }

	for(int i = n ; i > 2 ; i--) {
		LL val = (arr[i] - getVal(i, sumA, sumB)) % MOD;
		val = (val + MOD) % MOD;
		LL valBef = (arr[i-1] - getVal(i-1, sumA, sumB)) % MOD;
		valBef = (valBef + MOD) % MOD;

		if(val != 0) {
			LL a = getInverseVal(i, val, valBef);
			LL b = getInverseVal(i-1, val, valBef);

			ansA.push_back(a);
			ansB.push_back(b);
			ansC.push_back(i);

			sumA = (sumA + a) % MOD;
			sumB = (sumB + b) % MOD;
		}
	}

	LL a = (arr[1] - sumA) % MOD;
	a = (a + MOD) % MOD;
	LL b = (arr[2] - sumB) % MOD;
	b = (b + MOD) % MOD;

	if(a != 0 || (b != 0 && n >= 2)) {
		ansA.push_back(a);
		ansB.push_back(b);
		ansC.push_back(min(n, 2));
	}

	printf("%d\n",(int)ansA.size());
	for(int i = 0 ; i < ansA.size() ; i++) {
		printf("%lld %lld %lld\n", ansA[i], ansB[i], ansC[i]);
	}

	// // tes
	// vector<LL> tes(n+1, 0);
	// for(int i = 0 ; i < ansA.size() ; i++) {
	// 	LL a = ansA[i];
	// 	LL b = ansB[i];
	// 	LL c = ansC[i];

	// 	tes[1] = (tes[1] + a) % MOD;
	// 	if(c >= 2) tes[2] = (tes[2] + b) % MOD;

	// 	for(int j = 3 ; j <= c ; j++) {
	// 		b = a+b;
	// 		a = b-a;
	// 		tes[j] = (tes[j] + b) % MOD;
	// 	}
	// }

	// for(int i = 1 ; i <= n ; i++) cout << tes[i] << " ";
}

int main() {
	init();
	read();
	solve();
	return 0;
}