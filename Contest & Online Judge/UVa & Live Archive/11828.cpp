#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1001;
const LL MOD = (LL)1e9;

int n,k;
LL C[N][N];
char s[N + 5];
LL po[26][N];;
int sama;
LL cntsama[N],cntbeda[N];

void precompute(){
    po[2][0] = 1;
    po[24][0] = 1;
    po[25][0] = 1;
    for(int i =1 ; i < N ; i++){
        po[2][i] = (po[2][i - 1] << 1) % MOD;
        po[24][i] = (po[24][i - 1] * 24LL) % MOD;
        po[25][i] = (po[25][i - 1] * 25LL) % MOD;
    }    
    for(int i = 0 ; i < N ; i++){
        C[i][0] = 1;
        for(int j = 1 ; j <= i ; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }    
}

void init(){
    scanf("%d %d",&n,&k);
    scanf("%s",s);
}

LL solve(){
    memset(cntsama,0,sizeof cntsama);
    memset(cntbeda,0,sizeof cntbeda);
    sama = 0;
    for(int i = 0 ; i < n / 2 ; i++)
        if(s[i] == s[n - i - 1])
            sama++;
    for(int i = 0 ; i <= sama ; i++){
        int diff = 2 * i;
        if(diff > k) break;
        cntsama[diff] = (C[sama][i] * po[25][i]) % MOD;
    } 
    int beda = n / 2 - sama;
    for(int i = 0 ; i <= beda ; i++){
        int diff = 2 * i + (beda - i);
        if(diff > k) break;
        cntbeda[diff] = (C[beda][beda - i] * po[2][beda - i]) % MOD;
        cntbeda[diff] = (cntbeda[diff] * po[24][i]) % MOD;
    }
    for(int i = 1 ; i <= k ; i++)
        cntsama[i] = (cntsama[i] + cntsama[i - 1]) % MOD;       
    LL ans = 0;    
    if(n % 2 == 0){
        for(int i = 0 ; i <= k ; i++)
            ans = (ans + cntbeda[i] * cntsama[k - i]) % MOD;
    }
    else{
        for(int i = 0 ; i <= k ; i++){
            ans = (ans + cntbeda[i] * cntsama[k - i]) % MOD;
            if(i < k){
                LL temp = 25LL;
                temp = (temp * cntbeda[i]) % MOD;
                temp = (temp * cntsama[k - i - 1]) % MOD;
                ans = (ans + temp) % MOD;
            }
        }
    }
    return ans;
}

int main(){
    precompute();
    int tc;
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        init();
        printf("Case %d: %lld\n",t,solve());
    }
    return 0;
}
