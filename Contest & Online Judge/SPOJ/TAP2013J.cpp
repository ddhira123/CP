#include <cstdio>
using namespace std;

const int N = 1000;
const int MOD = 1000000007;

void Add(int &x,int y){
    x += y;
    if(x >= MOD) x -= MOD;
}

int dp[N + 5][2];
int tc,n;

void Precompute(){
    dp[0][0] = 1;
    for(int i = 1 ; i <= N ; i++){
        int val = (i & 1) ^ 1;
        for(int j = i ; j <= N ; j++){
            Add(dp[j][1],dp[j - i][1 ^ val]);
            Add(dp[j][0],dp[j - i][0 ^ val]);
        }
    }
}

int main(){
    Precompute();
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        scanf("%d",&n);
        printf("%d\n",dp[n][1]);
    }
    return 0;
}
