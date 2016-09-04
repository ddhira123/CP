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

const int MAXN = 300005;

struct Range_Segment_Tree{
    int RMQ[4 * MAXN];
    int Lazy[4 * MAXN];
    int n;
    
    Range_Segment_Tree(){}
    
    void Build(int sz,int x){
        n = sz;
        Build(1,1,n,x);
    }
    
    void Build(int id,int l,int r,int x){
        RMQ[id] = x;
        Lazy[id] = INF;
        int m = (l + r) >> 1;
        int chld = id << 1;
        if(l < r){
            Build(chld,l,m,x);
            Build(chld + 1,m + 1,r,x);
        }
    }
    
    void Propagate(int id,int l,int r){
        int m = (l + r) >> 1, chld = id << 1;
        for(int i = 0 ; i < 2 ; i++){
            RMQ[chld + i] = min(RMQ[chld + i],Lazy[id]);
            Lazy[chld + i] = min(Lazy[chld + i],Lazy[id]);
        }
        Lazy[id] = INF;
    }
    
    void UpdateRange(int l,int r,int val){
        UpdateRange(1,1,n,l,r,val);
    }
    
    void UpdateRange(int id,int l,int r,int x,int y,int val){
        if(x <= l && r <= y){
            RMQ[id] = min(RMQ[id],val);
            Lazy[id] = min(Lazy[id],val);
        }
        else{
            int m = (l + r) >> 1,chld = id << 1;
            if(Lazy[id] != INF)
                Propagate(id,l,r);
            if(x <= m)
                UpdateRange(chld,l,m,x,y,val);
            if(y > m)
                UpdateRange(chld + 1,m + 1,r,x,y,val);    
        }
    }
    
    int Query(int x){
        int id = 1;
        int l = 1;
        int r = n;
        while(l < r){
            int m = (l + r) >> 1,chld = id << 1;
            if(Lazy[id] != INF)
                Propagate(id,l,r);
            if(x <= m){
                id = chld;
                r = m;
            }    
            else{
                id = chld + 1;
                l = m + 1;
            }
        }
        return RMQ[id];
    }
    
};

struct DP_Segment_Tree{
    int DP[4 * MAXN];
    int n;
    
    DP_Segment_Tree(){}
    
    void Build(int sz){
        n = sz;
        Build(1,1,n);
    }
    
    void Build(int id,int l,int r){
        DP[id] = INF;
        int m = (l + r) >> 1;
        int chld = id << 1;
        if(l < r){
            Build(chld,l,m);
            Build(chld + 1,m + 1,r);
        }
    }
    
    void Update(int x,int val){
        Update(1,1,n,x,val);
    }
    
    void Update(int id,int l,int r,int x,int val){
        if(l == r){
            DP[id] = val;
        }
        else{
            int m = (l + r) >> 1,chld = id << 1;
            if(x <= m)
                Update(chld,l,m,x,val);
            else
                Update(chld + 1,m + 1,r,x,val);  
            DP[id] = min(DP[chld],DP[chld + 1]);      
        }
    }
    
    int Query(int l,int r){
        return Query(1,1,n,l,r);
    }
    
    int Query(int id,int l,int r,int x,int y){
        if(x <= l && r <= y)
            return DP[id];
        else{
            int m = (l + r) >> 1, chld = id << 1;
            int res = INF;
            if(x <= m)
                res = min(res,Query(chld,l,m,x,y));
            if(y > m)
                res = min(res,Query(chld + 1,m + 1,r,x,y));
            return res;        
        }    
    }
};

Range_Segment_Tree Rtree;
DP_Segment_Tree DPtree;
int tc,n,d;
int arr[MAXN];
int uniq[MAXN];
int len;

void Make(){
    sort(uniq + 1,uniq + n + 1);
    len = unique(uniq + 1,uniq + n + 1) - (uniq) - 1;
}

int ID(int x){
    return lower_bound(uniq + 1,uniq + len + 1,x) - uniq;
}

void BuildAll(){
    DPtree.Build(n + 1);
    DPtree.Update(n + 1,0);
    Make();
    Rtree.Build(len,n + 1);
}

int main(){
    scanf("%d",&tc);
    for(int T = 1  ; T <= tc ; T++){
        scanf("%d %d",&n,&d);
        for(int i = 1 ; i <= n ; i++){
            scanf("%d",&arr[i]);
            uniq[i] = arr[i];
        }
        BuildAll();
        for(int i = n ; i >= 1 ; i--){
            int idx = ID(arr[i]);
            int farthest = Rtree.Query(idx);
            int ans = 1 + DPtree.Query(i,farthest);
            DPtree.Update(i,ans);
            
            int kanan = ID(arr[i] + d + 1);
            if(kanan <= len)
                Rtree.UpdateRange(kanan,len,i);
            
            int kiri = ID(arr[i] - d) - 1;
            if(kiri >= 1)
                Rtree.UpdateRange(1,kiri,i);    
                
            //printf("%d id %d far %d ans %d kanan %d kiri %d\n",i,idx,farthest,ans,kanan,kiri);
        }
        printf("%d\n",DPtree.Query(1,1));
    }
    //puts("ganteng");
    return 0;
}

