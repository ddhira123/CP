#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int M = 205;

struct Matrix {
	long long mat[M][M];
	int sz;

	Matrix(int _sz = 0) {
		memset(mat,0,sizeof mat);
		sz = _sz;
	}

	void setVal(int row,int col,long long val) {
		mat[row][col] = val;
	}

	long long getVal(int row,int col) {
		return mat[row][col];
	}

	Matrix operator *(Matrix other) const {
		Matrix res = Matrix(sz);

		for(int i = 0 ; i < sz ; i++)
			for(int j = 0 ; j < sz ; j++) {
				long long ret;
				ret = (long long)4e18;

				for(int k = 0 ; k < sz ; k++)
					ret = min(ret,mat[i][k] + other.mat[k][j]);

				res.setVal(i,j,ret);
			}

		return res;	
	}

	Matrix operator ^(int pwr) const {
		Matrix base = Matrix(sz);
		Matrix ret = Matrix(sz);

		for(int i = 0 ; i < sz ; i++)
			for(int j = 0 ; j < sz ; j++) {
				base.mat[i][j] = mat[i][j];
			}

		while(pwr) {
			if(pwr & 1) ret = ret * base;
			base = base * base;
			pwr >>= 1;
		}	

		return ret;
	}
};

int backTable[N];
int idxUsed;
char arr[M][N];
int len[M];
int n,m;

void makeBackTable(int idx) {
	idxUsed = idx;
	backTable[0] = -1;
	int i = 0, j = -1;
	while(i < len[idx]) {
		while(j != -1 && arr[idx][i] != arr[idx][j]) j = backTable[j];
		i++; j++;
		backTable[i] = j;
	}
}

int getLongestSuffix(int a,int b) {
	if(idxUsed != a) makeBackTable(a);
	int st = max(0,len[b] - len[a] + 1);
	int j = 0;

	while(st < len[b]) {
		while(j != -1 && arr[a][j] != arr[b][st]) j = backTable[j];
		st++; j++;
	}

	return len[a] - j;
}

int main() {
	scanf("%d %d",&n,&m);

	for(int i = 0 ; i < n ; i++) {
		scanf("%s",arr[i]);
		len[i] = strlen(arr[i]);
	}

	Matrix res = Matrix(n);
	idxUsed = -1;

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++) {
			int hasil = getLongestSuffix(i,j);
			//printf("%d\n",hasil);
			res.setVal(i,j,hasil);
		}

	res = res^(m - 1);
	long long ans = (long long)4e18;

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			ans = min(ans,res.getVal(i,j) + len[j]);

	printf("%lld\n",ans);			
	return 0;
}