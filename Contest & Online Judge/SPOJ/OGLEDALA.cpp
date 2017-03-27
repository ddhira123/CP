#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 100005;

struct data{
    LL len;
    LL cnt;
    int idx;
    
    data(LL _l = 0,LL _c = 0,int _i = 0){
        len = _l;
        cnt = _c;
        idx = _i;
    }
    
    bool operator <(data other) const{
        if(len == other.len) return idx < other.idx;
        return len > other.len;
    }
};

vector<data> v;
LL pos[N],q[N];
int n,k;
LL m;

void build(LL gap,int idx){
    queue<LL> q;
    map<LL,LL> memo;
    if(gap == 0) return;
    q.push(gap);
    memo[gap] = 1;
    while(!q.empty()){
        LL now = q.front();
        LL cur = memo[now];
        q.pop();
        v.push_back(data(now,cur,idx));
        LL nxt2 = (now - 1) / 2LL;
        LL nxt = now - nxt2 - 1;
        if(nxt > 0){
            if(memo.count(nxt) == 0){
                q.push(nxt);
            }
            memo[nxt] += cur;
        }
        if(nxt2 > 0){
            if(memo.count(nxt2) == 0)
                q.push(nxt2);
            memo[nxt2] += cur;    
        }
    }
}

map<LL,LL> dp;
LL tgt;

LL solve(LL x){
    if(x == tgt) return 1;
    if(x < tgt) return 0;
    if(dp.count(x)) return dp[x];
    LL nxt = (x - 1) / 2LL;
    return dp[x] = solve(nxt) + solve(x - nxt - 1);
}

LL query(LL need,data &x){
    LL curlen = pos[x.idx] - pos[x.idx - 1] - 1;
    dp.clear();
    tgt = x.len;
    LL ans = pos[x.idx - 1];
    while(curlen > x.len){
        LL nex = (curlen - 1) / 2LL;
        LL res = solve(nex);
        if(res >= need)
            curlen = nex;
        else{
            need -= res;
            curlen -= (nex + 1);
            ans += (nex + 1);
        }    
    }
    ans += (x.len + 1) / 2LL;
    return ans;
}

void init(){
    scanf("%lld %d %d",&m,&n,&k);
    for(int i = 1 ; i <= n ; i++)
        scanf("%lld",&pos[i]);
    pos[n + 1] = m + 1;
    for(int i = 1 ; i <= n + 1 ; i++)
        build(pos[i] - pos[i - 1] - 1,i);
    sort(v.begin(),v.end());        
}

void answer(){
    int now = 0;
    LL tot = n;
    //printf("size %d\n",(int)v.size());
    for(int i = 1 ; i <= k ; i++){
        scanf("%lld",&q[i]);
        if(q[i] <= (LL)n)
            printf("%lld\n",pos[q[i]]);
        else{
            while(tot + v[now].cnt < q[i]){
                tot += v[now].cnt;
                //printf("now %d tot %lld len %lld\n",now,tot,v[now].len);
                now++;
            }
            printf("%lld\n",query(q[i] - tot,v[now]));
        }    
    }
}

int main(){
    init();
    answer();
    return 0;
}