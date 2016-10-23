// upsolving
#include <bits/stdc++.h>
using namespace std;

const int MX = 2e5 + 5;

int BIT[MX];
int arr[MX];
int c, n;

void update(int x,int val) {
	for(; x <= c ; x += x & -x)
		BIT[x] += val;
}

int query(int x) {
	int ret = 0;
	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}
	return ret;
}

int getClosest(int x) {
	int tot = query(x);
	int ret = 0;
	for(int i = 17 ; i >= 0 ; i--)
		if(ret + (1<<i) <= c && tot > BIT[ret + (1<<i)]) {
			ret += (1<<i);
			tot -= BIT[ret];
		}
	return ret+1;
}

bool check(int sum) {
	//cerr << sum << "\n";
	if(sum == 0) return 1;
	if(query(sum) == 0) return 0;
	
	int val = getClosest(sum);
	int occ = query(val) - query(val-1);
	int butuh = sum / val;
	occ = min(occ,butuh);

	update(val,-occ);
	bool ret = check(sum - val*occ);
	update(val,occ);

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);

	cin >> c >> n;
	for(int i = 0 ; i < n ; i++) {
		cin >> arr[i];
		update(arr[i],1);
	}

	sort(arr,arr + n);

	int cur = c;
	int lst = c+1;
	int ans = c+1;
	for(int i = n-1 ; i >= 0 ; i--) {
		if(cur >= arr[i]) {
			//cerr << "masuk " << arr[i] << "\n";
			for(int j = arr[i] ; j < lst && cur-j > 0 ; j++)
				if(!check(cur - j)) {
					ans = j;
					break;
				}
			lst = arr[i];
			cur -= arr[i];
		}
		update(arr[i],-1);
	}

	if(ans == c+1) cout << "Greed is good\n";
	else cout << ans << "\n";
	return 0;
}