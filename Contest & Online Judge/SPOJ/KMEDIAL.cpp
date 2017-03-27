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

/*eq[i] - eq[j] > bal[j] - bal[i]
eq[i] + bal[i] > eq[j] + bal[j]

bal[i] <= bal[j], maka eq[i] > eq[j]

eq[i] - eq[j] > bal[i] - bal[j]
eq[i] - bal[i] > eq[j] - bal[j]

bal[i] >= bal[j], maka eq[i] > eq[j]*/

const int N = 100005;

pii eqbal[N];
int arr[N];
int BIT[2 * N];
int lim;
int tc,n,k;

void Update(int x,int val){
    for(; x <= lim ; x += x & -x)
        BIT[x] += val;
}

int Query(int x){
    int res = 0;
    for(; x > 0 ; x -= x & -x)
        res += BIT[x];
    return res;    
}

bool cmp1(pii a,pii b){
    if(a.se == b.se)
        return a.fi >= b.fi;
    return a.se < b.se;    
}

bool cmp2(pii a,pii b){
    if(a.se == b.se)
        return a.fi <= b.fi;
    return a.se > b.se;    
}

LL Process(){
    int mins = INF, maks = -INF;
    for(int i = 0 ; i <= n ; i++){
        mins = min(mins,arr[i]);
        maks = max(maks,arr[i]);
    }
    mins = (-mins) + 1;
    lim = maks + mins;
    for(int i = 0 ; i <= n ; i++){
        arr[i] += mins;
        Update(arr[i],1);
    }
    LL ans = 0;
    for(int i = 0 ; i <= n ; i++){
        Update(arr[i],-1);
        ans += Query(arr[i] - 1);
    }
    return ans;
}

int main(){
    //scanf("%d",&tc);
    tc = io();
    while(tc--){
        //scanf("%d %d",&n,&k);
        n = io(); k = io();
        int eq = 0,bal = 0;
        eqbal[0] = mp(0,0);
        for(int i = 1 ; i <= n ; i++){
            int a;
            //scanf("%d",&a);
            a = io();
            if(a < k)
                bal--;
            else if(a == k)
                eq++;
            else
                bal++;
            eqbal[i] = mp(eq,bal);            
        }
        LL ret = 0;
        sort(eqbal,eqbal + n + 1,cmp1);
        for(int i = 0 ; i <= n ; i++)
            arr[i] = eqbal[i].fi + eqbal[i].se;
        ret += Process();
        //sort(eqbal,eqbal + n + 1,cmp2);
        reverse(eqbal,eqbal + n + 1);
        for(int i = 0 ; i <= n ; i++)
            arr[i] = eqbal[i].fi - eqbal[i].se;
        ret += Process();
        printf("%lld\n",ret);        
    }
    //puts("ganteng");
    return 0;
}
