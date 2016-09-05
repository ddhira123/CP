#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define pb push_back

char c[2][5];
int arr[2][4];
int temp[2][4];

int main() {
	for(int i = 0 ; i < 2 ; i++) {
		for(int j = 0 ; j < 2 ; j++)
			scanf("%s",c[j]);
		arr[i][0] = c[0][0];
		arr[i][1] = c[0][1];
		arr[i][2] = c[1][1];
		arr[i][3] = c[1][0];		
	}

	bool can = 0;
	for(int i = -3 ; i < 4 ; i++)
		for(int j = -3 ; j < 4 ; j++) {
			int d[2],t[2];
			d[0] = i < 0 ? 3 : 1;
			d[1] = j < 0 ? 3 : 1;
			t[0] = abs(i);
			t[1] = abs(j);

			for(int k = 0 ; k < 4 ; k++) {
				temp[0][k] = arr[0][k];
				temp[1][k] = arr[1][k];
			}

			for(int tipe = 0 ; tipe < 2 ; tipe++)
				for(int k = 0 ; k < t[tipe] ; k++)
					for(int iter = 0 ; iter < 4 ; iter++)
						if(temp[tipe][iter] == 'X') {
							swap(temp[tipe][iter],temp[tipe][(iter + d[tipe]) % 4]);
							break;
						}

			bool valid = 1;
			for(int k = 0 ; k < 4 ; k++)
				valid &= (temp[0][k] == temp[1][k]);
			can |= valid;				
		}
	
	printf("%s\n",can ? "YES" : "NO");
	return 0;
}