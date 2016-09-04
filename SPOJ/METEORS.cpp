#include <cstdio>
#include <vector>
using namespace std;
#define pb push_back

typedef long long LL;

#ifdef _WIN32
    #define getchar_unlocked getchar
#endif

#define g getchar_unlocked

inline int io(){
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

const int N = 300005;

int lo[N],hi[N];
vector<int> proc[N];
vector<int> sector[N];
int target[N];
LL BIT[N];
int l[N],r[N],val[N];
int n,m,k;

void Update(int x,LL val){
    for(; x <= m ; x += x & -x)
        BIT[x] += val;
}

LL Query(int x){
    LL res = 0;
    for(; x > 0 ; x -= x & -x)
        res += BIT[x];
    return res;
}

void Meteor(){ // total : (m + k) * log(m) * log(k)
    for(int i = 1 ; i <= n ; i++){
        lo[i] = 1;
        hi[i] = k + 1;
        proc[(lo[i] + hi[i]) / 2].pb(i);
    }
    int notyet = n;
    while(notyet > 0){ // log(k)
        for(int i = 1 ; i <= m ; i++)
            BIT[i] = 0;
        for(int i = 1 ; i <= k && notyet > 0 ; i++){ 
            if(l[i] <= r[i]){ // total : k * log(m)
                Update(l[i],val[i]);
                Update(r[i] + 1,-val[i]);
            }
            else{
                Update(l[i],val[i]);
                Update(1,val[i]);
                Update(r[i] + 1,-val[i]);
            }
            while(!proc[i].empty()){
                int now = proc[i].back();
                proc[i].pop_back();
                LL tgt = target[now];
                LL res = 0;
                for(int j = 0 ; j < sector[now].size() && res < tgt; j++) // total : m * log(m)
                    res += Query(sector[now][j]);
                if(res >= tgt)
                    hi[now] = i;
                else
                    lo[now] = i + 1;
                if(lo[now] < hi[now]){
                    int mid = (lo[now] + hi[now]) / 2;
                    proc[mid].pb(now);
                }
                else
                    notyet--;
            }
        }
    }
    for(int i = 1 ; i <= n ; i++)
        if(lo[i] == k + 1)
            puts("NIE");
        else
            printf("%d\n",lo[i]);
}

int main(){
    //scanf("%d %d",&n,&m);
    n = io(); m = io();
    for(int i = 1 ; i <= m ; i++){
        int a;
        //scanf("%d",&a);
        a = io();
        sector[a].pb(i);
    }
    for(int i = 1 ; i <= n ; i++){
        //scanf("%d",&target[i]);
        target[i] = io();
    }
    //scanf("%d",&k);
    k = io();
    for(int i = 1 ; i <= k ; i++){
        //scanf("%d %d %d",&l[i],&r[i],&val[i]);
        l[i] = io(); r[i] = io(); val[i] = io();
    }
    Meteor();
    return 0;
}
