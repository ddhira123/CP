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

int x[N];
LL gold[N],d[N];
vector<LL> uniq;
LL BIT[N];
int n;
LL ans;

void Make(){
    sort(uniq.begin(),uniq.end());
    uniq.erase(unique(uniq.begin(),uniq.end()),uniq.end());
}

int ID(LL z){
    int pos = upper_bound(uniq.begin(),uniq.end(),z) - uniq.begin();
    return pos - 1; 
}

void Update(int z,LL val){
    assert(z > 0);
    for(; z <= uniq.size() ; z += z & -z)
        BIT[z] = min(BIT[z],val);
}

LL Query(int z){
    LL res = INFLL;
    for(; z > 0 ; z -= z & -z)
        res = min(res,BIT[z]);
    return res;    
}

int main(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++){
        scanf("%d %lld %lld",&x[i],&gold[i],&d[i]);
        ans = max(ans,gold[i]);
        gold[i] += gold[i - 1];
        d[i] += d[i - 1];
        uniq.pb(d[i - 1] - (LL)x[i]);
        BIT[i] = INFLL;
    }
    uniq.pb(-INFLL);
    Make();
    for(int i = 1 ; i <= n ; i++){
        int idx = ID(d[i] - (LL)x[i]);
        LL kurang = Query(idx);
        ans = max(ans,gold[i] - kurang);
        idx = ID(d[i - 1] - (LL)x[i]);
        Update(idx,gold[i - 1]);
    }
    printf("%lld\n",ans);
    //puts("ganteng");
    return 0;
}

