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

#define pb push_back
#define fi first
#define se second
#define mp make_pair

const int N = 100005;

typedef pair<int,int> pii;

map<pii,long long> memo;
pii edge[2 * N];
int cnt[2 * N];
int deg[N];
vector<int> adj[N];
int n,m,q;
int tc;

void init(){
    for(int i = 1 ; i <= n ; i++){
        adj[i].clear();
        deg[i] = 0;
    }    
    memo.clear();
    n = io(); m = io();
    for(int i = 1 ; i <= m ; i++){
        int u,v;
        //scanf("%d %d",&u,&v);
        u = io(); v = io();
        adj[u].pb(v);
        adj[v].pb(u);
        deg[u]++;
        deg[v]++;
        if(u > v) swap(u,v);
        edge[i] = mp(u,v);
    }

    sort(edge + 1,edge + m + 1);
    int tot = 0;
    for(int i = 1 ; i <= m ;){
        int j = i;
        while(j <= m && edge[i] == edge[j]) j++;
        edge[tot] = edge[i];
        cnt[tot++] = j - i;
        i = j;
    }
    m = tot;
}

int get(int u,int v){
    if(u > v) swap(u,v);
    int id = lower_bound(edge,edge + m,mp(u,v)) - edge;
    if(id == m || edge[id] != mp(u,v)) return 0;
    return cnt[id];
}

void solve(){
    q = io();
    for(int i = 1 ; i <= q ; i++){
        int u,v;
        u = io(); v = io();
        if(u == v){
            printf("0 1\n");
            continue;    
        }
        int temp = get(u,v);
        if(temp){
            printf("1 %d\n",temp);
            continue;
        }
        if(deg[u] > deg[v]) swap(u,v);
        if(deg[u] == deg[v] && u > v) swap(u,v);
        long long res = 0;
        //printf("u %d v %d\n",u,v);
        if(memo.find(mp(u,v)) != memo.end()){
            //puts("udah");
            res = memo[mp(u,v)];
        }
        else{
            //puts("counting");
            for(int j = 0 ; j < deg[u] ; j++){
                int x = adj[u][j];
                temp = get(v,x);
                res += temp;
            }
        }
        memo[mp(u,v)] = res;
        if(res == 0)
            puts("The pair of cities are not connected or too far away.");
        else
            printf("2 %lld\n",res);    
    }
}

int main(){
    scanf("%d",&tc);
    //tc = io();
    for(int t = 1 ; t <= tc ; t++){
        printf("Case #%d:\n",t);
        init();
        solve();
    }
    return 0;
}