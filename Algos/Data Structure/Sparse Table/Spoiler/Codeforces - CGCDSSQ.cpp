#include <cstdio>
#include <unordered_map>
using namespace std;

const int N = 100005;
const int LOG = 17;

int arr[N];
int ST[N][LOG];
int logg[N];
int query[3 * N];
unordered_map<int,long long> memo;
int n,q;

int fpb(int a,int b){
    return b == 0 ? a : fpb(b,a % b);
}

void build(){
    for(int i = 1 ; i <= n ; i++)
        ST[i][0] = arr[i];
    for(int i = 1 ; (1 << i) <= n ; i++)    
        for(int j = 1 ; j + (1 << i) - 1 <= n ; j++){
            int k = j + (1 << (i - 1));
            ST[j][i] = fpb(ST[j][i - 1],ST[k][i - 1]);
        }
}

void solve(){
    for(int i = 1 ; i <= n ; i++){
        while((1 << logg[i]) <= n) logg[i]++;
        logg[i]--;
    }
    for(int i = 1 ; i <= n ; i++){
        int j = i;
        int val = arr[i];
        while(j <= n){
            int k = j;
            for(int lg = logg[j] ; lg >= 0 ; lg--)
                if(n - k + 1 >= (1 << lg) && fpb(val,ST[k][lg]) == val){
                    k = k + (1 << lg) - 1;
                }
            if(memo.count(val))
                memo[val] += (k - j + 1);
            j = k + 1;
            val = fpb(val,arr[j]);    
        }
    }
}

void init(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++)
        scanf("%d",&arr[i]);
    scanf("%d",&q);
    for(int i = 1 ; i <= q ; i++){
        scanf("%d",&query[i]);
        memo[query[i]] = 0;
    }    
}

int main(){
    init();
    build();
    solve();
    for(int i = 1 ; i <= q ; i++)
        printf("%I64d\n",memo[query[i]]);
    return 0;
}