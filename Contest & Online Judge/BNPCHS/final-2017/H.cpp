#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		long long a1, b1, x1;
		long long a2, b2, x2;

		cin >> a1 >> b1 >> x1;
		cin >> a2 >> b2 >> x2;

		long double mat[2][3];
		mat[0][0] = a1; mat[0][1] = b1; mat[0][2] = x1;
		mat[1][0] = a2; mat[1][1] = b2; mat[1][2] = x2;
		string ok = "Y";
		int lst = 0;

		for(int i = 0 ; i < 2 ; i++) {
			int pos = -1;
			for(int j = lst ; j < 2 ; j++)
				if(fabs(mat[j][i]) > 1e-12) {
					pos = j;
					break;
				}

			if(pos != -1) {
				for(int j = 0 ; j < 3 ; j++) {
					swap(mat[lst][j], mat[pos][j]);
				}
				long double val = mat[lst][i];
				for(int j = 0 ; j < 3 ; j++) {
					mat[lst][j] /= val;
				}
				for(int j = lst+1 ; j < 2 ; j++) {
					long double mul = mat[j][i];
					for(int k = 0 ; k < 3 ; k++) {
						mat[j][k] -= mul * mat[lst][k];
					}
				}
				lst++;
			}
		}

		for(int i = 1 ; i >= 0 ; i--) {
			int kiri = -1;
			for(int j = 1 ; j >= 0 ; j--)
				if(fabs(mat[i][j]) > 1e-12) {
					kiri = j;
				}
			if(kiri != -1) {
				for(int j = i-1 ; j >= 0 ; j--) {
					long double mul = mat[j][kiri];
					for(int k = kiri ; k < 3 ; k++) {
						mat[j][k] -= mul * mat[i][k];
					}
				}
			}
		}

		printf("Kasus #%d: ", tc);
		// for(int i = 0 ; i < 2 ; i++) {
		// 	for(int j = 0 ; j < 3 ; j++)
		// 		printf("%.5Lf ", mat[i][j]);
		// 	puts("");
		// }

		if(fabs(mat[0][0] - 1) < 1e-12 && fabs(mat[1][1] - 1) < 1e-12) {
			long double b = mat[1][2];
			long double a = mat[0][2];
			long long aa = (long long)(round(a));
			long long bb = (long long)(round(b));
			// printf("%.5Lf %.5Lf\n", a, b);
			printf("%lld %lld\n", aa, bb);
		} else {
			bool flag = 0;
			for(int i = 0 ; i < 2 ; i++) {
				bool nol = 1;
				for(int j = 0 ; j < 2 ; j++) {
					nol &= (fabs(mat[i][j]) < 1e-12);
				}

				if(nol) {
					if(fabs(mat[i][2]) > 1e-12) {
						flag = 1;
					}
				}
			}

			if(!flag) {
				puts("MULTIPLE SOLUTIONS");
			} else {
				puts("NO SOLUTION");
			}
		}
	}
	return 0;
}