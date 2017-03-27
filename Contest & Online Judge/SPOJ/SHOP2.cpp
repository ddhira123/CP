#include <bits/stdc++.h>
using namespace std;

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

const int N = 2001;
const int SOURCE = 0;
const int SINK = 1;
const int INF = (int)1e9;
struct edge{
	int to;
	int cap;
};

vector<int> adj[2 * N + 5];
vector<edge> elist;
int it[2 * N + 5];
int dist[2 * N + 5];
int prv[2 * N + 5];
int cnt;
int n,m;

void add(int fr,int to,int cap){
	adj[fr].pb(cnt++);
	adj[to].pb(cnt++);
	
	elist.pb({to,cap});
	elist.pb({fr,0});
}

void hard_reset(){
	elist.clear();
	for(int i = 0 ; i <= n + m + 1 ; i++)
		adj[i].clear();
	cnt = 0;	
}

void reset(){
	for(int i = 0 ; i <= n + m + 1 ; i++){
		it[i] = 0;
		dist[i] = -1;
	}
}

void BFS(){
	dist[SOURCE] = 1;
	queue<int> q;
	q.push(SOURCE);
	while(!q.empty()){
		int now = q.front();
		q.pop();
		for(int idx : adj[now]){
			int to = elist[idx].to;
			int cap = elist[idx].cap;
			if(dist[to] == -1 && cap > 0){
				dist[to] = dist[now] + 1;
				prv[to] = idx;
				q.push(to);
			}
		}
	}
}

int augment(int now,int mins){
	if(now == SINK)
		return mins;
	while(it[now] < adj[now].size()){
		int idx = adj[now][it[now]];
		int to = elist[idx].to;
		int cap = elist[idx].cap;
		if(dist[to] != dist[now] + 1 || cap == 0)
			it[now]++;
		else{
			int ret = augment(to,min(mins,cap));
			if(ret > 0){
				elist[idx].cap -= ret;
				elist[idx ^ 1].cap += ret;
				return ret;
			}
			else
				it[now]++;
		}	
	}
	return 0;	
}

int augmentkarp(int now,int mins){
	if(now == SOURCE)
		return mins;
	int idx = prv[now];
	int fr = elist[idx ^ 1].to;
	int res = augmentkarp(fr,min(mins,elist[idx].cap));
	elist[idx].cap -= res;
	elist[idx ^ 1].cap += res;
	return res;
}

int maxflow(){
	int mf = 0;
	while(1){
		reset();
		BFS();
		if(dist[SINK] == -1) break;
		int ret = 0;
		ret = augment(SOURCE,INF);
		//ret = augmentkarp(SINK,INF);
		while(ret){
			mf += ret;
			ret = augment(SOURCE,INF);
		}
	}
	return mf;
}

int main(){
	int tc;
	io(tc);
	while(tc--){
		io(n); io(m);
		int sum = 0;
		for(int i = 1 ; i <= n ; i++){
			int val;
			io(val);
			sum += val;
			add(i + m + 1,SINK,val);
		}
		for(int i = 1 ; i <= m ; i++){
			int val;
			io(val);
			add(SOURCE,i + 1,val);
		}
		for(int i = 1 ; i <= m ; i++){
			int k;
			io(k);
			for(int j = 1 ; j <= k ; j++){
				int x;
				io(x);
				add(i + 1,x + m + 1,INF);
			}
		}
		printf("%d\n",sum - maxflow());
		hard_reset();
	}	
	return 0;
}