#include <bits/stdc++.h>
using namespace std;

vector<int> active;
vector<pair<int,int>> ans;
int n;
int arr[200005];

int main() {
	scanf("%d", &n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d", arr + i);
	for(int i = n ; i >= 1;  i--) {
		if(active.size() < arr[i]) {
			puts("NO");
			return 0;
		}
		while(arr[i]) {
			ans.push_back({i, active.back()});
			active.pop_back();
			arr[i]--;
		}
		active.push_back(i);
	}
	puts("YES");
	for(pair<int,int> x : ans) {
		printf("%d %d\n", x.first, x.second);
	}
	return 0;
}