#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

typedef long long LL;
typedef pair<int,int> pii;

const int N = 100005;
const LL INF = 4000000000000000000LL;

vector<int> adj[N];
LL best[2 * N];
int sz[N];
int worst[N];
vector<int> appear;
vector<pair<int,LL> > tmp;
queue<int> q;
bool vis[N];
int con[N];
int arr[N];
LL ans;
int n;

void DFS1(int pos,int prev){
    sz[pos] = 1;
    worst[pos] = 0;
    appear.pb(pos);
    for(int i = 0 ; i < adj[pos].size() ; i++){
        int nxt = adj[pos][i];
        if(vis[nxt] || prev == nxt) continue;
        DFS1(nxt,pos);
        worst[pos] = max(worst[pos],sz[nxt]);
        sz[pos] += sz[nxt];
    }
}

void DFS2(int pos,int prev,int ncon,LL cnt){
    cnt += arr[pos];    
    ncon += con[pos];
    ans = max(ans,best[-ncon + n] + cnt);
    tmp.pb(mp(ncon,cnt));
    for(int i = 0 ; i < adj[pos].size() ; i++){
        int nxt = adj[pos][i];
        if(vis[nxt] || prev == nxt) continue;
        DFS2(nxt,pos,ncon,cnt);
    }        
}

void Process(int x){
    appear.clear();
    tmp.clear();
    DFS1(x,0);
    int root = x;
    for(int i = 0 ; i < appear.size() ; i++){
        int lol = appear[i];
        worst[lol] = max(worst[lol],sz[x] - sz[lol]);
        if(worst[lol] < worst[root])
            root = lol;
    }
    vis[root] = 1;
    int last = 0;
    best[con[root] + n] = arr[root];
    for(int i = 0 ; i < adj[root].size() ; i++){
        int nxt = adj[root][i];
        if(vis[nxt]) continue;
        DFS2(nxt,root,0,0);
        while(last < tmp.size()){
            tmp[last].fi += con[root];
            tmp[last].se += arr[root];
            best[tmp[last].fi + n] = max(best[tmp[last].fi + n],tmp[last].se);
            last++;
        }
    }
    best[con[root] + n] = -INF;
    for(int i = 0 ; i < tmp.size() ; i++){
        int ncon = tmp[i].fi;
        best[ncon + n] = -INF;
    }
    for(int i = 0 ; i < adj[root].size() ; i++){
        int nxt = adj[root][i];
        if(!vis[nxt]) q.push(nxt);
    }
}

void Init(){
    scanf("%d",&n);
    char c = getchar();
    for(int i = 0 ; i <= 2 * n ; i++)
        best[i] = -INF;
    for(int i = 1 ; i <= n ; i++){
        c = getchar();
        if(c == 'B') con[i] = 1;
        else         con[i] = -1;
    }
    for(int i = 1 ; i <= n ; i++)
        scanf("%d",&arr[i]);
    for(int i = 2 ; i <= n ; i++){
        int a;
        scanf("%d",&a);
        adj[a].pb(i);
        adj[i].pb(a);
    }        
}

void Solve(){
    ans = -INF;
    q.push(1);
    while(!q.empty()){
        int now = q.front();
        q.pop();
        Process(now);
    }    
    assert(ans != -INF);
    printf("%lld\n",ans);
}

int main(){
    Init();
    Solve();
    return 0;
}

