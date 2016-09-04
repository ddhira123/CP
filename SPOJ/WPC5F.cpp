#include <cstdio>
using namespace std;

/*3 0 -> 0 2, 1 1, 2 0 // kalo harus turun
2 1 -> 0 2, 1 1
1 2 -> 0 2
0 3 ->

0 3 -> 2 0, 1 1, 0 2 // kalo harus naik
1 2 -> 2 0, 1 1
2 1 -> 2 0*/

const int MOD = 1000000009;
const int N = 705;

int dp[N][N];
bool flag[N];
int n,k;

void Add(int &x,int y){
    x += y;
    if(x >= MOD) x -= MOD;
    if(x < 0)    x += MOD;
}

void Init(){
    scanf("%d %d",&n,&k);
    for(int i = 1 ; i <= k ; i++){
        int a;
        scanf("%d",&a);
        flag[a] = 1;
    }
}

void Solve(){
    dp[0][0] = 1;
    for(int i = 1 ; i < n ; i++){
        int pos = n - i + 1;
        int all = 0;
        for(int j = 0 ; j < i ; j++)
            Add(all,dp[j][i - j - 1]);
        int l,r;    
        if(flag[pos]){ // turun
            l = i - 1,r = 0;
            for(int j = i ; j >= 0 ; j--){
                dp[j][i - j] = all;
                Add(all,-dp[l][r]);
                l--;
                r++;
            }
        }    
        else{
            l = 0, r = i - 1;
            for(int j = 0 ; j <= i ; j++){
                dp[j][i - j] = all;
                Add(all,-dp[l][r]);
                l++;
                r--;
            }
        }
    }
    int ans = 0;
    for(int i = 0 ; i < n ; i++)
        Add(ans,dp[i][n - i - 1]);
    printf("%d\n",ans);    
}

int main(){
    Init();
    Solve();
    return 0;
}
