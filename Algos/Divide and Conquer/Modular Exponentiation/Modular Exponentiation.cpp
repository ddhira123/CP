/**
	Modular Exponentiation

	We have recursive and iterative version for modexpo.

	For recursive, we have f(base,po,mod):
		- po = 0, 1 % mod. Remember that base^0 = 1 % mod
		- po % 2 = 1, base * f(base,po-1,mod) % mod
		- po % 2 = 0, we have (f(base,po/2,mod))^2 % mod. Save f(base,po/2,mod) in one variable.

	For iterative, write po in base 2 form. Calculate base^(2^0), base^(2^1), base^(2^2), ...
	Suppose po in base 2 form is p_k p_(k-1) ... p_0. Then, base^po can be calculated as 
	sum{i=0 -> k}{base^i * p_i}
	base^ can be calculated on the fly	
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL recursiveModularExponentiation(LL base,LL po,LL mod) {
	if(po == 0) return 1 % mod;
	if(po % 2 == 1) return base * recursiveModularExponentiation(base,po-1,mod) % mod;
	LL temp = recursiveModularExponentiation(base,po / 2,mod);
	return temp * temp % mod;
}

LL iterativeModularExponentiation(LL base,LL po,LL mod) {
	LL ret = 1 % mod;
	while(po > 0) {
		if(po % 2 == 1) ret = ret * base % mod;
		base = base * base % mod;
		po >>= 1;
	}
	return ret;
}

int main() {
	return 0;
}