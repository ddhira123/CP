#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int MAGIC = 50;
const int MOD = 1e9+7;

int a[N][N];
int b[N][N];
int c[N][N];
int r[N];
int res[N][N];
bool udah[N][N];
int bVec[N];
int cVec[N];
int resVec[N];
int n;

void read() {
	scanf("%d", &n);

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++) {
			scanf("%d", &a[i][j]);
		}

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++) {
			scanf("%d", &b[i][j]);
		}

	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++) {
			scanf("%d", &c[i][j]);
		}
}

bool solve() {
	if(0) {
		for(int i = 0 ; i < n ; i++)
			for(int j = 0 ; j < n ; j++) {
				for(int k = 0 ; k < n ; k++)
					res[i][j] = (res[i][j] + 1ll * a[i][k] * b[k][j]) % MOD;
				if(res[i][j] != c[i][j]) {
					return false;
				}
			}
		return true;
	} else {
		for(int i = 0 ; i < MAGIC ; i++) {
			for(int j = 0 ; j < n ; j++)
				r[j] = rand() & 1;

			for(int j = 0 ; j < n ; j++) {
				bVec[j] = 0;
				for(int k = 0 ; k < n ; k++)
					bVec[j] = (bVec[j] + r[k] * b[j][k]) % MOD;
			}

			for(int j = 0 ; j < n ; j++) {
				cVec[j] = 0;
				for(int k = 0 ; k < n ; k++)
					cVec[j] = (cVec[j] + r[k] * c[j][k]) % MOD;
			}

			for(int j = 0 ; j < n ; j++) {
				resVec[j] = 0;
				for(int k = 0 ; k < n ; k++)
					resVec[j] = (resVec[j] + 1ll * bVec[k] * a[j][k]) % MOD;
				if(resVec[j] != cVec[j]) {
					return false;
				}
			}
		}
		return true;
	}
}

int main() {
	read();
	printf("%s\n", solve() ? "YES" : "NO");
	return 0;
}