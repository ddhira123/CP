#include <bits/stdc++.h>
using namespace std;

string arr[105];
int psum[105][105];
int r,c,s;

int main() {
	cin >> r >> c >> s;
	for(int i = 0 ; i < r ; i++)
		cin >> arr[i];
	for(int i = 0 ; i < r ; i++) {
		for(int j = 0 ; j < c ; j++) {
			psum[i][j] = arr[i][j] == '*';

			if(i) psum[i][j] += psum[i - 1][j];
			if(j) psum[i][j] += psum[i][j - 1];
			if(i > 0 && j > 0) psum[i][j] -= psum[i - 1][j - 1];
		}
	}

	int best = -1;
	int rs = -1;
	int cs = -1;

	for(int i = 0 ; i + s - 1 < r ; i++)
		for(int j = 0 ; j + s - 1 < c ; j++) {
			int bawah = i + s - 2;
			int kanan = j + s - 2;
			int ii = i + 1;
			int jj = j + 1;

			int ret = psum[bawah][kanan];
			if(ii) ret -= psum[ii - 1][kanan];
			if(jj) ret -= psum[bawah][jj - 1];
			if(ii > 0 && jj > 0) ret += psum[ii - 1][jj - 1];

			if(ret > best) {
				best = ret;
				rs = i;
				cs = j;
			}
		}

	for(int j = 0 ; j < s ; j++) {
		arr[rs][cs + j] = '-';
		arr[rs + s - 1][cs + j] = '-';
	}	

	for(int i = 0 ; i < s ; i++) {
		arr[rs + i][cs] = '|';
		arr[rs + i][cs + s - 1] = '|';
	}

	arr[rs][cs] = arr[rs][cs + s - 1] = arr[rs + s - 1][cs] = arr[rs + s - 1][cs + s - 1] = '+';

	cout << best << "\n";
	for(int i = 0 ; i < r ; i++) {
		cout << arr[i] << "\n";
	}
	return 0;
}