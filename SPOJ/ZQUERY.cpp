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

const int N = 50005;

struct kuery{
    int l;
    int r;
    int id;
};

int sum[N];
int ans[N];
kuery query[N];
int st[2 * N], en[2 * N];
pii arr[N];
int cnt[2 * N];
priority_queue<int> pq;
int n,m,sroot;

bool cmp(kuery a,kuery b){
    if(a.l / sroot == b.l / sroot) return a.r < b.r;
    return a.l / sroot < b.l / sroot;
}

void Add(int pos,int opt){ // 0 : front, 1 : back
    int x = sum[pos];
    if(st[x] <= en[x])
        cnt[arr[en[x]].se - arr[st[x]].se]--;
    if(opt == 0)    
        st[x]--;
    else
        en[x]++;    
    int diff = arr[en[x]].se - arr[st[x]].se;
    cnt[diff]++;
    if(cnt[diff] == 1)
        pq.push(diff);    
}

void Delete(int x,int opt){
    int diff = arr[en[x]].se - arr[st[x]].se;
    cnt[diff]--;
    if(opt == 0)
        st[x]++;
    else
        en[x]--;    
    if(st[x] <= en[x]){
        diff = arr[en[x]].se - arr[st[x]].se;
        cnt[diff]++;
        if(cnt[diff] == 1)
            pq.push(diff);
    }
}

void Init(){
    scanf("%d %d",&n,&m);
    sroot = (int)sqrt(n);
    sum[0] = n;
    arr[0] = mp(n,0);
    for(int i = 1 ; i <= n ; i++){
        int a;
        scanf("%d",&a);
        sum[i] = sum[i - 1] + a;
        arr[i] = mp(sum[i],i);
        //printf("%d SUM %d\n",i,sum[i]);
    }
    for(int i = 0 ; i < m ; i++){
        scanf("%d %d",&query[i].l,&query[i].r);
        query[i].l--;
        query[i].id = i;
    }
    
    sort(arr,arr + n + 1);
    st[arr[0].fi] = 0;
    en[arr[0].fi] = -1;
    for(int i = 1 ; i <= n ; i++)
        if(arr[i].fi != arr[i - 1].fi){
            st[arr[i].fi] = i;
            en[arr[i].fi] = i - 1;
        }
}

void Solve(){
    sort(query,query + m,cmp);
    int le = 0;
    int rig = -1;
    for(int i = 0 ; i < m ; i++){
        //printf("QUERY %d %d\n",query[i].l,query[i].r);
        while(rig < query[i].r){
            Add(rig + 1,1);
            rig++;
            //printf("ADD RIG %d %d TOP %d\n",le,rig,pq.top());
        }
        
        while(rig > query[i].r){
            Delete(sum[rig],1);
            rig--;
            //printf("DEL RIG %d %d TOP %d\n",le,rig,pq.top());
        }
        
        while(le < query[i].l){
            Delete(sum[le],0);
            le++;
            //printf("DEL LE %d %d TOP %d\n",le,rig,pq.top());            
        }
        
        while(le > query[i].l){
            Add(le - 1,0);
            le--;
            //printf("ADD LE %d %d TOP %d\n",le,rig,pq.top());            
        }
        
        while(cnt[pq.top()] == 0) pq.pop();
        ans[query[i].id] = pq.top();
    }
    for(int i = 0 ; i < m ; i++)
        printf("%d\n",ans[i]);
}

int main(){
    Init();
    Solve();
    //puts("ganteng");
    return 0;
}

