#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

int n,l,tc;
int dp[N];
int dp2[N];
vector<int> Radj[N],adj[N];
bool vis[N];

int solve(int now){
    if(now == 1)
        return 1;
    int &ret = dp[now];
    if(ret != -1)
        return ret;
    ret = 0;
    for(int prv : Radj[now])
        ret = (ret + solve(prv)) % 100000;
    return ret;            
}

int solve2(int now){
    if(now == n)
        return 1;
    int &ret = dp2[now];
    if(ret != -1)
        return ret;
    ret = 0;
    for(int nxt : adj[now])
        ret = (ret + solve2(nxt)) % 100000;
    return ret;            
}

void reset(){
    for(int i = 1 ; i <= n ; i++){
        Radj[i].clear();
        adj[i].clear();
        dp[i] = -1;
        dp2[i] = -1;
        vis[i] = 0;
    }
}

int dfs(int now){
    if(now == 1 || vis[now])
        return 0;    
    vis[now] = 1;
    int ret = ((long long)solve(now) * (long long)solve2(now)) % 100000LL;
    for(int prv : Radj[now])
        ret = (ret + dfs(prv)) % 100000;
    //printf("now %d ret %d\n",now,ret);    
    return ret;            
}

int main(){
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        scanf("%d %d",&n,&l);
        reset();
        for(int i = 1 ; i <= l ; i++){
            int u,v;
            scanf("%d %d",&u,&v);
            Radj[v].push_back(u);
            adj[u].push_back(v);
        }
        int ans = dfs(n);
        printf("Case %d: %d %d\n",t,ans,solve(n));    
    }
    return 0;
}
