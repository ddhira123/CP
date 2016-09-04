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

int cnt[N];
int SA[N],tmpS[N];
int RA[N],tmpR[N];
int phi[N],PLCP[N],LCP[N];

pii arr[N];
int sz[N],pset[N];

char s[N];
int len;

int Finds(int x){
    return x == pset[x] ? x : pset[x] = Finds(pset[x]);
}

void Merge(int x,int y){
    x = Finds(x);
    y = Finds(y);
    if(x == y) return;
    sz[x] += sz[y];
    pset[y] = x;
}

void Radix_Sort(int k){
    int maxx = max(len,300);
    for(int i = 0 ; i < maxx ; i++)
        cnt[i] = 0;
    for(int i = 0 ; i  < len ; i++)
        cnt[i + k < len ? RA[i + k] : 0]++;
    
    int tot = 0;
    for(int i = 0 ; i < maxx ; i++){
        int tmp = cnt[i];
        cnt[i] = tot;
        tot += tmp;
    } 
    
    for(int i = 0 ; i < len ; i++)
        tmpS[cnt[SA[i] + k < len ? RA[SA[i] + k] : 0]++] = SA[i];
    for(int i = 0 ; i < len ; i++)
        SA[i] = tmpS[i];           
}

void Build_Suffix_Array(){
    for(int i = 0 ; i < len ; i++){
        SA[i] = i;
        RA[i] = s[i];
    }
    for(int lg = 1 ; lg < len ; lg <<= 1){
        Radix_Sort(lg);
        Radix_Sort(0);
        int tot = 0;
        tmpR[SA[0]] = 0;
        for(int i = 1 ; i < len ; i++)
            tmpR[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && SA[i] + lg < len && SA[i - 1] + lg < len 
                            && RA[SA[i] + lg] == RA[SA[i - 1] + lg]) ? tot : ++tot;
        
        for(int i = 0 ; i < len ; i++)
            RA[i] = tmpR[i];
        if(RA[SA[len - 1]] == len - 1) break;                        
    }
}

void Build_LCP(){
    phi[SA[0]] = -1;
    for(int i = 1 ; i < len ; i++)
        phi[SA[i]] = SA[i - 1];
    for(int i = 0, l = 0 ; i < len ; i++){
        if(phi[i] == -1)
            PLCP[i] = 0;
        else{
            while(s[i + l] == s[phi[i] + l]) l++;
            PLCP[i] = l;
            l = max(0,l - 1);
        }    
    }
    for(int i = 0 ; i < len ; i++)
        LCP[i] = PLCP[SA[i]];
}

void Print(){
    for(int i = 0 ; i < len ; i++){
        printf("Index %d\n",i);
        printf("%d %s\n",SA[i],s + SA[i]);
        printf("LCP %d\n",LCP[i]);
        puts("");
    }
    DEBUG;
}

LL Solve(){
    for(int i = 0 ; i < len ; i++){
        pset[i] = i;
        sz[i] = 1;
        arr[i] = mp(LCP[i],i);
    }
    sort(arr,arr + len);
    //for(int i = 0 ; i < len ; i++)
    //    printf("SA %d PLCP %d\n",arr[i].se,arr[i].fi);
    LL ans = len - 1;
    for(int i = len - 1 ; i >= 0 ; i--)
        if(arr[i].fi == 0)
            break;
        else{
            //printf("UNION %d %d\n",arr[i].se,arr[i].se - 1);  
            Merge(arr[i].se,arr[i].se - 1);
            ans = max(ans,(LL)arr[i].fi * (LL)sz[Finds(arr[i].se)]);
        }    
    return ans;    
}

int main(){
    scanf("%s",s);
    len = strlen(s);
    s[len++] = '$';
    s[len] = '\0';
    Build_Suffix_Array();
    Build_LCP();
    //Print();
    printf("%lld\n",Solve());
    //puts("ganteng");
    return 0;
}

