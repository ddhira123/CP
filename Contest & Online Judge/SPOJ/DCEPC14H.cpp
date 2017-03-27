#include <bits/stdc++.h>
using namespace std;

const int R = 505;
const int C = 505;
const int N = 205;
const int MAXVERTICES = 4 * N;
const int INF = (int)1e9;
const int SOURCE = 0;
const int SINK = 1;

#define pb push_back

struct edge{
	int to;
	int cap;
};

struct line{
	int val;
	int r1;
	int r2;
	int c1;
	int c2;
};

vector<line> vertical,horizontal;
vector<edge> elist;
int cnt;
vector<int> adj[MAXVERTICES];
int dist[MAXVERTICES];
int it[MAXVERTICES];
int r,c;
char grid[R][C];

void add(int fr,int to,int cap){
	adj[fr].pb(cnt++);
	adj[to].pb(cnt++);
	
	elist.pb({to,cap});
	elist.pb({fr,0});
}

void reset(){
	for(int i = 0 ; i <= 1 + (int)(vertical.size() + horizontal.size()) ; i++){
		dist[i] = -1;
		it[i] = 0;
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
			if(ret == 0)
				it[now]++;
			else{
				elist[idx].cap -= ret;
				elist[idx ^ 1].cap += ret;
				return ret;
			}	
		}	
	}
	return 0;	
}

void BFS(){
	queue<int> q;
	dist[SOURCE] = 0;
	q.push(0);
	while(!q.empty()){
		int now = q.front();
		q.pop();
		for(int idx : adj[now]){
			int to = elist[idx].to;
			int cap = elist[idx].cap;
			if(cap > 0 && dist[to] == -1){
				dist[to] = dist[now] + 1;
				q.push(to);
			}
		}
	}
}

int maxflow(){
	int mf = 0;
	while(1){
		reset();
		BFS();
		if(dist[SINK] == -1)
			break;
		int ret = augment(SOURCE,INF);	
		while(ret > 0){
			mf += ret;
			ret = augment(SOURCE,INF);
		}
	}
	return mf;
}

void build_graph(){
	for(int i = 0 ; i < vertical.size() ; i++)
		add(SOURCE,2 + i,vertical[i].val);
	for(int i = 0 ; i < horizontal.size() ; i++)
		add(2 + (int)vertical.size() + i,SINK,horizontal[i].val);
	for(int i = 0 ; i < vertical.size() ; i++)
		for(int j = 0 ; j < horizontal.size() ; j++){
			int colVertical = vertical[i].c1;
			int rowHorizontal = horizontal[j].r1;
			if(vertical[i].r1 <= rowHorizontal && rowHorizontal <= vertical[i].r2
				&& horizontal[j].c1 <= colVertical && colVertical <= horizontal[j].c2)
					add(2 + i,2 + (int)vertical.size() + j,INF);
		}		
}

void init(){
	scanf("%d",&r);
	c = r;
	for(int i = 0 ; i < r ; i++)
		scanf("%s",grid[i]);
}

void solve(){
	int sum = 0;
	for(int i = 0 ; i < r ; i++)
		for(int j = 0 ; j < c ; j++)
			if(grid[i][j] == 'T'){
				//bikin ke atas
				int total = 0;
				int iter = i - 1;
				while(iter >= 0 && ('0' <= grid[iter][j] && grid[iter][j] <= '9')){
					total += (int)(grid[iter][j] - '0');
					iter--;
				}
				if(iter == -1 || grid[iter][j] != 'T'){
					sum += total;
					vertical.pb({total,iter + 1,i - 1,j,j});
				}
				//bikin ke bawah
				total = 0;
				iter = i + 1;
				while(iter < r && ('0' <= grid[iter][j] && grid[iter][j] <= '9')){
					total += (int)(grid[iter][j] - '0');
					iter++;
				}
				sum += total;
				vertical.pb({total,i + 1,iter - 1,j,j});

				//bikin ke kiri
				total = 0;
				iter = j - 1;
				while(iter >= 0 && ('0' <= grid[i][iter] && grid[i][iter] <= '9')){
					total += (int)(grid[i][iter] - '0');
					iter--;
				}
				if(iter == -1 || grid[i][iter] != 'T'){
					sum += total;
					horizontal.pb({total,i,i,iter + 1,j - 1});
				}
				//bikin ke kanan
				total = 0;
				iter = j + 1;
				while(iter < c && ('0' <= grid[i][iter] && grid[i][iter] <= '9')){
					total += (int)(grid[i][iter] - '0');
					iter++;
				}
				sum += total;
				horizontal.pb({total,i,i,j + 1,iter - 1});				
			}
	build_graph();		
	int minCut = maxflow();
	printf("%d\n",sum - minCut);
}

int main(){
	init();
	solve();
	return 0;
}