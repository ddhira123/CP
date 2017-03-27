#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <bitset>
#include <cassert>
//Because defining using namespace std is too mainstream
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<string,string> pss;
typedef pair<int,double> pid;
typedef pair<int,LL> pil;
typedef pair<LL,LL> pll;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define TIE cin.tie(0)
#define INF 2000000001
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")

#ifdef _WIN32
    #define getchar_unlocked getchar
#endif

#define g getchar_unlocked

int dx8[8]={-1,-1,0,1,1,1,0,-1},dx4[4]={-1,0,1,0};
int dy8[8]={0,-1,-1,-1,0,1,1,1},dy4[4]={0,-1,0,1};

inline void open(string name){
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

inline void close(){
    fclose(stdin);
    fclose(stdout);
}

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

///////////////////////////////////////////////////
//////            End of Template            /////
/////////////////////////////////////////////////

const int N = 205;

struct Edge{
    int from;
    int to;
    int flow;
    
    Edge(){}
    
    Edge(int a,int b,int c){
        from = a;
        to = b;
        flow = c;
    }
};

int In(int x){
    return (x << 1);
}

int Out(int x){
    return (x << 1) + 1;
}

int n,m;
int st,en;
vector<Edge> Edgelist;
int cnt;
vector<int> adj[2 * N];
int dist[2 * N];
int cost[N];
int it[2 * N];

void Add_Edge(int _fr,int _to,int _fl){
    adj[_fr].pb(cnt++);
    Edgelist.pb(Edge(_fr,_to,_fl));
    
    adj[_to].pb(cnt++);
    Edgelist.pb(Edge(_to,_fr,0));    
}

void Init(){
    scanf("%d %d",&n,&m);
    scanf("%d %d",&st,&en);
    for(int i = 1 ; i <= n ; i++){
        scanf("%d",&cost[i]);
        Add_Edge(In(i),Out(i),cost[i]);
    }
    for(int i = 1 ; i <= m ; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        Add_Edge(Out(a),In(b),INF);
        Add_Edge(Out(b),In(a),INF);
    }
}

void BFS(){
    for(int i = 1 ; i <= Out(n) ; i++)
        dist[i] = -1;
    dist[In(st)] = 0;
    queue<int> q;
    q.push(In(st));
    
    while(!q.empty()){
        int now = q.front();
        q.pop();
        for(int i = 0 ; i < adj[now].size() ; i++){
            int idx = adj[now][i];
            int nxt = Edgelist[idx].to;
            int ff = Edgelist[idx].flow;
            if(dist[nxt] == -1 && ff > 0){
                dist[nxt] = dist[now] + 1;
                q.push(nxt);
            }
        }
    }    
}

int Augment(int pos,int mins){
    if(mins == 0) return 0;
    if(pos == Out(en)) return mins;
    for(; it[pos] < adj[pos].size() ; ){
        int idx = adj[pos][it[pos]];
        int nxt = Edgelist[idx].to;
        int ff = Edgelist[idx].flow;
        if(ff == 0 || dist[nxt] != dist[pos] + 1){
            it[pos]++;
            continue;
        }
        ff = Augment(nxt,min(mins,ff));
        if(ff > 0){
            Edgelist[idx].flow -= ff;
            Edgelist[idx ^ 1].flow += ff;
            return ff;
        }
        else
            it[pos]++;
    }
    return 0;
}

void MinCut(){
    while(1){
        BFS();
        if(dist[Out(en)] == -1) break;
        for(int i = 1 ; i <= Out(n) ; i++)
            it[i] = 0;
        int start = In(st);    
        while(Augment(start,INF) > 0){}  
    }
}

void Solve(){
    for(int i = 1 ; i <= Out(n) ; i++)
        dist[i] = -1;
    dist[In(st)] = 0;
    queue<int> q;
    q.push(In(st));
    while(!q.empty()){
        int now = q.front();
        q.pop();
        for(int i = 0 ; i < adj[now].size() ; i++){
            int idx = adj[now][i];
            int nxt = Edgelist[idx].to;
            int ff = Edgelist[idx].flow;
            if(ff > 0 && dist[nxt] == -1){
                dist[nxt] = dist[now] + 1;
                q.push(nxt);
            }
        }
    }
    bool spasi = 0;
    for(int i = 1 ; i <= n ; i++)
        if(dist[In(i)] != -1 && dist[Out(i)] == -1){
            if(spasi)
                printf(" ");
            else
                spasi = 1;
            printf("%d",i);        
        }    
    puts("");    
}

int main(){
    Init();
    MinCut();
    Solve();
    //puts("ganteng");
    return 0;
}
