#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second
#define mp make_pair
using namespace std;
typedef pair <int,int> pi;
typedef long long ll;
const ll INF = 1e18;
int n, m , k;
int dist[50005];
vector <int> vc[50005];

void bfs(){
	queue <pi> q;
	memset(dist, -1, sizeof(dist));
	q.push(mp(0, n));
	dist[n] = 0;
	while (!q.empty()){
		pi top = q.front();
		q.pop();
		if (dist[top.s] < top.f) continue;

		for (int nxt : vc[top.s]){
			if (dist[nxt] == -1){
				dist[nxt] = dist[top.s] + 1;
				q.push(mp(dist[nxt], nxt));
			}
		}
	}
}

ll f(ll a, ll b, ll c, ll t){
	return a * t * t + b * t + c;
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; i++){
		int a, b;
		scanf("%d%d",
		 &a, &b);
		vc[a].pb(b);
		vc[b].pb(a);
	}
	bfs();
	for (int i = 0; i < k; i++){
		int p, a, b, c;
		scanf("%d%d%d%d", &p, &a, &b, &c);
		printf("%lld\n", f(a,b,c,dist[p]));
	}
}