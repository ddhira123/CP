#include <bits/stdc++.h>
using namespace std;

string words[7];
string grid[20];

int main() {
	// for(int i = 0 ; i < 7 ; i++)
	// 	cin >> words[i];
	// for(int i = 0 ; i < 20 ; i++) {
	// 	cin >> grid[i];
	// }
	// for(int i = 0 ; i < 7 ; i++) {
	// 	cout << "CARI " << words[i] << endl;
	// 	bool ada = false;
	// 	int len = words[i].length();

	// 	for(int ii = 0 ; ii < 20 ; ii++)
	// 		for(int jj = 0 ; jj < 20 ; jj++) {
	// 			// cout << ii << "  "<< jj << endl;
	// 			// ke kanan
	// 			int k;
	// 			for(k = 0 ; k < len && jj + k < 20 && grid[ii][jj+k] == words[i][k] ; k++){
	// 				// cout << k << endl;
	// 			}
	// 			ada |= (k == len);

	// 			// ke kiri
	// 			for(k = 0 ; k < len && jj - k >= 0 && grid[ii][jj-k] == words[i][k] ; k++){}
	// 			ada |= (k == len);

	// 			// ke bawah
	// 			for(k = 0 ; k < len && ii + k < 20 && grid[ii+k][jj] == words[i][k] ; k++){}
	// 			ada |= (k == len);

	// 			// ke atas
	// 			for(k = 0 ; k < len && ii - k >= 0 && grid[ii-k][jj] == words[i][k] ; k++){}
	// 			ada |= (k == len);
	// 		}

	// 	if(!ada) {
	// 		cout << words[i] << " FAIL\n";
	// 	}
	// }
	cout << "PANJATPINANG\n";
	return 0;
}