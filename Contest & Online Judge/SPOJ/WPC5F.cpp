#include <cstdio>
#include <cstring>
using namespace std;

const int MOD = 1000000009;
const int N = 705;

bool flag[N];
int dp[N][N];
int n,k;

int solve(int less,int more){
    int pos = n - less - more + 1;
    if(pos == n + 1)
        return 1;
    if((flag[pos] && less == 0) || (!flag[pos] && more == 0))
        return 0;
    int &ret = dp[less][more];
    if(ret != -1)
        return ret;
    if(flag[pos])
        ret = solve(less - 1,more) + solve(less - 1,more + 1);
    else
        ret = solve(less,more - 1) + solve(less + 1,more - 1);
    if(ret >= MOD)
        ret -= MOD;
    return ret;
}

void Init(){
    scanf("%d %d",&n,&k);
    for(int i = 1 ; i <= k ; i++){
        int x;
        scanf("%d",&x);
        flag[x] = 1;
    }
}

void DP(){
    memset(dp,-1,sizeof dp);
    int ans = 0;
    for(int i = 1 ; i <= n ; i++){
        ans += solve(i - 1,n - i);
        if(ans >= MOD)
            ans -= MOD;
    }
    printf("%d\n",ans);
}

int main(){
    Init();
    DP();
    return 0;
}
