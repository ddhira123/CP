#include <cstdio>
using namespace std;

const int N = 1005;

int sum[N][N];
int n;

int query(int bot,int right,int top,int left){
    return sum[bot][right] - sum[top - 1][right] - sum[bot][left - 1] + sum[top - 1][left - 1];
}

void init(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++){
            scanf("%d",&sum[i][j]);
            sum[i][j] ^= 1;
            sum[i][j] = sum[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
}

void solve(){
    int best = 0;
    int cnt = 0;
    for(int top = 1 ; top <= n ; top++)
        for(int left = 1 ; left <= n ; left++)
            if(query(top,left,top,left) == 0){
                int lo = 1;
                int hi = n - (top > left ? top : left) + 1;
                while(lo < hi){
                    int mi = (lo + hi + 1) >> 1;
                    int bot = top + mi - 1;
                    int right = left + mi - 1;
                    if(query(bot,right,top,left))
                        hi = mi - 1;
                    else
                        lo = mi;    
                }
                if(lo > best)
                    best = lo,cnt = 1;
                else if(lo == best)
                    cnt++;    
            }
    long long ans = best;
    ans *= cnt;        
    printf("%lld\n",ans);          
}

int main(){
    init();
    solve();
    return 0;
}
