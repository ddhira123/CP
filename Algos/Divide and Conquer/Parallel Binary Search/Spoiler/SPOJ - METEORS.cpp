#include <cstdio>
#include <vector>
using namespace std;
#define pb push_back

typedef long long LL;

const int N = 300005;

int lo[N],hi[N];
vector<int> proc[N];
vector<int> sector[N];
int target[N];
LL BIT[N];
int l[N],r[N],val[N];
int n,m,k;

void update(int x,LL val){
    for(; x <= m ; x += x & -x)
        BIT[x] += val;
}

LL query(int x){
    LL res = 0;
    for(; x > 0 ; x -= x & -x)
        res += BIT[x];
    return res;
}

void meteor(){
    for(int i = 1 ; i <= n ; i++){
        lo[i] = 1;
        hi[i] = k + 1;
        proc[(lo[i] + hi[i]) / 2].pb(i);
    }
    bool change = 1;
    while(change){
        change = 0;
        for(int i = 1 ; i <= m ; i++)
            BIT[i] = 0;
        for(int i = 1 ; i <= k ; i++){
            if(l[i] <= r[i]){
                update(l[i],val[i]);
                update(r[i] + 1,-val[i]);
            }
            else{
                update(l[i],val[i]);
                update(1,val[i]);
                update(r[i] + 1,-val[i]);
            }
            while(!proc[i].empty()){
                int now = proc[i].back();
                proc[i].pop_back();
                LL tgt = target[now];
                LL res = 0;
                for(int j = 0 ; j < sector[now].size() && res < tgt; j++)
                    res += query(sector[now][j]);
                if(res >= tgt)
                    hi[now] = i;
                else
                    lo[now] = i + 1;
                if(lo[now] < hi[now]){
                    int mid = (lo[now] + hi[now]) / 2;
                    proc[mid].pb(now);
                    change = 1;
                }
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
    scanf("%d %d",&n,&m);
    for(int i = 1 ; i <= m ; i++){
        int a;
        scanf("%d",&a);
        sector[a].pb(i);
    }
    for(int i = 1 ; i <= n ; i++)
        scanf("%d",&target[i]);
    scanf("%d",&k);
    for(int i = 1 ; i <= k ; i++)
        scanf("%d %d %d",&l[i],&r[i],&val[i]);
    meteor();
    return 0;
}
