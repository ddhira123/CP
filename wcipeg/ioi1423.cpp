#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;

const int N = 100005;
const int LOG = 20;

struct state{
    int l;
    int r;
    int optL;
    int optR;
    
    state(int _l = 0,int _r = 0,int _optL = 0,int _optR = 0){
        l = _l;
        r = _r;
        optL = _optL;
        optR = _optR;
    }
};

struct node{
    LL sum;
    int cnt;
    
    node(){
        sum = cnt = 0;
    }
};

//ke kanan balik terus ke kiri
LL ans_right[3 * N];
LL ans_left[3 * N];
node stree[4 * N];
queue<state> q[LOG];
int idx[N];
int inve[N];
int attraction[N];

int n,d,start;

void Build(int id,int l,int r){
    stree[id].sum = stree[id].cnt = 0;
    if(l < r){
        int m = (l + r) >> 1;
        int chld = id << 1;
        Build(chld,l,m);
        Build(chld + 1,m + 1,r);
    }
}

void Update(int id,int l,int r,int x){
    if(l == r){
        stree[id].cnt = 1;
        stree[id].sum = attraction[idx[l]];
    }
    else{
        int m = (l + r) >> 1;
        int chld = id << 1;
        if(x <= m) Update(chld,l,m,x);
        else       Update(chld + 1,m + 1,r,x);
        stree[id].cnt = stree[chld].cnt + stree[chld + 1].cnt;
        stree[id].sum = stree[chld].sum + stree[chld + 1].sum;
    }
}

LL Query(int kth){
    if(kth == 0) return 0;
    LL ret = 0;
    int lo = 0;
    int hi = n - 1;
    int id = 1;
    while(lo < hi){
        int m = (lo + hi) >> 1;
        int chld = id << 1;
        if(stree[chld].cnt >= kth){
            hi = m;
            id = chld;
        }
        else{
            ret += stree[chld].sum;
            kth -= stree[chld].cnt;
            lo = m + 1;
            id = chld + 1;
        }
    }
    ret += stree[id].sum;
    return ret;
}

void Solve_Right(){
    memset(ans_right,0,sizeof ans_right);
    q[0].push(state(0,d,start,n - 1));
    for(int i = 0 ; !q[i].empty() ; i++){
        Build(1,0,n - 1);
        int last_update = start;
        while(!q[i].empty()){
            state now = q[i].front();
            q[i].pop();
            int mi = (now.l + now.r) >> 1;
            int optM = now.optL;
            LL best = -1;
            for(int j = now.optL ; j <= now.optR ; j++){
                while(last_update < j){
                    Update(1,0,n - 1,inve[last_update + 1]);
                    last_update++;
                }    
                int sisa = mi - 2 * (j - start);
                sisa = min(sisa,j - start);
                if(sisa < 0) break;
                LL ret = Query(sisa);
                if(ret > best){
                    best = ret;
                    optM = j;
                }
            }
            ans_right[mi] = best;
            if(now.l < now.r){
                q[i + 1].push(state(now.l,mi,now.optL,optM));
                q[i + 1].push(state(mi + 1,now.r,optM,now.optR));
            }
        }
    }
}

void Solve_Left(){
    memset(ans_left,0,sizeof ans_left);
    q[0].push(state(0,d,0,start));
    for(int i = 0 ; !q[i].empty() ; i++){
        Build(1,0,n - 1);
        int last_update = start + 1;
        while(!q[i].empty()){
            state now = q[i].front();
            q[i].pop();
            int optM = now.optR;
            LL best = -1;
            int mi = (now.l + now.r) >> 1;
            for(int j = now.optR ; j >= now.optL ; j--){
                while(last_update > j){
                    Update(1,0,n - 1,inve[last_update - 1]);
                    last_update--;
                }
                int sisa = mi - (start - j);
                sisa = min(sisa,start - j + 1);
                if(sisa < 0) break;
                LL ret = Query(sisa);
                if(ret > best){
                    best = ret;
                    optM = j;
                }
            }
            ans_left[mi] = best;
            //printf("mi %d best %lld optM %d\n",mi,best,optM);
            if(now.l < now.r){
                q[i + 1].push(state(now.l,mi,optM,now.optR));
                q[i + 1].push(state(mi + 1,now.r,now.optL,optM));
            }
        }
    }
}

bool cmp(int a,int b){
    if(attraction[a] == attraction[b])
        return a < b;
    return attraction[a] > attraction[b];   
}

void Init(){
    scanf("%d %d %d",&n,&start,&d);
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&attraction[i]);
        idx[i] = i;
    }
}

void Solve(){
    LL res = 0;
    for(int times = 0 ; times < 2 ; times++){
        sort(idx,idx + n,cmp);
        for(int i = 0 ; i <  n ; i++){
            inve[idx[i]] = i;
        }
        Solve_Left();
        Solve_Right();
        for(int i = 0 ; i <= d ; i++){
            res = max(res,ans_left[i] + ans_right[d - i]);
            //printf("i %d l %lld r %lld\n",i,ans_left[i],ans_right[d - i]);
        }    
        reverse(attraction,attraction + n);
        start = n - start - 1;    
    }
    printf("%lld\n",res);
}

int main(){
    Init();
    Solve();
    return 0;
}
