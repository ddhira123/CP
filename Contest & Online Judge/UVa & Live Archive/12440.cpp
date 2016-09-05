#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

const int N = 100005;

struct node{
    int mins;
    int prop;
    
    node(){
        mins = prop = 0;
    }
};

set<int> s;
node stree[4 * N];
int stek[N];
int saiz;
int prv[N];
int dp[N];
int c[N],h[N];
int n,tc;

void Build(int id,int l,int r){
    stree[id].mins = stree[id].prop = 0;
    if(l < r){
        int chld = id << 1, m = (l + r) >> 1;
        Build(chld,l,m);
        Build(chld + 1,m + 1,r);
    }
}

void Propagate(int id){
    int chld = id << 1;
    for(int i = 0 ; i < 2 ; i++)
        stree[chld + i].prop += stree[id].prop;
    stree[id].prop = 0;    
}

void Update(int id,int l,int r,int x,int y,int val){
    if(x <= l && r <= y)
        stree[id].prop += val;
    else{
        int chld = id << 1, m = (l + r) >> 1;
        Propagate(id);
        if(x <= m)  Update(chld,l,m,x,y,val);
        if(y > m)   Update(chld + 1,m + 1,r,x,y,val);
        stree[id].mins = min(stree[chld].mins + stree[chld].prop,stree[chld + 1].mins + stree[chld + 1].prop);
    }    
}

int Query(int id,int l,int r,int x,int y){
    if(x <= l && r <= y)
        return stree[id].mins + stree[id].prop;
    else{
        int chld = id << 1,m = (l + r) >> 1;
        int res = 2000000001;
        Propagate(id);
        if(x <= m)  res = min(res,Query(chld,l,m,x,y));
        if(y > m)   res = min(res,Query(chld + 1,m + 1,r,x,y));
        return res;
    }    
}

void Build_Prev(){
    s.clear();
    int last = 1;
    for(int i = 1 ; i <= n ; i++){
        while(s.count(c[i]))
            s.erase(c[last++]);
        s.insert(c[i]);
        prv[i] = last;    
        //printf("%d -> %d\n",i,prv[i]);
    }
}

void Solve(){
    Build_Prev();
    Build(1,1,n);
    h[0] = 2000000001;
    saiz = 0;
    for(int i = 1 ; i <= n ; i++){
        while(h[stek[saiz - 1]] <= h[i]){
            Update(1,1,n,stek[saiz - 2] + 1,stek[saiz - 1],-h[stek[saiz - 1]]);
            saiz--;
        }
        stek[saiz++] = i;
        Update(1,1,n,stek[saiz - 2] + 1,stek[saiz - 1],h[stek[saiz - 1]]);
        int res = Query(1,1,n,prv[i],i);
        if(i < n)
            Update(1,1,n,i + 1,i + 1,res);
        dp[i] = res;    
        //printf("%d %d\n",i,dp[i]);
    }
    printf("%d\n",dp[n]);
}

void Init(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++)
        scanf("%d %d",&c[i],&h[i]);
}

int main(){
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        Init();
        printf("Case %d: ",t);
        Solve();
    }
    return 0;
}
