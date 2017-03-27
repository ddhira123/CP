#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <bitset>
#include <cassert>
//Because defining using namespace std is too mainstream
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<string,string> pss;
typedef pair<int,double> pid;
typedef pair<int,LL> pil;
typedef pair<LL,LL> pll;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define TIE cin.tie(0)
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")

#ifdef _WIN32
    #define getchar_unlocked getchar
#endif

#define g getchar_unlocked

int dx8[8]={-1,-1,0,1,1,1,0,-1},dx4[4]={-1,0,1,0};
int dy8[8]={0,-1,-1,-1,0,1,1,1},dy4[4]={0,-1,0,1};

inline void open(string name){
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

inline void close(){
    fclose(stdin);
    fclose(stdout);
}

inline int io(){
    register char c;
    while(1){
        c = g();
        if(c != '\n' && c != ' ') break;
    }
    int res = 0, sign = 1;
    if(c=='-') sign = -1;
    else       res = c-'0';
    while(1){
        c = g();
        if(c == ' ' || c == '\n' || c == EOF) break;
        res = (res << 3) + (res << 1) + c - '0';
    }
    return res * sign;
}

///////////////////////////////////////////////////
//////            End of Template            /////
/////////////////////////////////////////////////

const int N = 100005;

LL fact[N],inve[N];
char s[3][N];
int cnt[4];
int n;

void Flip(char &x){
    x = (x == '1') ? '0' : '1';
}

LL modpow(LL base,int po){
    LL res = 1;
    while(po){
        if(po & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        po >>= 1;
    }
    return res;
}

void Precompute(){
    n = strlen(s[0]);
    fact[0] = inve[0] = 1;
    for(int i = 1 ; i <= n ; i++){
        fact[i] = (fact[i - 1] * (LL)i) % MOD;
        inve[i] = modpow(fact[i],MOD - 2);
    }
    for(int i = 0 ; i < n ; i++){
        if(s[0][i] == '1')
            for(int j = 0 ; j < 3 ; j++)
                Flip(s[j][i]);
        int mask = 0;
        for(int j = 0 ; j < 3 ; j++)
            mask |= ((s[j][i] - '0') << (2 - j));
        cnt[mask]++;            
    }
}

LL C(int x,int y){
    LL res = (inve[y] * inve[x - y]) % MOD;
    res = (res * fact[x]) % MOD;
    return res;
}

int main(){
    for(int i = 0 ; i < 3 ; i++)
        scanf("%s",s[i]);
    Precompute();
    LL ans = 0;
    for(int dist = -n ; dist <= n ; dist++){
        int tmp = dist + cnt[1];
        if(tmp % 2) continue;
        tmp /= 2;
        if(tmp < 0 || tmp > cnt[1]) continue; 
        int u10 = tmp;
        int u11 = cnt[1] - u10;
        
        tmp = dist + cnt[2];
        if(tmp % 2) continue;
        tmp /= 2;
        if(tmp < 0 || tmp > cnt[2]) continue; 
        int u20 = tmp;
        int u21 = cnt[2] - u20;  

        tmp = dist + cnt[3];
        if(tmp % 2) continue;
        tmp /= 2;
        if(tmp < 0 || tmp > cnt[3]) continue; 
        int u31 = tmp;
        int u30 = cnt[3] - u31;  
        
        LL res = 1;          
        res = (res * C(cnt[1],u10)) % MOD;
        res = (res * C(cnt[2],u20)) % MOD;
        res = (res * C(cnt[3],u30)) % MOD;
        ans = (ans + res) % MOD;  
    }
    ans = (ans * modpow(2,cnt[0])) % MOD;
    printf("%lld\n",ans);    
    //puts("ganteng");
    return 0;
}
