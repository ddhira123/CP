#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n,m;
map<int,int> last;
map<int,int> lastMod;
int arr[N];
int tc;
int BIT[N];

void update(int x,int val){
	for(; x <= n + 1;  x += x & -x)
		BIT[x] += val;
}

int query(int x){
	int res = 0;
	while(x){
		res += BIT[x];
		x -= x & -x;
	}
	return res;
}

int main(){
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++){
		last.clear();
		lastMod.clear();
		memset(BIT,0,sizeof BIT);
		scanf("%d %d",&n,&m);
		for(int i = 1 ; i <= n ; i++){
			int x;
			scanf("%d",&x);
			arr[i] = x;
			last[x] = n + 1;
			lastMod[x % m] = n + 1;
			lastMod[(m - (arr[i] % m)) % m] = n + 1;
			update(n + 1,1);
		}
		int maks = -1;
		int best = -1;
		for(int i = n ; i >= 1 ; i--){
			int nxt = last[arr[i]];
			update(nxt,-1);
			update(i,1);
			last[arr[i]] = i;
			lastMod[arr[i] % m] = i;
			int mod = (m - (arr[i] % m)) % m;
			int lmt = lastMod[mod];
			int res = query(lmt - 1);
			//cout << i << " " << mod << " " << lmt << " " << res << endl;
			if(res >= maks){
				maks = res;
				best = i;
			}
		}
		int kanan = best;
		if(maks > 0){
			int lastAdd = best;
			int cannot = (m - (arr[best] % m)) % m;
			set<int> seen;
			int iter = best;
			while(iter <= n && arr[iter] % m != cannot){
				if(seen.count(arr[iter]) == 0){
					lastAdd = iter;
					seen.insert(arr[iter]);
				}
				iter++;
			}
			kanan = lastAdd;
		}
		if(maks == 0)
			printf("Case #%d: impossible\n",t);
		else
			printf("Case #%d: %d %d %d\n",t,maks,best,kanan);	
	}
	return 0;
}
