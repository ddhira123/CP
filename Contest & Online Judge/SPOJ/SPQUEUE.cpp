#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 500005;
const int MX = 12;

vector<int> prime;
LL fak[N];
int cnt[N][MX];
LL dp[N];
LL dpp[N][MX];

int par[N];
int deg[N];
int q[N],head,tail;
int sz[N];

int n,tc;
LL mod;

LL extended_euclid(LL a, LL b, LL &x, LL &y) {
    LL xx = y = 0;
    LL yy = x = 1;
    while (b) {
        LL q = a/b;
        LL t = b; b = a%b; a = t;
        t = xx; xx = x-q*xx; x = t;
        t = yy; yy = y-q*yy; y = t;
    }
    return a;
}    

LL mod_inverse(LL a, LL b) {
    LL x, y;
    LL d = extended_euclid(a, b, x, y);
    if (d > 1) return -1;
    x %= b;
    return (x + b) % b;
}

LL modpow(LL base,LL po){
    LL res = 1;
    while(po){
        if(po & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        po >>= 1;
    }
    return res;
}

void init(){
    scanf("%lld %d",&mod,&n);
    for(int i = 2 ; i <= n ; i++){
        scanf("%d",&par[i]);
        deg[par[i]]++;
    }
}

void compute(){
    prime.clear();
    LL temp = mod;
    for(int i = 2 ; i <= (int)sqrt(mod) + 1 ; i++)
        if(temp % i == 0){
            prime.push_back(i);
            while(temp % i == 0) temp /= i;
        }
    if(temp > 1) prime.push_back(temp);
    //for(int j = 0 ; j < prime.size() ; j++)
    //    printf("%d\n",prime[j]);
    fak[0] = 1;
    for(int i = 1 ; i <= n ; i++){
        temp = i;
        for(int j = 0 ; j < prime.size() ; j++){
            cnt[i][j] = cnt[i - 1][j];
            while(temp % prime[j] == 0){
                temp /= prime[j];
                cnt[i][j]++;
            }
        }
        fak[i] = (fak[i - 1] * temp) % mod;
    }    
}

LL solve(){
    if(mod == 1) return 0;
    compute();
    head = tail = 0;
    for(int i = 1 ; i <= n ; i++){
        dp[i] = 1;
        sz[i] = 1;
        for(int j = 0 ; j < prime.size() ; j++)
            dpp[i][j] = 0;
        if(deg[i] == 0)
            q[tail++] = i;    
    }    
    for(int i = 1 ; i <= n ; i++){
        assert(head < tail);
        int x = q[head++];
        dp[x] = (dp[x] * fak[sz[x] - 1]) % mod;
        for(int j = 0 ; j < prime.size() ; j++)
            dpp[x][j] += cnt[sz[x] - 1][j];
        //printf("%d %lld\n",)       
        if(x > 1){    
            int papa = par[x];
            LL inve = mod_inverse(fak[sz[x]],mod);
            dp[papa] = (dp[papa] * inve) % mod;
            dp[papa] = (dp[papa] * dp[x]) % mod;
            for(int j = 0 ; j < prime.size() ; j++){
                dpp[papa][j] += dpp[x][j];
                dpp[papa][j] -= cnt[sz[x]][j];
            }
            sz[papa] += sz[x];
            deg[papa]--;
            if(deg[papa] == 0)
                q[tail++] = papa;
        }
    }
    LL ans = dp[1];
    for(int j = 0 ; j < prime.size() ; j++)
        ans = (ans * modpow(prime[j],dpp[1][j])) % mod;
    return ans;        
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        init();
        printf("%lld\n",solve());
    }
    return 0;
}