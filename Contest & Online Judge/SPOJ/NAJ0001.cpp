#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define pb push_back

typedef pair<int,int> pii;

const int N = 100005;
const int MX = 1000005;
const int VMX = 1001;

vector<pii> prime;
int sieve[MX];
vector<int> indice[VMX];
vector<long long> psum[VMX]; 
int n,m;
int arr[N];

void SieveOfErathostenes(){
    for(int i = 2 ; i < MX ; i++)
        if(sieve[i] == 0)
            for(int j = i ; j < MX ; j += i)
                sieve[j] = i;
}

long long Query(int val,int x,int y){
    y = upper_bound(indice[val].begin(),indice[val].end(),y) - indice[val].begin();
    x = lower_bound(indice[val].begin(),indice[val].end(),x) - indice[val].begin();
    long long res = psum[val][y];
    res -= psum[val][x];
    return res; 
}

void Add(int pos,int mul,int idx){
    if(mul >= VMX) return;
    if(pos == prime.size()){
        indice[mul].pb(idx);
        //printf("%d\n",mul);
    }    
    else{
        int times = 1;
        for(int i = 0 ; i <= prime[pos].se ; i++){
            Add(pos + 1,mul * times,idx);
            times *= prime[pos].fi;
        }
    }
}

void Init(){
    scanf("%d %d",&n,&m);
    for(int i = 0 ; i < VMX ; i++)
        indice[i].clear();
    for(int i = 1 ; i <= n ; i++){
        scanf("%d",&arr[i]);
        int x = arr[i];
        prime.clear();
        while(x != 1){
            int y = sieve[x];
            int cnt = 0;
            while(sieve[x] == y){
                cnt++;
                x /= y;
            }
            prime.pb(mp(y,cnt));
        }
        //printf("adding %d\n",arr[i]);
        Add(0,1,i);
    }
    for(int i = 0 ; i < VMX ; i++){
        psum[i].clear();
        psum[i].resize(indice[i].size() + 1);
        psum[i][0] = 0;
        for(int j = 1 ; j <= indice[i].size() ; j++){
            int pos = indice[i][j - 1];
            psum[i][j] = psum[i][j - 1] + (long long)arr[pos];
            //if(i == 2)
            //    printf("%d %lld\n",pos,psum[i][j]);
        }
    }
}

void Solve(){
    for(int i = 1 ; i <= m ; i++){
        int val,x,y;
        scanf("%d %d %d",&val,&x,&y);
        printf("%lld\n",Query(val,x,y));
    }
}

int main(){
    SieveOfErathostenes();
    int tc;
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        if(t > 1) printf("\n");
        printf("Case #%d\n",t);
        Init();
        Solve();
    }
    return 0;
}