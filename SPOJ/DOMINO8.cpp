#include <bits/stdc++.h>
using namespace std;

#ifdef _WIN32
    #define getchar_unlocked getchar
#endif

#define g getchar_unlocked

inline int io(){
    register char c;
    while(1){
        c = g();
        if(c != '\n' && c != ' ') break;
    }
    int res = 0, sign = 1;
    if(c=='-') sign = -1;
    else       res = c-'0';
    while(1){
        c = g();
        if(c == ' ' || c == '\n' || c == EOF) break;
        res = (res << 3) + (res << 1) + c - '0';
    }
    return res * sign;
}

const int N = 2001;
const int N2 = N * N;
const int INF = (int)2e9;

int dr[4] = {0,-1,0,1};
int dc[4] = {-1,0,1,0};

struct edge{
	int from;
	int to;
	int flow;
	int cost;
};

vector<edge> edgeList;
vector<int> adj[N2 + 5];
int saiz;
int arr[N][N];

int dist[N2];
bool inQ[N2];
int prv[N2];

int n,k;

void addEdge(int from,int to,int flow,int cost) {
	edgeList.push_back((edge){from,to,flow,cost});
	edgeList.push_back((edge){to,from,0,-cost});
	
	adj[from].push_back(saiz++);
	adj[to].push_back(saiz++);
}

bool BFS() {
	for(int i = 0 ; i <= n * n + 5 ; i++)
		dist[i] = INF;
	dist[0] = 0;
	queue<int> q;
	q.push(0);
	
	while(!q.empty()) {
		int now = q.front();
		inQ[now] = 0;
		q.pop();
		
		for(int idx : adj[now]) {
			edge nex = edgeList[idx];
			int to = nex.to;
			int flow = nex.flow;
			int cost = nex.cost;
			
			if(flow > 0 && dist[now] + cost < dist[to]) {
				dist[to] = dist[now] + cost;
				prv[to] = idx;
				
				if(!inQ[to]) {
					q.push(to);
					inQ[to] = 1;
				}
			}
		}
	}
	
	return dist[2] != INF;		
}

int minCostMaxFlow() {
	int ret = 0;
	
	while(BFS()) {
		int now = 2;
		int mins = INF;
		int cost = dist[2];
		
		while(now != 0) {
			int idx = prv[now];
			int from = edgeList[idx].from;
			int flow = edgeList[idx].flow;
			
			mins = min(mins,flow);
			now = from;
		}
		
		ret += mins * cost;
		
		now = 2;
		while(now != 0) {
			int idx = prv[now];
			int from = edgeList[idx].from;
			
			edgeList[idx].flow -= mins;
			edgeList[idx ^ 1].flow += mins;
			
			now = from;
		}
	}
	
	return ret;
}

void buildGraph() {
	addEdge(0,1,k,0);
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++)
			if((i + j) % 2 == 0) {
				addEdge(1,i * n + j + 3,1,0);
				for(int iter = 0 ; iter < 4 ; iter++) {
					int nr = i + dr[iter];
					int nc = j + dc[iter];
					
					if(nr >= 0 && nc >= 0 && nr < n && nc < n) {
						addEdge(i * n + j + 3,nr * n + nc + 3,1,-(arr[i][j] + arr[nr][nc]));
					}
				}
			}
			else {
				addEdge(i * n + j + 3,2,1,0);
			}
}

int main() {
	int tot = 0;
	//scanf("%d %d",&n,&k);
	n = io(); k = io();
	for(int i = 0 ; i < n ; i++)
		for(int j = 0 ; j < n ; j++) {
			//scanf("%d",&arr[i][j]);
			arr[i][j] = io();
			tot += arr[i][j];
		}
	buildGraph();
	int ans = tot + minCostMaxFlow();
	printf("%d\n",ans);	
	return 0;
}
