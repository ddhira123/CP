#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair

const int N = 18 + 2;
const LL INF = (LL)4e18;

int old_node[N];
int old_kiri[N],old_kanan[N];
int restricted_node[N];
int restricted_kiri[N],restricted_kanan[N];
int old_val[N],restricted_val[1 << N];
int restricted_suf[N][N];
int old_pos[N];
int tc,n,m;
int cnt[N];

LL pwr[N];
int num[1 << N];

void precompute(){
    pwr[0] = 1;
    for(int i = 1 ; i < N ; i++)
        pwr[i] = pwr[i - 1] * 10LL;
    for(int i = 0 ; i < N ; i++)
        num[1 << i] = i;   
    memset(restricted_val,-1,sizeof restricted_val);     
}

void init(){
    scanf("%d %d",&n,&m);
    assert(0 <= m && m <= 18);
    for(int i = 0 ; i < n ; i++)
        scanf("%d",&old_node[i]);
    for(int i = 0 ; i < n ; i++){
        scanf("%d %d",&old_kiri[i],&old_kanan[i]);
        //pwr[i] = (i ? pwr[i - 1] * 10LL : 1);
    } 
    for(int i = 0 ; i < m ; i++)
        scanf("%d",&restricted_node[i]);
    for(int i = 0 ; i < m ; i++)  
        scanf("%d %d",&restricted_kiri[i],&restricted_kanan[i]);     
}

void make_old(){
    int root = (1 << n) - 1;
    for(int i = 0 ; i < n ; i++){
        if(old_kiri[i] != -1){
            assert(root & (1 << old_kiri[i]));
            root ^= (1 << old_kiri[i]);
        }
        if(old_kanan[i] != -1){
            assert(root & (1 << old_kanan[i]));
            root ^= (1 << old_kanan[i]);
        }
    }
    assert(__builtin_popcount(root) == 1);
    for(int i = 0 ; i < n ; i++)
        if(root & (1 << i)){
            root = i;
            break;
        }
    queue<pii> q;
    q.push(mp(root,1));
    int ctr = 0;
    while(!q.empty()){
        int now = q.front().fi;
        int pos = q.front().se;
        q.pop();
        old_pos[ctr] = pos;
        old_val[ctr++] = old_node[now];
        //printf("ctr %d pos %d val %d\n",ctr - 1,pos,old_node[now]);
        if(old_kiri[now] != -1)
            q.push(mp(old_kiri[now],2 * pos));
        if(old_kanan[now] != -1)
            q.push(mp(old_kanan[now],2 * pos + 1));    
    }    
}

void make_restricted(int stat = 0){
    int root = (1 << m) - 1;
    for(int i = 0 ; i < m ; i++){
        if(restricted_kiri[i] != -1){
            assert(root & (1 << restricted_kiri[i]));
            root ^= (1 << restricted_kiri[i]);
        }
        if(restricted_kanan[i] != -1){
            assert(root & (1 << restricted_kanan[i]));
            root ^= (1 << restricted_kanan[i]);
        }
    }
    assert(__builtin_popcount(root) == 1);
    for(int i = 0 ; i < m ; i++)
        if(root & (1 << i)){
            root = i;
            break;
        }    
    queue<pii> q;
    q.push(mp(root,1));
    int ctr = 0;
    while(!q.empty()){
        int now = q.front().fi;
        int pos = q.front().se;
        q.pop();
        if(!stat)
            restricted_val[pos] = restricted_node[now];
        else
            restricted_val[pos] = -1;    
        //printf("pos %d val %d\n",pos,restricted_node[now]);
        if(restricted_kiri[now] != -1)
            q.push(mp(restricted_kiri[now],2 * pos));
        if(restricted_kanan[now] != -1)
            q.push(mp(restricted_kanan[now],2 * pos + 1));    
    }   
}

void make_suffix_sum(){
    memset(restricted_suf[n],0,sizeof restricted_suf[n]);
    for(int i = n - 1 ; i >= 0 ; i--){
        for(int j = 0 ; j <= 9 ; j++)
            restricted_suf[i][j] = restricted_suf[i + 1][j];
        int tree_pos = old_pos[i];
        int restricted = restricted_val[tree_pos];
        if(restricted != -1) 
            restricted_suf[i][restricted]++;   
        //for(int j = 0 ; j <= 9 ; j++)
            //printf("%d %d : %d\n",i,j,restricted_suf[i][j]);    
    }
}

bool cek(int x){
    int sum = 0;
    for(int i = 0 ; i <= 9 ; i++)
        sum += cnt[i];
    for(int i = 0 ; i <= 9 ; i++){
        //printf("i %d %d %d\n",i,sum - cnt[i],restricted_suf[x][i]);
        if(sum - cnt[i] < restricted_suf[x][i])
            return 0;
    }        
    return 1;            
}

LL backtrack(LL sum,int x){
    if(x == n) return abs(sum);
    int lol = old_val[x];
    bool udah = 0;
    LL res = INF;
    if(sum < 0)
        for(int j = 0 ; j <= 9 && !udah ; j++){
            if(cnt[j]){
            LL add = pwr[n - 1 - x] * (LL)(old_val[x] - j); 
            cnt[j]--;
            if(cek(x + 1) && restricted_suf[x + 1][j] - restricted_suf[x][j] != -1){
                //printf("sum %lld x %d j %d\n",sum,x,j);
                res = backtrack(sum + add,x + 1);
                udah = 1;
            }      
            cnt[j]++;
        }
    }    
    else   
        for(int j = 9 ; j >= 0 && !udah ; j--)
            if(cnt[j]){
            LL add = pwr[n - 1 - x] * (LL)(old_val[x] - j); 
            cnt[j]--;
            if(cek(x + 1) && restricted_suf[x + 1][j] - restricted_suf[x][j] != -1){
                //printf("sum %lld x %d j %d\n",sum,x,j);
                res = backtrack(sum + add,x + 1);
                udah = 1;
            }      
            cnt[j]++;
        }    
    assert(udah);    
    //printf("sum %lld x %d\n",sum,x);    
    return res;    
}

LL solve(){
    memset(cnt,0,sizeof cnt);
    for(int i = 0 ; i < n ; i++)
        cnt[old_node[i]]++;
    if(!cek(0)) return -1;
    int i = 0;
    while(i < n){
        int lol = old_val[i];
        cnt[lol]--;
        if(!cek(i + 1) || restricted_suf[i + 1][lol] - restricted_suf[i][lol] == -1){
            cnt[lol]++;
            break;
        }
        i++;
    }    
    //printf("i %d\n",i);
    if(i == n) return 0;
    LL ans = INF;
    for(int j = 0 ; j <= 9 ; j++)
        if(cnt[j]){
            LL add = pwr[n - 1 - i] * (LL)(old_val[i] - j);
            cnt[j]--;
            if(cek(i + 1) && restricted_suf[i + 1][j] - restricted_suf[i][j] != -1){
                LL temp = backtrack(add,i + 1);
                ans = min(ans,temp);
                //printf("start j %d temp %lld\n",j,temp);
            }    
            cnt[j]++;    
        }
    assert(ans != INF);    
    return ans;    
}

int main(){
    precompute();
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        init();
        make_old();
        make_restricted();
        make_suffix_sum();
        printf("%lld\n",solve());
        make_restricted(1);
    }
    return 0;
}