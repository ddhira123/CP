#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 15;

int arr[N + 5];
long long dp[(1 << N) + 5];
long long fak[N + 5];
int cnt[N + 5];
int n,tc;

void Init(){
    scanf("%d",&n);
    for(int i = 0 ; i < n ; i++)
        cnt[i] = 0;
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&arr[i]);
        cnt[arr[i]]++;
    }
}

void DP(){
    dp[(1 << n) - 1] = 1;
    for(int i = (1 << n) - 2 ; i >= 0 ; i--){
        int pos = __builtin_popcount(i);
        dp[i] = 0;
        for(int j = 0 ; j < n ; j++)
            if((i & (1 << j)) == 0 && arr[pos] != arr[j])
                dp[i] += dp[i | (1 << j)];
    }
    long long ans = dp[0];
    for(int i = 0 ; i < n ; i++)
        ans /= fak[cnt[i]];
    printf("%lld\n",ans);
}

int main(){
    fak[0] = 1;
    for(int i = 1 ; i <= N ; i++)
        fak[i] = fak[i - 1] * (long long)i;
    scanf("%d",&tc);
    while(tc--){
        Init();
        DP();
    }
    return 0;
}
