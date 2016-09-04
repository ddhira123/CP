#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int MOD = 1e6 + 3;


struct matrix {
	long long mat[N][N];
	int sz;

	matrix(int _sz) {
		sz = _sz;
		memset(mat,0,sizeof mat);
	}

	matrix operator *(matrix other) const {
		matrix ret = matrix(sz);
		for(int i = 0 ; i < sz ; i++)
			for(int j = 0 ; j < sz ; j++)
				for(int k = 0 ; k < sz ; k++)
					ret.mat[i][j] = (ret.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
		return ret;
	}

	matrix operator ^(int po) const {
		matrix ret = matrix(sz);
		matrix base = matrix(sz);

		for(int i = 0 ; i < sz ; i++) {
			ret.mat[i][i] = 1;
			for(int j = 0 ; j < sz ; j++)
				base.mat[i][j] = mat[i][j];
		}

		while(po) {
			if(po & 1) ret = ret * base;
			base = base * base;
			po >>= 1;
		}

		return ret;
	}
}; 

int main() {
	int c, w, h;
	cin >> c >> w >> h;
	matrix res = matrix(w+1);
	for(int i = 0 ; i <= w ; i++)
		res.mat[0][i] = 1;
	for(int i = 1 ; i <= w ; i++)
		res.mat[i][i-1] = h;
	res = res^(c);
	long long ans = 0;
	for(int i = 0 ; i <= w ; i++) {
		ans = (ans + res.mat[i][0]) % MOD;
	}
	cout << ans << endl;
	return 0;
}