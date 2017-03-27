#include <bits/stdc++.h>
using namespace std;

const int R = 15;
const int C = 15;
const int MAXVERTICE = 2 * R * C  + 5;
const int SOURCE = 0;
const int SINK = 1;
const int INF = (int)1e9;

int dr[4] = {0,-1,0,1};
int dc[4] = {-1,0,1,0};

#define pb push_back

struct edge{
	int from;
	int to;
	int cap;
	int cost;
};

//for MaxFlow
vector<edge> elist;
vector<int> adj[MAXVERTICE];
int cnt;
int numOfVertice;
bool con[MAXVERTICE][MAXVERTICE];

//for SPFA
int dist[MAXVERTICE];
bool in_q[MAXVERTICE];
int prv[MAXVERTICE];

int arr[R][C];
int r,c,d;

void hard_reset(){
	cnt = 0;
	memset(con,0,sizeof con);
	for(int i = 0 ; i <= numOfVertice ; i++){
		adj[i].clear();
	}
	elist.clear();
}

void reset(){
	for(int i = 0  ; i <= numOfVertice ; i++)
		dist[i] = INF;
}

void add(int from,int to,int cap,int cost){
	adj[from].pb(cnt++);
	adj[to].pb(cnt++);
	
	elist.pb({from,to,cap,cost});
	elist.pb({to,from,0,-cost});
}

int ID(int row,int col){
	if(row == -1 || row == r || col == -1 || col == c)
		return -1;
	return row * c + col;	
}

int In(int x){
	return 2 * (x + 1);
}

int Out(int x){
	return 2 * (x + 1) + 1;
}

void DFS(int now,int row,int col){
	int idx = ID(row,col);
	if(con[now][idx]) return;
	con[now][idx] = 1;
	for(int i = 0 ; i < 4 ; i++){
		int nr = row + dr[i];
		int nc = col + dc[i];
		int nxt = ID(nr,nc);
		if(nxt == -1 || arr[nr][nc] >= arr[row][col])
			continue;
		DFS(now,nr,nc);	
	}
}

void build_graph(){
	for(int i = 0 ; i < r * c ; i++){
		int row = i / c;
		int col = i % c;
		DFS(i,row,col);
		add(SOURCE,In(i),1,arr[row][col]);
		for(int j = 0 ; j < r * c ; j++)
			if(i != j && con[i][j]){
				add(In(i),Out(j),1,0);
			}
		add(Out(i),SINK,1,-arr[row][col]);	
	}
	numOfVertice = Out(r * c - 1);
}

void SPFA(){
	dist[SOURCE] = 0;
	queue<int> q;
	q.push(SOURCE);
	in_q[SOURCE] = 1;
	while(!q.empty()){
		int now = q.front();
		q.pop();
		in_q[now] = 0;
		for(int idx : adj[now]){
			int to = elist[idx].to;
			int cost = elist[idx].cost;
			int cap = elist[idx].cap;
			if(cap > 0 && dist[to] > dist[now] + cost){
				dist[to] = dist[now] + cost;
				prv[to] = idx;
				if(!in_q[to]){
					in_q[to] = 1;
					q.push(to);
				}
			}
		}
	}
}

pair<int,int> MinCostMaxFlow(){
	pair<int,int> res = {0,0};
	while(1){
		reset();
		SPFA();
		if(dist[SINK] == INF) break;
		int mins = INF;
		int ptr = SINK;
		while(ptr != SOURCE){
			int idx = prv[ptr];
			int from = elist[idx].from;
			int cap = elist[idx].cap;
			
			mins = min(mins,cap);
			res.second += elist[idx].cost;
			
			ptr = from;
		}
		
		res.first += mins;
		
		ptr = SINK;
		while(ptr != SOURCE){
			int idx = prv[ptr];
			int from = elist[idx].from;
			
			elist[idx].cap -= mins;
			elist[idx ^ 1].cap += mins;
			
			ptr = from;
		}
	}
	return res;
}

int main(){
	//ios_base::sync_with_stdio(0);
	while(scanf("%d %d %d",&r,&c,&d) && (r | c | d) > 0){
	//while(cin >> r >> c >> d && (r | c | d) > 0){
		for(int i = 0 ; i < r ; i++)
			for(int j = 0 ; j < c ; j++)
				scanf("%d",&arr[i][j]);
				//cin >> arr[i][j];
		build_graph();
		pair<int,int> ans = MinCostMaxFlow();
		ans.first = (r * c - ans.first - 1);
		ans.first *= d;
		printf("%d %d\n",ans.first,ans.second);
		//cout << ans.first << " " << ans.second << "\n";
		hard_reset();		
	}
	return 0;
}