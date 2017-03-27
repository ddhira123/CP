#include <cstdio>
#include <vector>
using namespace std;

typedef long long LL;

#ifdef _WIN32
    #define getchar_unlocked getchar
#endif

#define g getchar_unlocked

inline LL io(){
    register char c;
    while(1){
        c = g();
        if(c != '\n' && c != ' ') break;
    }
    LL res = 0, sign = 1;
    if(c=='-') sign = -1;
    else res = c-'0';
    while(1){
        c = g();
        if(c == ' ' || c == '\n' || c == EOF) break;
        res = (res << 3) + (res << 1) + (LL)(c - '0');
    }
    return res * sign;
}

const LL MOD = 1000000007;
const int N = 100005;

//0 : (x - sigma(k * depth))
//1 : sigma(k)
//2 : bonus

int BIT[3][N];
int in[N],ot[N];
int sz[N];
int par[N];
vector<int> chld[N];
int depth[N],total_depth[N];
int cnt;
int n,m;

int Add(int &x,int y){
    x += y;
    if(x >= MOD) x -= MOD;
    if(x < 0)    x += MOD;
}

void DFS(int pos,int dep){
    in[pos] = ++cnt;
    depth[pos] = dep;
    total_depth[pos] = dep;
    sz[pos] = 1;
    for(int i = 0 ; i < chld[pos].size() ; i++){
        int nxt = chld[pos][i];
        DFS(nxt,dep + 1);
        Add(total_depth[pos],total_depth[nxt]);
        sz[pos] += sz[nxt];
    }
    ot[pos] = cnt;
}

void UpdateB(int id,int pos,int val){
    for(; pos <= n ; pos += pos & -pos)
        Add(BIT[id][pos],val);
}

int QueryB(int id,int pos){
    int ans = 0;
    for(; pos > 0 ; pos -= pos & -pos)
        Add(ans,BIT[id][pos]);
    return ans;
}

void Update(int pos,LL x,LL k){
    x %= MOD;
    k %= MOD;
    LL k2 = (k * (LL)depth[pos]) % MOD;
    if(pos != 1){
        int parent = par[pos];
        LL tot = ((x - k2) * (LL)sz[pos]) % MOD;
        tot = (tot + k * (LL)total_depth[pos]) % MOD;
        UpdateB(2,in[parent],tot);
    }
    UpdateB(0,in[pos],x - k2);
    UpdateB(0,ot[pos] + 1,-(x - k2));
    UpdateB(1,in[pos],k);
    UpdateB(1,ot[pos] + 1,-k);
}

int Query(int pos){
    LL ans = 0;
    ans = (ans + QueryB(0,in[pos]) * (LL)sz[pos]) % MOD;
    ans = (ans + QueryB(1,in[pos]) * (LL)total_depth[pos]) % MOD;
    ans = (ans + QueryB(2,ot[pos]) - QueryB(2,in[pos] - 1)) % MOD;
    if(ans < 0) ans += MOD;
    return (int)ans;
}

void Init(){
    //scanf("%d",&n);
    n = io();
    for(int i = 2 ; i <= n ; i++){
        //scanf("%d",&par[i]);
        par[i] = io();
        chld[par[i]].push_back(i);
    }
    DFS(1,0);
}

void Solve(){
    //scanf("%d",&m);
    m = io();
    while(m--){
        int a,opt;
        LL b,c;
        //scanf("%d",&opt);
        opt = io();
        if(opt == 1){
            //scanf("%d %lld %lld",&a,&b,&c);
            a = io(); b = io(); c = io();
            Update(a,b,c);
        }
        else{
            //scanf("%d",&a);
            a = io();
            printf("%d\n",Query(a));
        }
    }
}

int main(){
    Init();
    Solve();
    return 0;
}
