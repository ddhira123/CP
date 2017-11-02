#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
#define mp make_pair
using namespace std;
int n, q;
int p[100005], s[100005];
int globalK;
vector <pair <pair <int,int>,int> > vc[100005];
long long ans[100005];
int maxi[20], valMap[100005], val[20];
vector <pair <int, int> > st[20];

bool cmp(pair <int,int> a, pair <int,int> b){
	return (double)a.s / a.f > (double) b.s / b.f;
}

void insert(int k, int val, int pos){
	while (!st[k].empty() && val >= st[k].back().f) st[k].pop_back();
	st[k].push_back(make_pair(val, pos));
}

int binser(int k,int pos){
	if (st[k].empty()) return 0;
	int l = 0, r = st[k].size() -1;
	if (st[k][r].s < pos) return 0;
	while (l < r){
		int mid = (l + r)>>1;
		if (st[k][mid].s < pos) l = mid + 1;
		else r = mid;
	}
	return st[k][l].f;
}

int main(){
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++){
		scanf("%d", &p[i]);
		valMap[p[i]] = 1;
	}
	for (int i = 1; i <= 1e5; i++)
		if (valMap[i]){
			valMap[i] = globalK;
			val[globalK++] = i;
		}
	for (int i = 1; i <= n; i++)
		scanf("%d", &s[i]);

	for (int i = 0; i < q; i++){
		int a, b, c;
		scanf("%d%d", &a,&c);
		scanf("%d%d", &a,&b);
		vc[a].pb(mp(mp(i, b), c));
	}
	for (int i = 1; i <= n; i++){
		insert(valMap[p[i]], s[i], i);
		for (int j = 0; j < vc[i].size(); j++){
			long long tmp = 0, money = vc[i][j].f.s;
			vector <pair <int,int> > gg(globalK);
			for (int k = 0; k < globalK; k++)
				gg[k] = make_pair(val[k], binser(k, vc[i][j].s));
			sort(gg.begin(), gg.end(), cmp);
			for (int k = 0; k < globalK; k++){
				if (money < gg[k].f) continue;
				tmp+=(money / gg[k].f) * gg[k].s;
				money%=gg[k].f;
			}
			ans[vc[i][j].f.f] = tmp;
		}
	}
	for (int i = 0 ; i < q; i++)
		printf("%lld\n", ans[i]);
}