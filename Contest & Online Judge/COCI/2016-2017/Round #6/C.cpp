#include <bits/stdc++.h>
using namespace std;

const int N = 20;
const int MX = (1<<N) + 5;

pair<int,int> arr[MX];
int val[MX];
int ans[MX];
int n;

void precompute() {
	for(int i = 2 ; i < MX ; i++)
		val[i] = 1 + val[i/2];
}

int main() {
	precompute();

	scanf("%d", &n);
	int len = 1 << n;
	for(int i = 0 ; i < len ; i++) {
		scanf("%d",&arr[i].first);
		arr[i].second = i;
	}

	sort(arr, arr + len);
	int j = 0;

	for(int i = 0 ; i < len ; i++) {
		while(j < len && arr[j].first <= arr[i].first) j++;
		ans[arr[i].second] = n - val[j];
	}

	for(int i = 0 ; i < len ; i++)
		printf("%d%c", ans[i], i+1 == len ? '\n' : ' ');
	return 0;
}