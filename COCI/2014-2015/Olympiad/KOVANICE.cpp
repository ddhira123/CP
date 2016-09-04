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

const int N = 300005;

int pset[N];
int dist[N];
int ans[N];
vector<int> adj[N],Radj[N];
int deg[N];
vector<pii> les;
char s[105];
int n,m,v;

int finds(int x){
    return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

void uni(int x,int y){
    x = finds(x);
    y = finds(y);
    if(x == y) return;
    pset[y] = x;
}

void Init(){
    scanf("%d %d %d",&m,&n,&v);
    for(int i = 1 ; i <= n ; i++)
        pset[i] = i,dist[i] = 1;
    for(int i = 0 ; i < v ; i++){
        scanf("%s",s);
        int len = strlen(s);
        int j = 0;
        while(j < len){
            if(s[j] == '=' || s[j] == '<')
                break;
            j++;    
        }
        int a = 0,b = 0;
        for(int k = 0 ; k < j ; k++)
            a = 10 * a + (int)(s[k] - '0');
        for(int k = j + 1 ; k < len ; k++)
            b = 10 * b + (int)(s[k] - '0');
        if(s[j] == '=')  
            uni(a,b);
        else
            les.pb(mp(a,b));          
    }    
}

void MakeAdj(){
    for(int i = 0 ; i < les.size() ; i++){
        les[i].fi = finds(les[i].fi);
        les[i].se = finds(les[i].se);
        adj[les[i].fi].pb(les[i].se);
        Radj[les[i].se].pb(les[i].fi);
        deg[les[i].se]++;
    }
}

void BFSDistance(){
    queue<int> q;
    for(int i = 1 ; i <= n ; i++)
        if(finds(i) == i && deg[i] == 0)
            q.push(i);
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        for(int i = 0 ; i < adj[pos].size() ; i++){
            int nxt = adj[pos][i];
            dist[nxt] = max(dist[nxt],dist[pos] + 1);
            deg[nxt]--;
            if(deg[nxt] == 0)
                q.push(nxt);
        }
    }        
}

void BFSColor(int st){
    queue<int> q;
    ans[st] = m;
    q.push(st);
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        /*for(int i = 0 ; i < adj[pos].size() ; i++){
            int nxt = adj[pos][i];
            if(ans[nxt] == 0){
                ans[nxt] = ans[pos] + 1;
                q.push(nxt); 
            }
        }*/
        for(int i = 0 ; i < Radj[pos].size() ; i++){
            int prv = Radj[pos][i];
            if(ans[prv] == 0 && dist[prv] + 1 == dist[pos]){
                ans[prv] = ans[pos] - 1;
                q.push(prv);
            }
        }
    }
}

void Solve(){
    MakeAdj();
    BFSDistance();
    for(int i = 1 ; i <= n ; i++)
        if(finds(i) == i && dist[i] == m && ans[i] == 0)
            BFSColor(i);
    for(int i = 1 ; i <= n ; i++){
        int x = finds(i);
        if(ans[x] == 0)
            printf("?\n");
        else
            printf("K%d\n",ans[x]);    
    }        
}

int main(){
    Init();
    Solve();
    //puts("ganteng");
    return 0;
}

