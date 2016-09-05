#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

#define pb push_back
#define fi first
#define se second
#define mp make_pair

typedef long long LL;
typedef pair<int,int> pii;

vector<int> isi[N];
int root[N],pos[N];
LL sum[N];
int saiz[N];
int n,m;
set<pii> s;

void init(){
    s.clear();
    for(int i = 1 ; i <= n ; i++){
        //isi[i].clear();
        //isi[i].pb(i);
        root[i] = i;
        pos[i] = 0;
        sum[i] = i;
        saiz[i] = 1;
        s.insert(mp(i,i));
    }
}

void join(int u,int v,int tipe){
    int uu = root[u];
    int vv = root[v];
    if(uu == vv) return;
    if(tipe == 2){
        //if(pos[u] >= saiz[uu]) return;
        //swap(isi[uu][pos[u]],isi[uu][saiz[uu] - 1]);
        //isi[uu].pop_back();
        sum[uu] -= u;
        saiz[uu]--;
        //isi[vv].pb(u);
        saiz[vv]++;
        //pos[u] = saiz[vv] - 1;
        root[u] = vv;
        sum[vv] += u;
        s.erase(mp(uu,u));
        s.insert(mp(vv,u));
    }
    else{
        if(saiz[uu] > saiz[vv]) swap(uu,vv);
        for(int i = 0 ; i < saiz[uu] ; i++){
            /*u = isi[uu][i];
            root[u] = vv;
            pos[u] = saiz[vv] + i;
            isi[vv].pb(u);*/
            auto it = s.lower_bound(mp(uu,0));
            u = it -> second;
            s.insert(mp(vv,u));
            root[u] = vv;
            s.erase(mp(uu,u));
        }
        isi[uu].clear();
        sum[vv] += sum[uu];
        saiz[vv] += saiz[uu];
        sum[uu] = 0;
        saiz[uu] = 0;
    }
}

void solve(){
    for(int i = 0 ; i < m ; i++){
        int opt,u,v;
        scanf("%d %d",&opt,&u);
        if(opt == 3){
            u = root[u];
            printf("%d %lld\n",saiz[u],sum[u]);
        }
        else{
            scanf("%d",&v);
            join(u,v,opt);
        }
    }
}

int main(){
    while(scanf("%d %d",&n,&m) == 2){
        init();
        solve();
        for(int i = 1 ; i <= n ; i++)
            isi[i].clear();
    }
    return 0;
}
