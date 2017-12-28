
#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int n,m,d;
map<long long,int> cnt;
set<long long> seen;
vector<long long> id;
map<long long,int> ranking;
vector<long long> valid;
int BIT[N];
map<long long, vector<long long> > adj;
map<long long,int> indegree;

void update(int x,int val){
    for( ; x < N ; x += x & -x)
        BIT[x] = max(BIT[x],val);
}

int query(int x){
    int res = 0;
    while(x){
        res = max(res,BIT[x]);
        x -= x & -x;
    }   
    return res;
}

bool cmp(int u,int v){
    return cnt[u] > cnt[v];
}

void make_rank(){
    queue<long long> q;
    for(auto it = indegree.begin() ; it != indegree.end() ; it++)
        if(it -> second == 0)
            q.push(it -> first);
    int itung = 0;
    while(!q.empty()){
        long long now = q.front();
        q.pop();
        ranking[now] = ++itung;
        for(int i = 0 ; i < adj[now].size() ; i++){
            long long nxt = adj[now][i];
            indegree[nxt]--;
            if(indegree[nxt] == 0)
                q.push(nxt);
        }
    }       
}

int main(){
    scanf("%d %d %d",&n,&m,&d);
    for(int i = 0 ; i < m ; i++){
        long long u,v;
        scanf("%lld %lld",&u,&v);
        cnt[u]++;
        seen.insert(u);
        seen.insert(v);
        indegree[v]++;
        if(indegree.count(u) == 0) indegree[u] = 0;
        adj[u].push_back(v);
    }
    make_rank();
    int ans = 0;
    for(int i = 0 ; i < n ; i++){
        long long u;
        scanf("%lld",&u);
        if(seen.count(u)) valid.push_back(u);
        else ans++;
    }   
    ans += (n - valid.size());
    for(int i = 0 ; i < valid.size() ; i++){
        long long u = valid[i];
        u = ranking[u];
        int val = query(u - 1) + 1;
        update(u,val);
    }
    ans += 2 * (valid.size() - query(N - 1));
    cout << ans << endl;
    return 0;
}

