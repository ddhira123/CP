#include <bits/stdc++.h>
using namespace std;

const int MX = 45000;

bool flag[MX];
vector<int> prime;

long long solve(int x){
    long long ans = 1;
    for(int fak : prime){
        if(fak * fak > x) break;
        long long cnt = 0;
        while(x % fak == 0){
            x /= fak;
            cnt++;
        }
        ans *= ((cnt + 1) * 2LL - 1);
    }
    if(x != 1){
        ans *= 3LL;
    }
    ans = (ans + 1) / 2LL;
    return ans;
}

void sieve(){
    for(int i = 2 ; i < MX ; i++)
        if(!flag[i]){
            prime.push_back(i);
            for(int j = i ; j < MX ; j += i)
                flag[j] = 1;
        }
}

int main(){
    sieve();
    int x;
    while(scanf("%d",&x) == 1 && x > 0)
        printf("%d %lld\n",x,solve(x));
    return 0;
}
