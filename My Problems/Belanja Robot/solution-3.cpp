#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
#define mp make_pair
using namespace std;
int n, q;
int p[100005], s[100005];
int globalK;
vector <pair <int,int> > vc[100005];
long long ans[100005];
int maxi[20], valMap[100005], val[20];

bool cmp(pair <int,int> a, pair <int,int> b){
	return (double)a.s / a.f > (double) b.s / b.f;
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
		int a, b;
		scanf("%d%d", &a,&b);
		scanf("%d%d", &a,&b);
		vc[a].pb(mp(i, b));
	}
	for (int i = 1; i <= n; i++){
		maxi[valMap[p[i]]] = max(maxi[valMap[p[i]]], s[i]);
		vector <pair <int,int> > gg(globalK);
		for (int j = 0; j < globalK; j++)
			gg[j] = make_pair(val[j], maxi[j]);
		sort(gg.begin(), gg.end(), cmp);
		for (int j = 0; j < vc[i].size(); j++){
			long long tmp = 0, money = vc[i][j].s;
			for (int k = 0; k < globalK; k++){
				if (money < gg[k].f) continue;
				tmp+=(money / gg[k].f) * gg[k].s;
				money%=gg[k].f;
			}
			ans[vc[i][j].f] = tmp;
		}
	}
	for (int i = 0 ; i < q; i++)
		printf("%lld\n", ans[i]);
}