#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
pair <int,int> x[100005];

bool cmp(pair <int,int> a, pair <int,int> b){
	return (double)a.s / a.f > (double) b.s / b.f;
}

long long query(int l, int r, int m){
	vector <pair <int,int> > vc;
	for (int i = l; i <= r; i++)
		vc.push_back(x[i]);
	sort(vc.begin(), vc.end(), cmp);
	long long ans = 0;
	for (int i = 0; i < vc.size(); i++){
		while (m >= vc[i].f){
			ans+=vc[i].s;
			m-=vc[i].f;
		}
	}
	return ans;
}

int main(){
	int n, q;
	scanf("%d%d" ,&n,&q); 
	for (int i = 1; i <= n; i++)
		scanf("%d", &x[i].f);
	for (int i = 1; i <=n; i++)
		scanf("%d", &x[i].s);
	for (; q--; ){
		int c;
		scanf("%d", &c);
		if (c == 1){
			int l,r,m;
			scanf("%d%d%d", &l, &r, &m);
			printf("%lld\n", query(l,r,m));
		}else{
			int a, y;
			scanf("%d%d", &a, &y);
			x[a].f = y;
		}
	}
}