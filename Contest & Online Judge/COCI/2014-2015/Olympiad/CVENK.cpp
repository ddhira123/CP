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

const int N = 100005;
const int LOG = 30; 

vector<pii> uniq;
int adj[LOG * N][2];
vector<int> lis[LOG * N][2];
int sz[LOG * N];
int dist[LOG * N][2];
LL sub[LOG * N],atas[LOG * N];
int n;
pii arr[N];

int GetAncUp(pii x){
    if(x.se == 0)
        return x.fi;
    int hi = x.se & -x.se;
    hi--;
    hi = min(hi,x.fi);
    int lo = 0;
    while(lo < hi){
        int mi = (lo + hi + 1) / 2;
        if((x.fi - mi) & x.se)
            hi = mi - 1;
        else
            lo = mi;    
    }
    return lo;
}

int GetAncLeft(pii x){
    if(x.fi == 0)
        return x.se;
    int hi = x.fi & -x.fi;
    hi--;
    hi = min(hi,x.se);
    int lo = 0;
    while(lo < hi){
        int mi = (lo + hi + 1) / 2;
        if((x.se - mi) & x.fi)
            hi = mi - 1;
        else
            lo = mi;    
    }
    return lo;
}

void CriticalPoint(int rs,int cs){
    while(rs != 0 || cs != 0){
        uniq.pb(mp(rs,cs));
        //printf("%d %d\n",rs,cs);
        if(rs > 0 && ((rs - 1) & cs) == 0){
            int dis = GetAncUp(mp(rs,cs));
            rs -= dis;
        }
        else{
            int dis = GetAncLeft(mp(rs,cs));
            cs -= dis;
        }
    }
}

void MakeUniq(){
    sort(uniq.begin(),uniq.end());
    uniq.erase(unique(uniq.begin(),uniq.end()),uniq.end());
    for(int i = 0 ; i < uniq.size() ; i++){
        for(int j = 0 ; j < 2 ; j++)
            adj[i][j] = dist[i][j] = INF;   
    }       
}

int ID(pii x){
    return lower_bound(uniq.begin(),uniq.end(),x) - uniq.begin();
}

void Add(int rs,int cs){
    sz[ID(mp(rs,cs))]++;
    while(rs != 0 || cs != 0){
        int idx = ID(mp(rs,cs));
        if(rs > 0 && ((rs - 1) & cs) == 0){
            int dis = GetAncUp(mp(rs,cs));
            if(dis){
                int id2 = ID(mp(rs - dis,cs));
                //adj[id2][0] = min(adj[id2][0],idx);
                //dist[id2][0] = min(dist[id2][0],dis);
                lis[id2][0].pb(idx);
                rs -= dis;
            }
        }
        else{
            int dis = GetAncLeft(mp(rs,cs));
            if(dis){
                int id2 = ID(mp(rs,cs - dis));
                //adj[id2][1] = min(adj[id2][1],idx);
                //dist[id2][1] = min(dist[id2][1],dis);
                lis[id2][1].pb(idx);
                cs -= dis;
            }
        }        
    }
}

void BuildTree(){
    for(int i = 0 ; i < uniq.size() ; i++)
        for(int j = 0 ; j < 2 ; j++)
            if(!lis[i][j].empty()){
                sort(lis[i][j].begin(),lis[i][j].end());
                lis[i][j].erase(unique(lis[i][j].begin(),lis[i][j].end()),lis[i][j].end());
                int idx = lis[i][j][0];
                adj[i][j] = idx;
                dist[i][j] = uniq[idx].fi + uniq[idx].se - uniq[i].fi - uniq[i].se;
                for(int k = 1 ; k < lis[i][j].size() ; k++){
                    idx = lis[i][j][k - 1];
                    int id2 = lis[i][j][k];
                    adj[idx][j] = id2;
                    dist[idx][j] = uniq[id2].fi + uniq[id2].se - uniq[idx].fi - uniq[idx].se;
                }
            }
}

void SolveTree(){
    queue<int> q;
    vector<int> stek;
    q.push(0);
    //for(int i = 0 ; i < uniq.size() ; i++){
    //    printf("R %d C %d bawah %d kanan %d\n",uniq[i].fi,uniq[i].se,adj[i][0],adj[i][1]);
    //}
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        stek.pb(pos);
        for(int i = 0 ; i < 2 ; i++){
            int nxt = adj[pos][i];
            if(nxt != INF){
                q.push(nxt);
            }
        }
    }
    for(int i = stek.size() - 1 ; i >= 0 ; i--){
        int pos = stek[i];
        for(int j = 0 ; j < 2 ; j++){
            int nxt = adj[pos][j];
            if(nxt == INF) continue;
            sub[pos] += (LL)sz[nxt] * (LL)dist[pos][j] + sub[nxt];
            sz[pos] += sz[nxt];
        }
    }
    LL ans = sub[0];
    for(int i = 0 ; i < stek.size() ; i++){
        int pos = stek[i];
        ans = min(ans,sub[pos] + atas[pos]);
        for(int j = 0 ; j < 2 ; j++){
            int nxt = adj[pos][j];
            if(nxt == INF) continue;
            atas[nxt] = sub[pos] - sub[nxt] - (LL)(sz[nxt]) * (LL)(dist[pos][j]);
            atas[nxt] += atas[pos];
            atas[nxt] += (LL)(n - sz[nxt]) * (LL)(dist[pos][j]); 
        }
    }
    printf("%lld\n",ans);
}

int main(){
    scanf("%d",&n);
    uniq.pb(mp(0,0));
    for(int i = 0 ; i < n ; i++){
        scanf("%d %d",&arr[i].fi,&arr[i].se);
        CriticalPoint(arr[i].fi,arr[i].se);
    }
    MakeUniq();
    for(int i = 0 ; i < n ; i++)
        Add(arr[i].fi,arr[i].se);
    BuildTree();    
    SolveTree();    
    //puts("ganteng");
    return 0;
}

