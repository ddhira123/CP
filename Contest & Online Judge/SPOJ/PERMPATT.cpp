#include <bits/stdc++.h>
using namespace std;

#ifdef _WIN32
#define getchar_unlocked getchar
#endif

#define g getchar_unlocked

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

#define fi first
#define se second
#define mp make_pair

typedef pair<int,int> pii;

const int N = 100001;

int n,tc;
int BIT[N + 5];
int pair_i2[N + 5];
int pair_i3[N + 5];
int stree[4 * N];
int ans;
pii arr[N  + 5];

void b_update(int x,int val){
    for(; x <= n ; x += x & -x){
        BIT[x] = max(BIT[x],val);
        //printf("x %d bit %d val %d\n",x,BIT[x],val);
    }    
}

int b_query(int x){
    int res = 0;
    for(; x ; x -= x & -x)
        res = max(res,BIT[x]);
    return res;    
}

void build(int id,int l,int r){
    stree[id] = 0;
    if(l < r){
        int m = (l + r) >> 1;
        int chld = id << 1;
        build(chld,l,m);
        build(chld + 1,m + 1,r);
    }    
}

void update(int id,int l,int r,int x,int val){
    if(l == r)
        stree[id] = val;
    else{
        int m = (l + r) >> 1;
        int chld = id << 1;
        if(x <= m) update(chld,l,m,x,val);
        else       update(chld + 1,m + 1,r,x,val);
        stree[id] = max(stree[chld],stree[chld + 1]);
    }    
}

void query2(int id,int l,int r,int lim){
    while(l < r){
        int m = (l + r) >> 1;
        int chld = id << 1;
        if(stree[chld + 1] > lim){
            id = chld + 1;
            l = m + 1;
        }
        else{
            assert(stree[chld] > lim);
            id = chld;
            r = m;
        }
    }
    ans = l;
}

void query(int id,int l,int r,int x,int y,int lim){
    if(x <= l && r <= y){
        if(ans == 0 && stree[id] > lim)
            query2(id,l,r,lim);
    }
    else{
        int m = (l + r) >> 1;
        int chld = (id) << 1;
        if(y > m) query(chld + 1,m + 1,r,x,y,lim);
        if(ans == 0 && x <= m) query(chld,l,m,x,y,lim); 
    }
}

int main(){
    //tc = io();
    scanf("%d",&tc);
    while(tc--){
        //n = io();
        scanf("%d",&n);
        for(int i = 1 ; i <= n ; i++){
            scanf("%d",&arr[i].fi);
            //arr[i].fi = io();
            arr[i].se = i;
            BIT[i] = 0;
        }    
        //cari i4 untuk tiap i2
        for(int i = n ; i >= 1 ; i--){
            pair_i2[arr[i].fi] = b_query(n - arr[i].fi + 1);
            //printf("i2 %d %d\n",arr[i].fi,pair_i2[arr[i].fi]);
            b_update(n - arr[i].fi + 1,i);
        }
        //cari i2 untuk tiap i3
        sort(arr + 1,arr + n + 1);
        build(1,1,n);
        for(int i = n ; i >= 1 ; i--){
            //assert(arr[i].fi == i);
            int idx = arr[i].se;
            ans = 0;
            query(1,1,n,1,idx,idx);
            pair_i3[arr[i].fi] = ans;
            //printf("pair_i3 %d %d\n",arr[i].fi,pair_i3[arr[i].fi]);
            update(1,1,n,idx,pair_i2[arr[i].fi]);
        }
        //cari i3 untuk tiap i1
        build(1,1,n);
        bool ok = 0;
        for(int i = n ; i >= 1 ; i--){
            int idx = arr[i].se;
            ans = 0;
            query(1,1,n,idx,n,idx);
            //printf("i %d ans %d\n",i,ans);
            if(ans){
                ok = 1;
                break;
            }
            //printf("updated %d %d\n",idx,pair_i3[arr[i].fi]);
            update(1,1,n,idx,pair_i3[arr[i].fi]);
        }
        printf("%s\n",ok ? "yes" : "no");
    }
    return 0;
}