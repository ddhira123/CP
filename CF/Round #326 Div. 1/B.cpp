#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 1000005;
const LL MOD = (LL)1e9 + 7;

LL dp[2][N];
LL n,k,l;
pair<int,int> arr[N];

LL get(){
	LL panjang = (l + n - 1) / n;
	LL sisa = l % n;
	if(sisa == 0){
		sisa = n;
	}
	//cout << panjang << endl;
	LL ans = 0;
	int bit = 0;
	for(int i = 0 ; i < n ; i++)
		if((LL)arr[i].se < l)
			dp[bit][i] = 1;
	for(int i = 0 ; i < k && n * i < l; i++){
		for(int j = 0 ; j < n ; j++)
			dp[bit ^ 1][j] = 0;
		LL tot = 0;
		int j = 0;
		while(j < n){
			int iter = j;
			while(iter < n && arr[j].fi == arr[iter].fi) {
				tot = (dp[bit][iter] + tot) % MOD;
				iter++;
			}
			iter = j;
			while(iter < n && arr[j].fi == arr[iter].fi){
				int tempat = arr[iter].se;
				dp[bit ^ 1][iter] = tot;
				LL bisa = 0;
				if(tempat < sisa){
					bisa = panjang - i;
				}
				else{
					bisa = panjang - i - 1;
				}
				bisa %= MOD;
				//cout << iter << " " << bisa << " " << dp[bit][iter] << " " << tot << endl;
				ans = (ans + bisa * dp[bit][iter]) % MOD;
				iter++;
			}
			j = iter;	
		}
		bit ^= 1;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n >> l >> k;
	for(int i = 0 ; i < n ; i++){
		cin >> arr[i].fi;
		arr[i].se = i;
	}
	sort(arr,arr + n);
	cout << get() << endl;
	return 0;
}
