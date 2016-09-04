#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

typedef long long LL;
typedef pair<int,LL> pil;
typedef pair<int,int> pii;

const int N = 100005;
const int LG = 17;
const LL INF = 1000000000000000001LL;
const double EPS = 1e-9;

LL depth_tree[N];
int depth_stek[N];
int anc[N][LG];
LL dp[N],s[N],v[N];
vector<pil> adj[N];
int n;

bool bad(int x,int y,int z){
    return (double)(dp[z] - dp[x]) / (double)(depth_tree[x] - depth_tree[z]) + EPS >
            (double)(dp[y] - dp[x]) / (double)(depth_tree[x] - depth_tree[y]);
}

void Add(int pos,int pre){
    int lg = 0;
    while((1 << lg) <= depth_stek[pre]) lg++;
    lg--;
    for(int i = lg ; i >= 0 ; i--)
        if((1 << i) < depth_stek[pre]){
            int par = anc[pre][i];
            if(bad(anc[par][0],par,pos))
                pre = par;
        }
    while(depth_stek[pre] >= 1 && bad(anc[pre][0],pre,pos)){
        //printf("%d POP %d\n",pos,pre);
        pre = anc[pre][0];
    }
    depth_stek[pos] = depth_stek[pre] + 1;
    anc[pos][0] = pre;
    for(int i = 1 ; (1 << i) <= depth_stek[pos] ; i++){
        int par = anc[pos][i - 1];
        int gpar = anc[par][i - 1];
        anc[pos][i] = gpar;
    }
}

LL Query(LL x,int pos){
    int lg = 0;
    while((1 << lg) <= depth_stek[pos]) lg++;
    lg--;
    LL res = depth_tree[pos] * x + dp[pos];
    if(depth_stek[pos] >= 1)
        res = min(res,depth_tree[anc[pos][0]] * x + dp[anc[pos][0]]);
    for(int i = lg ; i >= 0 ; i--)
        if((1 << i) < depth_stek[pos]){
            int par = anc[pos][i];
            double ls,rs;
            int parpar = anc[par][0];
            ls = x;
            rs = (double)(dp[parpar] - dp[par]) / (double)(depth_tree[par] - depth_tree[parpar]);
            //printf("%d ls %lld rs %lld\n",par,ls,rs);
            if(ls + EPS > rs){
                pos = par;
            }
        }
    //printf("RESULT %d\n",pos);
    res = min(res,depth_tree[pos] * x + dp[pos]);
    if(depth_stek[pos] >= 1)
        res = min(res,depth_tree[anc[pos][0]] * x + dp[anc[pos][0]]);
    return res;
}

void DFS(int pos,int pre){
    //printf("QUERY %d\n",pos);
    dp[pos] = Query(-v[pos],pre);
    dp[pos] += s[pos] + depth_tree[pos] * v[pos];

    //printf("POS %d DEPTH_TREE %lld DP %lld\n",pos,depth_tree[pos],dp[pos]);
    Add(pos,pre);
    for(int i = 0 ; i < adj[pos].size() ; i++){
        int nxt = adj[pos][i].first;
        if(nxt != pre){
            depth_tree[nxt] = depth_tree[pos] + adj[pos][i].second;
            DFS(nxt,pos);
        }
    }
}

void BFS(int st){
    queue<pii> q;
    q.push(pii(st,1));
    while(!q.empty()){
        pii now = q.front();
        q.pop();
        int pos = now.first;
        int pre = now.second;
        dp[pos] = Query(-v[pos],pre) + s[pos] + depth_tree[pos] * v[pos];
        assert(dp[pos] > 0);
        Add(pos,pre);
        for(int i = 0 ; i < adj[pos].size() ; i++){
            int nxt = adj[pos][i].first;
            if(nxt != pre){
                depth_tree[nxt] = depth_tree[pos] + adj[pos][i].second;
                q.push(pii(nxt,pos));
            }
        }
    }
}

void Init(){
    scanf("%d",&n);
    for(int i = 1 ; i < n ; i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        adj[a].push_back(pil(b,c));
        adj[b].push_back(pil(a,c));
    }
    for(int i = 2 ; i <= n ; i++)
        scanf("%lld %lld",&s[i],&v[i]);
}

void Solve(){
    for(int i = 0 ; i < adj[1].size() ; i++){
        int nxt = adj[1][i].first;
        depth_tree[nxt] = adj[1][i].second;
        //DFS(nxt,1);
        BFS(nxt);
    }
    for(int i = 2 ; i <= n ; i++)
        printf("%lld%c",dp[i],i == n ? '\n' : ' ');
}

int main(){
    Init();
    Solve();
    return 0;
}
