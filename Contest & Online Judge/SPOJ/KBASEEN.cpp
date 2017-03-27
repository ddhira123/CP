#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL n,k,mod;

LL mul(LL a,LL b) {
	LL ret = 0;
	while(b) {
		if(b & 1)  {
			ret += a;
			if(ret >= mod) ret -= mod;
		}
		a <<= 1;
		if(a >= mod) a -= mod;
		b >>= 1;
	}
	return ret;
}

struct Matrix{
	LL mat[2][2];

	Matrix() {
		memset(mat,0,sizeof mat);
	}

	Matrix operator *(Matrix other) const {
		Matrix res;

		for(int i = 0 ; i < 2 ; i++)
			for(int j = 0 ; j < 2 ; j++)
				for(int k = 0 ; k < 2 ; k++) {
					res.mat[i][j] += mul(mat[i][k],other.mat[k][j]);
					if(res.mat[i][j] >= mod) res.mat[i][j] -= mod;
				}

		return res;		
	}

	Matrix operator ^(LL pwr) const {
		Matrix base;
		Matrix ret;

		for(int i = 0 ; i < 2 ; i++) {
			ret.mat[i][i] = 1;
			for(int j = 0 ; j < 2 ; j++)
				base.mat[i][j] = mat[i][j];
		}

		while(pwr) {
			if(pwr & 1) {
				ret = ret * base;
			}

			base = base * base;
			pwr >>= 1;
		}

		return ret;
	}
};

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t; tc++) {
		scanf("%lld %lld %lld",&n,&k,&mod);

		Matrix ans;
		ans.mat[0][0] = ans.mat[0][1] = (k - 1) % mod;
		ans.mat[1][0] = 1 % mod;

		ans = ans^(n - 1);

		LL res = 0;
		if(n == 1) {
			res = k % mod;
		}
		else {
			//printf("%lld %lld %lld\n",ans.mat[0][0],ans.mat[0][1],k - 1);
			res = mul(ans.mat[0][0],k - 1) + mul(ans.mat[0][1],1);
			res %= mod;
		}

		printf("%lld\n",res);
	}
	return 0;
}