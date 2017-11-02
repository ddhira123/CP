#include <bits/stdc++.h>
using namespace std;

const int N = 9;

long long nilai[20005];
long long arr[N];
int pwr[N + 5];
int mask[N];
int n;

void pre() {
	pwr[0] = 1;
	for(int i = 1 ; i <= N ; i++)
		pwr[i] = 3 * pwr[i - 1];
	for(int st = 0 ; st < n ; st++)
		for(int i = 0 ; i < 5 ; i++)
			mask[st] += pwr[(st + i) % n];
}

void dfs(int cur) {
	int temp_mask[N];
	int temp = cur;
	for(int i = 0 ; i < n ; i++) {
		temp_mask[i] = temp % 3;
		temp /= 3; 
	}

	for(int st = 0 ; st < n ; st++) {
		int mins = 10;
		int maks = -1;
		for(int i = 0 ; i < 5 ; i++) {
			mins = min(mins,temp_mask[(i + st) % n]);
			maks = max(maks,temp_mask[(i + st) % n]);
		}
		if(mins > 0) {
			int nex = cur - mask[st];
			if(nilai[nex] == -1) {
				nilai[nex] = nilai[cur] - arr[st];
				dfs(nex);
			}
		}
		if(maks < 2) {
			int nex = cur + mask[st];
			if(nilai[nex] == -1) {
				nilai[nex] = nilai[cur] + arr[st];
				dfs(nex);
			}
		}
	}
}

int main() {
	cin >> n;
	pre();
	for(int i = 0 ; i < n ; i++) cin >> arr[i];
	memset(nilai,-1,sizeof nilai);
	nilai[0] = 0;
	dfs(0);

	long long best = (long long)4e18;
	vector<int> ans;

	for(int i = 0 ; i < pwr[n] ; i++) {
		int temp = i;
		int maks = -1;
		vector<int> res;

		for(int j = 0 ; j < n ; j++) {
			int haha = temp % 3;
			if(haha > 0) {
				maks = max(maks,haha);
				res.push_back(j);
			}
			temp /= 3;
		}

		if(maks == 1 && res.size() == 5 && nilai[i] != -1 && best > nilai[i]) {
			best = nilai[i];
			ans = res;
		}
	}

	printf("%d",ans[0]);
	for(int i = 1 ; i < 5 ; i++)
		printf(" %d",ans[i]);
	puts("");
	return 0;
}