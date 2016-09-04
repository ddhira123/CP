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
#define INF 1000000000
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

int flow[2 * N][2 * N];
vector<int> adj[2 * N];
int it[2 * N];
int dist[2 * N];
int n,m,l,tc;

void Reset(){
    for(int i = 1 ; i <= n + m + 4 ; i++){
        adj[i].clear();
        for(int j = 1 ; j <= n + m + 4 ; j++)
            flow[i][j] = 0;
    }
}

void Add(int fr,int to,int fl){
    adj[fr].pb(to);
    flow[fr][to] = fl;
    
    adj[to].pb(fr);
}

void Init(){
    scanf("%d %d %d",&l,&n,&m);
    Reset();
    Add(n + m + 1,n + m + 2,l);
    Add(n + m + 3,n + m + 4,INF);
    for(int i = 1 ; i <= n ; i++){
        int a;
        scanf("%d",&a);
        Add(n + m + 2,i,a);
    }
    for(int i = 1 ; i <= m ; i++){
        int a;
        scanf("%d",&a);
        Add(n + i,n + m + 3,a);
    }
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++){
            int a;
            scanf("%d",&a);
            Add(i,n + j,a);
        }
}

void BFS(){
    for(int i = 1 ; i <= n + m + 4 ; i++)
        dist[i] = -1;
    queue<int> q;    
    dist[n + m + 1] = 0;
    q.push(n + m + 1);
    while(!q.empty()){
        int now = q.front();
        q.pop();
        for(int i = 0 ; i < adj[now].size() ; i++){
            int nxt = adj[now][i];
            if(flow[now][nxt] > 0 && dist[nxt] == -1){
                dist[nxt] = dist[now] + 1;
                q.push(nxt);
            }
        }
    }    
}

int Augment(int now,int mins){
    if(mins == 0) return 0;
    if(now == n + m + 4) return mins;
    for(; it[now] < adj[now].size() ; ){
        int nxt = adj[now][it[now]];
        if(flow[now][nxt] == 0 || dist[nxt] != dist[now] + 1){
            it[now]++;
            continue;
        }
        int res = Augment(nxt,min(mins,flow[now][nxt]));
        if(res > 0){
            flow[now][nxt] -= res;
            flow[nxt][now] += res;
            return res;
        }
        else
            it[now]++;
    }
    return 0;
}

int MaxFlow(){
    int ans = 0;
    while(1){
        BFS();
        if(dist[n + m + 4] == -1)
            break;
        for(int i = 1 ; i <= n + m + 4 ; i++)
            it[i] = 0;    
        int res = Augment(n + m + 1,INF);
        while(res > 0){
            ans += res;
            res = Augment(n + m + 1,INF);
        }    
    }
    return ans;
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        Init();
        printf("%d\n",MaxFlow());
    }
    //puts("ganteng");
    return 0;
}

