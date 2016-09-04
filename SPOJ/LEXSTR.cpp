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

const int MAXN = 100005;

vector<int> pos[MAXN];
vector<int> ch[MAXN];
char s[MAXN];
int par[MAXN];
int tc,q,len;

int finds(int x){
    return x == par[x] ? x : par[x] = finds(par[x]);
}

void uni(int x,int y){
    x = finds(x);
    y = finds(y);
    par[x] = y;
}

void Reset(){
    len = strlen(s);
    //printf("%d\n",len);
    for(int i = 0 ; i < len ; i++){
        par[i] = i;        
        ch[i].clear();
        pos[i].clear();
    }    
}

void Read(){
    scanf("%s",s);
    Reset();
    scanf("%d",&q);
    while(q--){
        int a,b;
        scanf("%d %d",&a,&b);
        uni(a,b);
    }
}

void Process(){
    for(int i = 0 ; i < len ; i++){
        int x = finds(i);
        ch[x].pb(s[i]);
        pos[x].pb(i);
        //printf("%d -> %d\n",i,x);
    }
    for(int i = 0 ; i < len ; i++){
        sort(ch[i].begin(),ch[i].end());
        sort(pos[i].begin(),pos[i].end());
        for(int j = 0 ; j < pos[i].size() ; j++)
            s[ pos[i][j] ] = ch[i][j];
    }
    puts(s);
}

int main(){
    scanf("%d",&tc);
    for(int T = 1 ; T <= tc ; T++){
        Read();
        Process();
    }
    //puts("ganteng");
    return 0;
}

