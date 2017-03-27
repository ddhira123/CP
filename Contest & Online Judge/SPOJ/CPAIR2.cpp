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

const int N  = 50005;
const int MX = 100000;

struct kuery{
    int l;
    int r;
    int id;
};

int   n,m,k;
int   arr[N];
kuery query[N];
int   BIT[MX + 5];
LL    ans[N];
int   sroot;

bool cmp(kuery a,kuery b){
    if(a.l / sroot == b.l / sroot) return a.r < b.r;
    return a.l / sroot < b.l / sroot;
}

void Update(int x,int val){
    for(; x <= MX ; x += x & -x)
        BIT[x] += val;
}

int Query(int x){
    int res = 0;
    for(; x > 0 ; x -= x & -x)
        res += BIT[x];
    return res;    
}

int Get(int x){
    int res = 0;
    int y = max(0,x - k);
    res = Query(y);
    y = min(MX,x + k - 1);
    res += Query(MX) - Query(y);
    return res;
}

void Solve(){
    sort(query,query + m,cmp);
    //int last = -1;
    LL cnt = 0;
    int le = 0,rig = -1;
    for(int i = 0 ; i < m ; i++){
        /*if(query[i].l / sroot > last){
            memset(BIT,0,sizeof BIT);
            cnt = 0;
            for(int j = query[i].l ; j <= query[i].r ; j++){
                cnt += Get(arr[j]);
                Update(arr[j],1);
            }
            le = query[i].l;
            rig = query[i].r;
            last = query[i].l / sroot;
        }*/
        
        while(rig > query[i].r){
            cnt -= Get(arr[rig]);
            Update(arr[rig],-1);
            rig--;
        }
        
        while(rig < query[i].r){
            cnt += Get(arr[rig + 1]);
            Update(arr[rig + 1],1);
            rig++;
        }
        
        while(le < query[i].l){
            cnt -= Get(arr[le]);
            Update(arr[le],-1);
            le++;
        }
        
        while(le > query[i].l){
            cnt += Get(arr[le - 1]);
            Update(arr[le - 1],1);
            le--;
        }
        
        while(le < query[i].l){
            cnt -= Get(arr[le]);
            Update(arr[le],-1);
            le++;
        }
        
        ans[query[i].id] = cnt;
    }
    
    for(int i = 0 ; i < m ; i++)
        printf("%lld\n",ans[i]);
}

int main(){
    scanf("%d %d %d",&n,&m,&k);
    sroot = (int)sqrt(n);
    for(int i = 0 ; i < n ; i++)
        scanf("%d",&arr[i]);
    for(int i = 0 ; i < m ; i++){
        scanf("%d %d",&query[i].l,&query[i].r);
        query[i].l--;   query[i].r--;
        query[i].id = i;
    }    
    sort(query,query + m,cmp);
    Solve();
    //puts("ganteng");
    return 0;
}
