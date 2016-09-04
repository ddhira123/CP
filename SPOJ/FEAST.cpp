#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 55;
const int S = 5005;

pair<int,int> arr[N];
long long dp[S];
int n,s,tc;

void Add(int x){
    for(int i = s ; i >= x ; i--)
        dp[i] += dp[i - x];
}

int main(){
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        scanf("%d %d",&s,&n);
        for(int i = 0 ; i < n ; i++)
            scanf("%d %d",&arr[i].second,&arr[i].first);
        sort(arr,arr + n);
        memset(dp,0,sizeof dp);
        dp[0] = 1;
        int it = n;
        long long ans = 0;
        for(int i = s ; i >= 1 ; i--)
            if(s % i == 0){
                while(it > 0 && arr[it - 1].first >= i){
                    it--;
                    Add(arr[it].second);
                }    
                ans += dp[s / i];  
            }    
        printf("Case %d: %lld\n",t,ans);    
    }
    return 0;
}
