#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int MX = 2000000;

int cnt[MX + 5];
int n;

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n;
	for(int i = 0 ; i  < n ; i++){
		int x;
		cin >> x;
		cnt[x]++;
	}
	int ans = 0;
	for(int i = 0 ; i <= MX ; i++){
		cnt[i + 1] += cnt[i] / 2;
		if(cnt[i] % 2 == 1)
			ans++;
	}
	cout << ans << endl;
	return 0;
}
