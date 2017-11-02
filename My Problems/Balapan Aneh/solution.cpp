#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define ll long long

const int N = 5e4 + 5;
const ll INF = 1e18;

struct poli{
	ll a, b, c;
} pol[N];

ll p[N];
pair<ll, ll> depth[N]; // ganjil, genap
vector <ll> adj[N];

void reset(int n){
	
	for(int i=1; i<=n; i++)
		depth[i] = {INF, INF};

}

void bfs(int n){

	reset(n);

	queue <pair <int, int>> q;
	q.push({n, 0});

	while(!q.empty()){
		ll now = q.front().f;
		ll x = q.front().s;
		q.pop();

		if(x%2 == 0){
			if(depth[now].s > x)
				depth[now].s = x;
			else
				continue;
		}
		else{
			if(depth[now].f > x)
				depth[now].f = x;
			else
				continue;
		}

		for(ll v : adj[now])
			q.push({v, x+1});
	}
}

ll result(ll i, ll t){
	return pol[i].a*t*t + pol[i].b*t + pol[i].c;
}

ll solve(ll i){
	ll ans = INF;
	ll mid = -pol[i].b/(2ll*pol[i].a);

	// cek ganjil
	if(depth[p[i]].f != INF){
		// mulai dari kanan
		if(depth[p[i]].f > mid)
			ans = min(ans, result(i, depth[p[i]].f));
		// cek kiri dan kanan
		else if(mid%2 == 1)
			ans = min(ans, min(result(i, mid), result(i, mid+2)));
		else
			ans = min(ans, min(result(i, max(mid-1, depth[p[i]].f)), result(i, mid+1)));
	}

	// cek genap
	if(depth[p[i]].s != INF){
		// mulai dari kanan
		if(depth[p[i]].s > mid)
			ans = min(ans, result(i, depth[p[i]].s));
		// cek kiri dan kanan
		else if(mid%2 == 0)
			ans = min(ans, min(result(i, mid), result(i, mid+2)));
		else
			ans = min(ans, min(result(i, max(mid-1, depth[p[i]].s)), result(i, mid+1)));
	}
	
	return ans;
}

int main(){
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	for(int i=0; i<m; i++){
		ll u, v;
		scanf("%lld %lld", &u, &v);

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(int i=1; i<=k; i++){
		scanf("%lld %lld %lld %lld", &p[i], &pol[i].a, &pol[i].b, &pol[i].c);
		assert(pol[i].a != 0);
	}

	bfs(n);

	for(int i=1; i<=k; i++)
		printf("%lld\n", solve(i));
}