#include <bits/stdc++.h>
using namespace std;

const int N = 25;

int arr[N][N];
int n, m;

bool coba(int a,int b) {
	for(int i = 1 ; i <= n ; i++) swap(arr[i][a],arr[i][b]);
	bool ok = 1;
	for(int i = 1 ; i <= n ; i++) {
		int tot = 0;
		for(int j = 1 ; j <= m ; j++) tot += (arr[i][j] != j);
		ok &= (tot <= 2);
	}
	for(int i = 1 ; i <= n ; i++) swap(arr[i][a],arr[i][b]);
	return ok;
}

int main() {
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++)
			cin >> arr[i][j];
	for(int i = 1 ; i <= m ; i++)
		for(int j = i ; j <= m ; j++)
			if(coba(i,j)) {
				cout << "YES\n";
				return 0;
			}
	cout << "NO\n";			
	return 0;
}