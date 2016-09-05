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
#define Lovely using
#define my_angel namespace
#define Ayase_tan std

Lovely my_angel Ayase_tan;

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

const int MAXN = 50005;

int stree[4 * MAXN];
int tc,n;

void Build(int id,int l,int r){
    if(l == r)
        stree[id] = 1;
    else{
        int m = (l + r) >> 1, chld = id << 1;
        Build(chld,l,m);
        Build(chld + 1,m + 1,r);
        stree[id] = stree[chld] + stree[chld + 1];
    }   
}

void Update(int id,int l,int r,int x){
    if(l == r)
        stree[id] = 0;
     else{
        int m = (l + r) >> 1, chld = id << 1;
        if(x <= m) Update(chld,l,m,x);
        else       Update(chld + 1,m + 1,r,x);
        stree[id] = stree[chld] + stree[chld + 1];
     }   
}

int Query(int k){
    int id = 1, l = 1, r = n;
    int cnt = 0;
    while(l < r){
        int m = (l + r) >> 1, chld = id << 1;
        if(cnt + stree[chld] >= k){
            r = m;
            id = chld;
        }
        else{
            cnt += stree[chld];
            l = m + 1;
            id = chld + 1;
        }
    }
    return l;
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        scanf("%d",&n);
        Build(1,1,n);
        int a;
        for(int i = 1 ; i <= n ; i++){
            scanf("%d",&a);
            int res = Query(a + 1);
            printf("%d%c",res,i == n ? '\n' : ' ');
            Update(1,1,n,res);
        }
    }
    //puts("ganteng");
    return 0;
}

