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

const int MAXN = 10005;

struct Person{
    int height;
    int taller;
    
    bool operator <(Person other) const{
        if(height == other.height)
            return taller < other.taller;
        return height < other.height;    
    }
};

Person arr[MAXN];
int tc,n;
int Stree[4 * MAXN];
int ans[MAXN];

void Build(int id,int l,int r){
    Stree[id] = r - l + 1;
    if(l < r){
        int m = (l + r) >> 1, chld = id << 1;
        Build(chld,l,m);
        Build(chld + 1,m + 1,r);
    }
}

void Update(int x){
    int id = 1, l = 1, r = n;
    while(1){
        Stree[id]--;
        if(l == r) break;
        int m = (l + r) >> 1, chld = id << 1;
        if(x <= m)
            id = chld, r = m;
        else
            id = chld + 1, l = m + 1;    
    }
}

int Query(int x){
    int id = 1, l = 1, r = n;
    int tot = 0;
    while(l < r){
        int m = (l + r) >> 1, chld = id << 1;
        if(tot + Stree[chld] >= x)
            id = chld, r = m;
        else
            tot += Stree[chld], id = chld + 1, l = m + 1;        
    }
    return l;
}

int main(){
    //scanf("%d",&tc);
    tc = io();
    for(int T = 1 ; T <= tc ; T++){
        //scanf("%d",&n);
        n = io();
        for(int i = 1 ; i <= n ; i++)
           // scanf("%d",&arr[i].height);
           arr[i].height = io();
        for(int i = 1 ; i <= n ; i++)
            //scanf("%d",&arr[i].taller);
           arr[i].taller = io();
        sort(arr + 1, arr + n + 1);
        Build(1,1,n);
        for(int i = 1 ; i <= n ; i++){
            int pos = Query(arr[i].taller + 1);
            ans[pos] = arr[i].height;
            Update(pos);
        }    
        printf("%d",ans[1]);
        for(int i = 2 ; i <= n ; i++)
            printf(" %d",ans[i]);
        puts("");    
    }
    //puts("ganteng");
    return 0;
}
