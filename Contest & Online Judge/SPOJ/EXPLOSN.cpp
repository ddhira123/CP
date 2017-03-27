#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 100005;
const int INF = 1000000000;

//0 : jujur
//1 : penipu

int dp[N][2][2];
int dp2[N][2];
vector<int> Radj[N];
int nxt[N];
bool vis[N];
int start;
int tc,n;

int solve2(int pos,int stat){
    int &ret = dp2[pos][stat];
    if(ret != -1)
        return ret;
    if(stat == 0){
        ret = 0;
        for(int i = 0 ; i < Radj[pos].size() ; i++){
            int prv = Radj[pos][i];
            ret += solve2(prv,1);
        }
    }
    else{
        ret = 1;
        for(int i = 0 ; i < Radj[pos].size() ; i++){
            int prv = Radj[pos][i];
            ret += min(solve2(prv,0),solve2(prv,1));
        }
    }
    return ret;
}

int solve(int pos,int stat_st,int stat_now){
    if(nxt[pos] == start){
        if(stat_st == 0 && stat_now == 0)
            return INF;
        return solve2(pos,stat_now);
    }
    int &ret = dp[pos][stat_st][stat_now];
    if(ret != -1)
    return ret;
    if(stat_now == 0){
        ret = solve2(pos,stat_now) + solve(nxt[pos],stat_st,1);
    }
    else{
        ret = solve2(pos,stat_now) + min(solve(nxt[pos],stat_st,0),solve(nxt[pos],stat_st,1));
    }
    return ret;
}

int DP(int x){
    while(!vis[x]){
        vis[x] = 1;
        x = nxt[x];
    }
    start = x;
    do{
        int nex = nxt[x];
        for(int i = 0 ; i < Radj[nex].size() ; i++){
            int prv = Radj[nex][i];
            if(prv == x){
                swap(Radj[nex][Radj[nex].size() - 1],Radj[nex][i]);
                Radj[nex].pop_back();
                break;
            }
        }
        x = nex;
    }while(x != start);
    return min(solve(x,0,0),solve(x,1,1));
}

void Reset(){
    memset(vis,0,sizeof vis);
    memset(dp,-1,sizeof dp);
    memset(dp2,-1,sizeof dp2);
    for(int i = 1 ; i <= n ; i++)
        Radj[i].clear();
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        scanf("%d",&n);
        Reset();
        for(int i = 1 ; i <= n ; i++){
            scanf("%d",&nxt[i]);
            Radj[nxt[i]].push_back(i);
        }
        int ans = 0;
        for(int i = 1 ; i <= n ; i++)
            if(!vis[i] && dp2[i][0] == -1 && dp2[i][1] == -1)
                ans += DP(i);
        printf("%d\n",ans);
    }
    return 0;
}
