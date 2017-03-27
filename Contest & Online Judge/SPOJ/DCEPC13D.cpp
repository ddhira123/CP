#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

// dari sini, copas Carizad

LL mod(LL a,LL b) {
	a %= b;
	a = (a + b) % b;
	return a % b;
}

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

pair<LL,LL> chinese_remainder_theorem(LL x, LL a, LL y, LL b) {
	LL s, t;
	LL d = extended_euclid(x, y, s, t);
	//printf("%lld %lld %lld %lld %lld\n",x,a,y,b,d);
	if (a%d != b%d) return make_pair(0, -1);
	LL md = x*y;
	LL res = (s*b) % md;
	res = (res * x) % md;
	LL res2 = (t*a) % md;
	res2 = (res2 * y) % md;
	return make_pair(mod(res+res2,md)/d, x*y/d);
}


pair<LL,LL> chinese_remainder_theorem(vector<LL> &x, vector<LL> &a) {
	pair<LL,LL> ret = make_pair(x[0], a[0]);
	//cerr << ret.first << " " << ret.second << endl;
	for (LL i = 1; i < x.size(); i++) {
		ret = chinese_remainder_theorem(ret.first, ret.second, x[i],a[i]);
		swap(ret.first,ret.second);
		//cerr << ret.first << " " << ret.second << endl;
		if (ret.second == -1) break;
	}
	return ret;
}

// end copasan

// mulai lucas theorem

int modPow(int base,int po,int mod) {
	int ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % mod;
		base = (base * base) % mod;
		po >>= 1;
	}
	return ret;
}

int getFactorial(int n,int mod) {
	int ret = 1;
	for(int i = 1 ; i <= n ; i++) {
		ret = (ret * i) % mod;
	}
	return ret;
}

int getInverse(int n,int mod) {
	return modPow(getFactorial(n,mod),mod - 2,mod);
}

int getCombination(int n,int k,int mod) {
	if(k > n) return 0;
	int ret = getFactorial(n,mod);
	ret = (ret * getInverse(k,mod)) % mod;
	ret = (ret * getInverse(n-k,mod)) % mod;
	return ret;
}

int lucasCombination(int n,int k,int mod) {
	int ret = 1;
	while(n > 0 || k > 0) {
		ret = (ret * getCombination(n % mod,k % mod,mod)) % mod;
		n /= mod;
		k /= mod;
	}
	return ret;
}

// end lucas theorem

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int n,r,m;
		scanf("%d %d %d",&n,&r,&m);
		vector<LL> x, a;

		if(m == 1) {
			printf("0\n");
		}	
		else {
			int orim = m;
			for(int i = 2 ; i <= 50 ; i++)
				if(m % i == 0) {
					x.push_back(i);
					m /= i;
					if(m%i == 0) assert(0);
					a.push_back(lucasCombination(n,r,i));
				}
			assert(m == 1);	
			//for(int j = 0 ; j < x.size() ; j++)
			//	cout << x[j] << " " << a[j] << endl;	
			pair<LL,LL> ret = chinese_remainder_theorem(x,a);
			//cout << ret.first << " " << ret.second << endl;
			//assert(ret.first != -1);
			assert(ret.first == orim);
			ret.second %= ret.first;
			ret.second = (ret.second + ret.first) % ret.first;
			printf("%lld\n",ret.second);
		}
	}
	return 0;
}