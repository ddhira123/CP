#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back

vector<pii> adj[N];
int dp[N];
int dist[N];
int n,m;

int dijkstra(int s,int t){
    for(int i = 0 ; i <= n ; i++)
        dist[i] = 1000000000;
    dist[s] = 0;
    dp[s] = 1;
    priority_queue<pii> pq;
    pq.push({0,s});
    while(!pq.empty()){
        pii now = pq.top();
        pq.pop();
        now.fi = -now.fi;
        if(now.fi != dist[now.se]) continue;
        for(pii nxt : adj[now.se]){
            int nex = nxt.fi;
            int ncos = now.fi + nxt.se;
            if(ncos < dist[nex]){
                dist[nex] = ncos;
                dp[nex] = dp[now.se];
                pq.push({-ncos,nex});
            }
            else if(ncos == dist[nex])
                dp[nex] += dp[now.se];
        }
    }   
    return dp[t];
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0 ; i < m ; i++){
        int u,v,cost;
        scanf("%d %d %d",&u,&v,&cost);
        adj[u].pb({v,cost});
    }
    int s,t;
    scanf("%d %d",&s,&t);
    printf("%d\n",dijkstra(s,t));
    return 0;
}

