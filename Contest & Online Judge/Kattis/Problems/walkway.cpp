#include <bits/stdc++.h>
using namespace std;

const int N = 1000;

typedef pair<int,int> pii;
#define fi first
#define se second

vector<pii> adj[N + 5];
int dist[N + 5];
int n;
int st,en;

void dijkstra(){
    for(int i = 1 ; i <= N ; i++)
        dist[i] = 2100000000;
    dist[st] = 0;
    priority_queue<pii> pq;
    pq.push({0,st});
    dist[st] = 0;
    while(!pq.empty()){
        pii now = pq.top();
        pq.pop();
        now.fi = -now.fi;
        if(now.fi != dist[now.se]) continue;
        //printf("%d %d\n",now.se,now.fi);
        for(pii nxt : adj[now.se]){
            int nex = nxt.fi;
            int ncos = now.fi + nxt.se;
            if(ncos < dist[nex]){
                dist[nex] = ncos;
                pq.push({-ncos,nex});
            }
        }
    }   
}

int main(){
    scanf("%d",&n);
    while(n){
        for(int i = 1 ; i <= N ; i++)
            adj[i].clear();
        for(int i = 0 ; i < n ; i++){
            int a,b,h;
            scanf("%d %d %d",&a,&b,&h);
            adj[a].push_back({b,(a + b) * h});
            adj[b].push_back({a,(a + b) * h});
        }   
        scanf("%d %d",&st,&en);
        dijkstra();
        int ans = dist[en];
        //printf("%d\n",ans);
        printf("%d.%02d\n",ans / 100,ans % 100);
        scanf("%d",&n);
    }
    return 0;
} 

