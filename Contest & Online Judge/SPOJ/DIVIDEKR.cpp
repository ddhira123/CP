#include <cstdio>
using namespace std;

const int N = 30;

int mask[N];
int ans,bm_ans;
int n,n2,m;

void rec(int pos,int cnt,int bm1,int bm2,int tot){
    if(tot >= ans)
        return;
    else if(cnt == n2){
        for(int i = pos ; i <= n ; i++)
            tot += (__builtin_popcount(mask[i] & bm1));
        if(tot < ans){
            ans = tot;
            bm_ans = bm1;
        }    
    }
    else if(pos - cnt - 1 == n2){
        for(int i = pos ; i <= n ; i++){
            tot += (__builtin_popcount(mask[i] & bm2));
            bm1 |= (1 << i);
        }    
        if(tot < ans){
            ans = tot;
            bm_ans = bm1;
        }        
    }
    else{
        rec(pos + 1,cnt + 1,bm1 | (1 << pos),bm2,tot + __builtin_popcount(mask[pos] & bm2));
        rec(pos + 1,cnt,bm1,bm2 | (1 << pos),tot + __builtin_popcount(mask[pos] & bm1));
    }
}

int main(){
    scanf("%d %d",&n,&m);
    n2 = n / 2;
    for(int i = 0 ; i < m ; i++){
        int u,v;
        scanf("%d %d",&u,&v);
        mask[u] |= (1 << v);
        mask[v] |= (1 << u);
    }
    ans = 1000000000;
    rec(2,1,2,0,0);
    //printf("%d\n",bm_ans);
    int cnt = 0;
    for(int i = 1 ; i <= n ; i++)
        if(bm_ans & (1 << i)){
            cnt++;
            printf("%d%c",i,cnt == n2 ? '\n' : ' ');
        }
    return 0;
}