#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const LL MOD = (LL)1e9 + 7;
const int N = 200005;

pii arr[N];
set<int> wall;
LL val[N];
LL bego[N];
LL BIT[N];
int n;

void update(int x,LL v) {
	for(; x <= n + 1 ; x += x & -x)
		BIT[x] = (BIT[x] + v) % MOD;
}

LL query(int x) {
	if(x <= 0) return 0;
	LL res = 0;
	while(x) {
		res = (res + BIT[x]) % MOD;
		x -= x & -x;
	}
	return res;
}

void init() {
	for(long long i = 1 ; i <= n ; i++) {
		val[i] = val[i - 1];
		bego[i] = ((LL)i * (i + 1) / 2ll) % MOD;
		val[i] = (val[i] + bego[i]) % MOD;
	}
	wall.insert(0);
	wall.insert(n + 1);
	update(1,bego[n]);
}

void solve() {
	sort(arr + 1,arr + n + 1);
	long long ans = 0;
	for(int i = 1 ; i <= n ; i++) {
		int cur = arr[i].fi;
		int pos = arr[i].se;
		auto it = wall.upper_bound(pos);
		int atas = *it - 1;
		it--;
		int bawah = *it + 1;
		//printf("pos %d atas %d bawah %d\n",pos,atas,bawah);
		wall.insert(pos);

		int len = atas - bawah + 1;

		if(pos == bawah && pos == atas) {
			update(bawah,-bego[len]);
		}
		else if(pos == atas) {
			update(bawah,-bego[len]);
			update(bawah,bego[len - 1]);
		}
		else if(pos == bawah) {
			update(bawah,-bego[len]);
			update(bawah + 1,bego[len - 1]);
		}
		else {
			update(bawah,-bego[len]);
			update(bawah,bego[pos - bawah]);
			update(pos + 1,bego[atas - pos]);
		}

		long long add = 0;
		// dari kiri
		add = (val[pos - bawah] * (atas - pos + 1)) % MOD;
		add = (add * cur) % MOD;
		ans = (ans + add) % MOD;
		//printf("add %lld\n",add);
		//dari kanan
		add = (val[atas - pos] * (pos - bawah + 1)) % MOD;
		add = (add * cur) % MOD;
		ans = (ans + add) % MOD;
		//printf("add %lld\n",add);
		//start independen
		long long subArray = ((LL)(pos - bawah + 1) * (atas - pos + 1)) % MOD;
		//independen kiri
		add = (query(bawah - 1) * cur) % MOD;
		add = (add * subArray) % MOD;
		ans = (ans + add) % MOD;
		//printf("add %lld\n",add);
		//independen kanan
		add = ((query(n) - query(atas + 1)) * cur) % MOD;
		add = (add * subArray) % MOD;
		ans = (ans + add) % MOD;
		//printf("add %lld\n",add); 
	}
	if(ans < 0) ans += MOD;
	printf("%lld\n",ans);
}

int main() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d",&arr[i].fi);
		arr[i].se = i;
	}

	init();
	solve();

	return 0;
}