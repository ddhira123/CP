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
//nyampah

const int N = 300005;

LL A[N];
int n,q;
LL m;

priority_queue<pll> pq;

LL Update(){
    pll ret = pq.top();
    pq.pop();
    LL st = -ret.se;
    LL en = st + ret.fi - 1;
    LL mid = (st + en) / 2LL;
    if(mid - st > 0)
        pq.push(mp(mid - st,-st));
    if(en - mid > 0)
        pq.push(mp(en - mid,-(mid + 1)));    
    return mid;
}

int main(){
    scanf("%lld %d %d",&m,&n,&q);
    for(int i = 1 ; i <= n ; i++){
        scanf("%lld",&A[i]);
        if(A[i] - A[i - 1] - 1 > 0)
            pq.push(mp(A[i] - A[i - 1] - 1,-(A[i - 1] + 1)));
    }
    if(m - A[n] > 0)
        pq.push(mp(m - A[n],-(A[n] + 1)));
    int it = n;
    for(int i = 1 ; i <= q ; i++){
        LL b;
        scanf("%lld",&b);
        assert(b < N);
        if(b <= n)
            printf("%lld\n",A[b]);
        else{
            while(it + 1 < b){
                LL tmp = Update();
                it++;
            }
            LL res = Update();
            printf("%lld\n",res);
            it++;
        }    
    }
    //puts("ganteng");
    return 0;
}

