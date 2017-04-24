//WA
#include <bits/stdc++.h>
using namespace std;

int w, h;
int arr[605][605];

void read() {
	scanf("%d %d",&h,&w);
	for(int i = 1 ; i <= h ; i++)
		for(int j = 0 ; j < w ; j++)
			scanf("%d",&arr[i][j]);
}

bool check() {
	int maks = 0;
	int mins = 1e9;
	int mid = h/2;
	for(int i = 0 ; i < w ; i++) {
		maks = max(maks,abs(arr[mid][i] - arr[mid+1][i]));
		mins = min(mins,abs(arr[mid][i] - arr[h][i]));
	}
	#define MAGIC 110
	return maks >= MAGIC && mins <= MAGIC;
}

int main() {
	int t; cin >> t;
	for(int tc = 0 ; tc < t ; tc++) {
		read();
		printf("%s\n",check() ? "YES" : "NO");
	}
	return 0;
}