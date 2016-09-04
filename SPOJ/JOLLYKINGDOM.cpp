#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
#define pb push_back

inline void io(int &ptr){
	ptr = 0;
	register char c;
	while(1){
		c = getchar_unlocked();
		if(c != '\n' && c != ' ') break;
	}
	int res = 0, sign = 1;
	if(c=='-') sign = -1;
	else res = c-'0';
	while(1){
		c = getchar_unlocked();
		if(c == ' ' || c == '\n' || c == EOF) break;
		res = (res << 3) + (res << 1) + c - '0';
	}
	ptr = res * sign;
}

int flow[2 * N][2 * N];
vector<int> adj[2 * N];
int par[2 * N];
int lvl[2 * N];
int place[2 * N][2 * N];
int cnt[2 * N];
int n,m,h;
int mf = 0;
int kiri,kanan;

void add(int from,int to) {
	from++ ; to += n + 1; 
	if(flow[from][to] == 0 && flow[to][from] == 0) {
		flow[from][to] = 1;
		adj[from].pb(to);
		
		place[from][to] = cnt[from]++;
	}
	
	if(flow[0][from] == 0 && flow[from][0] == 0) {
		adj[0].pb(from);
		flow[0][from] = 1;
		
		place[0][from] = cnt[0]++;
		kiri++;
	}

	if(flow[1][to] == 0 && flow[to][1] == 0) {
		adj[to].pb(1);
		flow[to][1] = 1;
		
		place[to][1] = cnt[to]++;
		kanan++;
	}
}

vector<int> haha;

bool bfs() {
	for(int x : haha) lvl[x] = -1;
	haha.clear();
	queue<int> q;
	q.push(0);
	
	while(!q.empty() && lvl[1] == -1) {
		int now = q.front();
		q.pop();
		for(int nxt : adj[now]) {
			if(lvl[nxt] == -1) {
				lvl[nxt] = lvl[now] + 1;
				par[nxt] = now;
				q.push(nxt);
				haha.push_back(nxt);
			}
		}
	}
	return lvl[1] != -1;	
}

void maxFlow() {
	bool apadeh = bfs();
	
	if(!apadeh) return;
	mf++;
	
	int now = 1;
	while(now != 0) {
		int papa = par[now];
		flow[papa][now]--;
		flow[now][papa]++;
		
		adj[now].pb(papa);
		place[now][papa] = cnt[now]++;
		
		int temp = place[papa][now];
		swap(adj[papa][temp], adj[papa][cnt[papa] - 1]);
		place[papa][adj[papa][temp] ] = temp;
		cnt[papa]--;
		adj[papa].pop_back();
		
		now = papa;
	}
}

int main() {
	memset(lvl,-1,sizeof lvl);
	lvl[0] = 0;
	//io(n); io(m); io(h);
	scanf("%d %d %d",&n,&m,&h);
	for(int i = 0 ; i < h ; i++) {
		int x,y;
		//io(x); io(y);
		scanf("%d %d",&x,&y);
		add(x,y);
		if(mf != min(kiri,kanan))
			maxFlow();
		printf("%d\n",mf);
	}
	return 0;
}
