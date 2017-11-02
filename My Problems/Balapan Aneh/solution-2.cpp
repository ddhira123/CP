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
int dist[50005][2];
int globalP;
vector <int> vc[50005];
//5 4 1
//1 2
//2 3
//3 4
//4 5
//1 1 -10 0
void bfs(){
	queue <pi> q;
	memset(dist, -1, sizeof(dist));
	q.push(mp(0, globalP));
	dist[globalP][0] = 0;
	while (!q.empty()){
		pi top = q.front();
		q.pop();
		if (dist[top.s][top.f&1] < top.f) continue;
		int now = top.f&1;
		for (int nxt : vc[top.s]){
			int s = (top.f+1)&1;
			if (dist[nxt][s] == -1){
				dist[nxt][s] = dist[top.s][now] + 1;
				q.push(mp(dist[nxt][s], nxt));
			}
		}
	}
}

ll f(ll a, ll b, ll c, ll t){
	return a * t * t + b * t + c;
}


ll ternary_search(int a, int b, int c, int l){
	if (l == -1) return INF;
	int base = (l&1);
	l/=2;
	int r = 5e5;
	while (l < r){
		int mid1 = l + (r - l)/3;
		int mid2 = r - (r - l)/3;
		if (f(a, b, c, mid1 * 2 + base) < f(a, b, c, mid2 * 2 + base)) r = mid2 - 1;
		else l = mid1 + 1;
	}
	return f(a, b, c, l * 2 + base);
}

ll min_val(int p, int a, int b, int c){
	return min(ternary_search(a, b, c, dist[n][0]), ternary_search(a, b, c, dist[n][1]));
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
	for (int i = 0; i < k; i++){
		int p, a, b, c;
		scanf("%d%d%d%d", &p, &a, &b, &c);
		globalP = p;
		bfs();
		printf("%lld\n", min_val(p, a, b, c));
	}
}