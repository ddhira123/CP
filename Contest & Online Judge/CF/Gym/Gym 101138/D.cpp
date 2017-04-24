#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 400;

struct kuery {
	int id;
	int sign;
	int l, r;

	bool operator <(kuery other) const {
		if(l / MAGIC == other.l / MAGIC)
			return r < other.r;
		return l / MAGIC < other.l / MAGIC;
	}
};

vector<kuery> v;
vector<kuery> v2;
long long ans[50005];
int cnt[50005];
int arr[50005];
int n, q;
pair<pair<int,int>,pair<int,int>> qq[50005];

//[1,b], [1,d]
void adder2(int id,int sign,int b,int d) {
	if(b > d) swap(b,d);

	v2.push_back((kuery){id,sign,1,d});
	if(b < d)
		v2.push_back((kuery){id,-sign,b+1,d});

	v.push_back((kuery){id,-sign,1,d});
	v.push_back((kuery){id,sign,1,b});
	if(b < d) {
		v.push_back((kuery){id,sign,b+1,d});
	}	
}

//
void adder(int id,int sign,int a,int b,int c,int d) {
	adder2(id,sign,b,d);
	if(a > 1) adder2(id,-sign,a-1,d);
	if(c > 1) adder2(id,-sign,b,c-1);
	if(a > 1 && c > 1) adder2(id,sign,a-1,c-1);
}

void init() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",arr + i);
	scanf("%d",&q);
	for(int i = 0 ; i < q ; i++) {
		int a, b, c ,d;
		scanf("%d %d %d %d",&a,&b,&c,&d);
		
		adder(i,1,a,b,c,d);
	}
}

void work() {
	sort(v.begin(),v.end());
	int l = 1, r = 1;
	long long tot = 0;

	for(int i = 0 ; i < v.size() ; i++) {
		int a = v[i].l;
		int b = v[i].r;

		while(r <= b) {
			tot += cnt[arr[r]];
			cnt[arr[r]]++;
			//printf("a %d %d %lld\n",r,arr[r],tot);
			r++;
		}

		while(l > a) {
			l--;
			tot += cnt[arr[l]];
			cnt[arr[l]]++;
		}

		while(l < a) {
			cnt[arr[l]]--;
			tot -= cnt[arr[l]];
			//printf("c %d %d %lld\n",l,arr[l],tot);
			l++;
		}

		while(r-1 > b) {
			r--;
			cnt[arr[r]]--;
			tot -= cnt[arr[r]];
			//printf("d %d %d %lld\n",r,arr[r],tot);
		}

		//printf("%d %d %lld\n",a,b,tot);
		ans[v[i].id] += tot * v[i].sign;
	}
}

void work2() {
	sort(v2.begin(),v2.end());
	int l = 1, r = 1;
	long long tot = 0;
	memset(cnt,0,sizeof cnt);

	for(int i = 0 ; i < v2.size() ; i++) {
		int a = v2[i].l;
		int b = v2[i].r;

		while(r <= b) {
			tot += (2*cnt[arr[r]]+1);
			cnt[arr[r]]++;
			r++;
		}

		while(l > a) {
			l--;
			tot += (2*cnt[arr[l]]+1);
			cnt[arr[l]]++;
		}

		while(l < a) {
			cnt[arr[l]]--;
			tot -= (2*cnt[arr[l]]+1);
			l++;
		}

		while(r-1 > b) {
			r--;
			cnt[arr[r]]--;
			tot -= (2*cnt[arr[r]]+1);
		}

		ans[v2[i].id] += tot * v2[i].sign;
	}
}

void solve() {
	work();
	work2();
	for(int i = 0 ; i < q ; i++)
		printf("%lld\n",ans[i]);
}

int main() {
	init();
	solve();
	return 0;
}