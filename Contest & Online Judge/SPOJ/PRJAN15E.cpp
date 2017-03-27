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
#include <stack>
#include <vector>
#include <bitset>
#include <cassert>

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

const int MAXN = 100005;

int pset[MAXN],sz[MAXN];
pair<int,pii> edge[MAXN];
int n,tc;

int finds(int x){
    return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

LL uni(int x,int y){
    x = finds(x);
    y = finds(y);
    LL res = (LL)sz[x] * (LL)sz[y];
    sz[y] += sz[x];
    pset[x] = y;
    return res;
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        scanf("%d",&n);
        for(int i = 1 ; i < n ; i++){
            pset[i] = i;
            sz[i] = 1;
            scanf("%d %d %d",&edge[i].se.fi,&edge[i].se.se,&edge[i].fi);
        }
        pset[n] = n;
        sz[n] = 1;
        sort(edge + 1, edge + n);
        LL ans = 0;
        for(int i = n - 1 ; i >= 0 ; i--){
            int a = edge[i].se.fi;
            int b = edge[i].se.se;
            LL cost = edge[i].fi;
            ans += cost * uni(a,b);
        }
        ans *= 2LL;
        printf("%lld\n",ans);
    }
    //puts("ganteng");
    return 0;
}
