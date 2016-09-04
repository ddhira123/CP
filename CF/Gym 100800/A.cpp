#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const int N = 505;
const double EPS = 1e-9;
const double INF = 1e9;

int n,s,t;
double q;
double x[N], y[N];
int h[N];
int isi[N];
double mins[N];
double dist[N][N];
bool visited[N];

void read() {
	cin >> n >> s >> t >> q;
	for(int i = 1 ; i <= n ; i++)
		cin >> x[i] >> y[i] >> h[i];
	for(int i = 1 ; i <= s ; i++)
		cin >> isi[i];
	for(int i = 1 ; i <= t ; i++)
		cin >> isi[s + i];
}

void make() {
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			if(i == j)
				dist[i][j] = 0;
			else if (h[i] > h[j] && sqrt(q) + EPS > hypot(x[i] - x[j],y[i] - y[j]))
				dist[i][j] = hypot(x[i] - x[j],y[i] - y[j]);

	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			for(int k = 1 ; k <= n ; k++)
				dist[j][k] = min(dist[j][k],dist[j][i] + dist[i][k]);		
}

void solve() {
	for(int i = 1 ; i <= s + t;  i++)
		if(i <= s) mins[i] = 0;
		else mins[i] = INF;

	double tot = 0;
	for(int i = 1 ; i <= s + t ; i++) {
		int cur = -1;
		for(int j = 1 ; j <= s + t ; j++)
			if(!visited[j] && (cur == -1 || mins[cur] > mins[j]))
				cur = j;
		if(fabs(mins[cur],INF) < EPS) {
			puts("IMPOSSIBLE");
			return;
		}	
		visited[cur] = 1;
		for(int j = 1 ; j <= s + t ; j++)
			mins[j] = min(mins[j],dist[isi[cur]][isi[j]]);
	}	
}

int main() {
	return 0;
}