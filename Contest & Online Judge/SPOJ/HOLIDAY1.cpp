#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 35;

LL fpb(LL a,LL b){
    return b ? fpb(b,a % b) : a;
}

int pmask[N],mask[N];
LL dist[N][N];
LL arr[N];
int n,tgt,k,tc;

bool can(int pos,int sisa,int bm){
    assert(pos >= -1);
    //printf("pos %d sisa %d bm %d\n",pos,sisa,bm);
    if(pos + 1 == sisa){
        if(pos == -1) return 1;
        return ((pmask[pos] & ((1 << (pos + 1)) - 1)) == 0 && (pmask[pos] & bm) == 0); 
    }
    bool ret = 0;
    if(!ret) ret = can(pos - 1,sisa,bm);    
    if(!ret && (mask[pos] & (bm | (1 << pos)) ) == 0) ret = can(pos - 1,sisa - 1,bm | (1 << pos));
    //if(!ret) ret = can(pos - 1,sisa,bm);
    return ret;
}

bool backtrack(int pos,int sisa,int bm){
    assert(pos >= -1);
    if(pos + 1 == sisa){
        if(pos == -1) return 1;
        return ((pmask[pos] & ((1 << (pos + 1)) - 1)) == 0 && (pmask[pos] & bm) == 0);     
    }
    //bool ret = 0;
    /*if((mask[pos] & (bm | (1 << pos)) ) == 0) ret = can(pos - 1,sisa - 1,bm | (1 << pos));
    if(!ret){
        backtrack(pos - 1,sisa,bm);
        printf("%d%c",pos + 1,sisa == k ? '\n' : ' ');
    }
    else
        backtrack(pos - 1,sisa - 1,bm | (1 << pos));*/
    bool ret = 0;
    if(!ret) ret = backtrack(pos - 1,sisa,bm);
    if(ret){
        printf("%d%c",pos + 1,sisa == k ? '\n' : ' ');
    }
    if(!ret && (mask[pos] & (bm | (1 << pos)) ) == 0) ret = backtrack(pos - 1,sisa - 1,bm | (1 << pos));
    //if(!ret){
    //    ret = backtrack(pos - 1,sisa,bm);
    //    if(ret)
    //        printf("%d%c",pos + 1,sisa == k ? '\n' : ' ');
    //}  
    return ret;      
    //printf("pos %d sisa %d bm %d ret %d\n",pos,sisa,bm,ret);
}

void init(){
    scanf("%d %d",&n,&k);
    for(int i = 0 ; i < n ; i++)
        scanf("%lld",&arr[i]);    
}

void gen(LL mi){
    //printf("gen %lld\n",mi);
    for(int i = 0 ; i < n ; i++){
        mask[i] = 0;
        for(int j = 0 ; j < n ; j++)
            if(dist[i][j] < mi)
                mask[i] |= (1 << j);
        pmask[i] = mask[i] | (i ? pmask[i - 1] : 0);
        //printf("%d %d %d\n",i,mask[i],pmask[i]);        
    }
}

void solve(){
    LL mins = (LL)1e18 + 1,maks = 0;
    vector<LL> candidate;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++){
            dist[i][j] = fpb(arr[i],arr[j]);
            mins = min(mins,dist[i][j]);
            maks = max(maks,dist[i][j]);
            candidate.push_back(dist[i][j] + 1);
            candidate.push_back(dist[i][j]);
            //candidate.push_back(dist[i][j] - 1);
        } 
     sort(candidate.begin(),candidate.end());  
     candidate.erase(unique(candidate.begin(),candidate.end()),candidate.end()); 
     LL lo = 0,hi = candidate.size() - 1;
     tgt = (1 << n) - 1;
     k = n - k;
     while(lo < hi){
        LL mi = (lo + hi + 1) / 2LL;
        gen(candidate[mi]);
        //printf("%lld %lld\n",lo,hi);
        if(can(n - 1,k,0))
            lo = mi;
        else
            hi = mi - 1;    
     }      
     gen(candidate[lo]);
     //printf("%lld\n",lo);
     bool temp = backtrack(n - 1,k,0);       
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        init();
        solve();
    }
    return 0;
}