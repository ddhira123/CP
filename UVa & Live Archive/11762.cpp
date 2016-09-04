#include <bits/stdc++.h>
using namespace std;

const int MX = 1000001;

int divisor[MX];
vector<int> prime;
double dp[MX];

void sieve(){
    for(int i = 2 ; i < MX ; i++)
        if(divisor[i] == 0){
            prime.push_back(i);
            for(int j = i ; j < MX ; j += i)
                divisor[j] = i;
        }
}

void solve(){
    int it = 0;
    dp[2] = 1;
    for(int i = 3 ; i < MX ; i++){
        while(it < prime.size() && prime[it] <= i) it++;
        double &ret = dp[i];
        double ratio = 0;
        int x = i;
        while(x != 1){
            int y = divisor[x];
            ret += dp[i / y];
            while(y == divisor[x]) x /= y;
            ratio++;
        }
        ret /= it;
        ret++;
        ret *= (double)it;
        ret /= ratio;
    }
}

int main(){
    sieve();
    solve();
    int tc,n;
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        scanf("%d",&n);
        printf("Case %d: %.7lf\n",t,dp[n]);
    }
    return 0;
}
