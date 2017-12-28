#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back

const int N = 100005;
const int MX = 1000;
const int INF = (int)1e9;

struct stree{
    // x - y,x + y,index
    vector<pair<pii,int> > titik;
    vector<pii> tree;
    
    void build(int id,int l,int r){
        tree[id] = {INF,INF};
        if(l < r){
            int m = (l + r) / 2;
            int chld = id * 2;
            build(chld,l,m);
            build(chld + 1,m + 1,r);
        }
    }
    
    void make(){
        sort(titik.begin(),titik.end());
        tree.resize(4 * titik.size());
        if(!titik.empty())
            build(1,0,titik.size() - 1);
    }
    
    void hapus(){
        titik.clear();
        tree.clear();
    }
    
    void update(int id,int l,int r,int x,int val,int idx){
        if(l == r)
            tree[id] = {val,idx};
        else{
            int m = (l + r) / 2;
            int chld = id * 2;
            if(x <= m)  update(chld,l,m,x,val,idx);
            else        update(chld + 1,m + 1,r,x,val,idx);
            tree[id] = min(tree[chld],tree[chld + 1]);
        }   
    }
    
    pii query(int id,int l,int r,int x,int y){
        if(x <= l && r <= y)
            return tree[id];
        else{
            int m = (l + r) / 2;
            int chld = id * 2;
            pii res = {INF,INF};
            if(x <= m) res = min(res,query(chld,l,m,x,y));
            if(y > m)   res = min(res,query(chld + 1,m + 1,r,x,y));
            return res;
        }   
    }
    
    pii update2(pair<pii,int> x){
        pii temp = {x.fi.fi - x.fi.se,x.fi.fi + x.fi.se};
        x = {temp,x.se};
        assert(binary_search(titik.begin(),titik.end(),x));
        int idx = lower_bound(titik.begin(),titik.end(),x) - titik.begin();
        //cout << idx << endl;
        update(1,0,titik.size() - 1,idx,temp.se,x.se);
    }
    
    pii query2(pii x,int tipe){
        if(titik.empty()) return {INF,INF}; 
        int lo = 0;
        int hi = 0;
        pair<pii,int> temp;
        if(tipe == 0){
            temp = {{x.fi - x.se,INF},INF};
            hi = upper_bound(titik.begin(),titik.end(), temp ) - titik.begin();
            hi--;
        }
        else{
            temp = {{x.fi - x.se,INF},INF};
            hi = (int)titik.size() - 1;
            lo = upper_bound(titik.begin(),titik.end(),temp) - titik.begin();
        }
        if(lo <= hi)
            return query(1,0,titik.size() - 1,lo,hi);
        return {INF,INF};   
    }
};

stree rtree[4 * (MX + 5)];

void add(int id,int l,int r,int x,int y,int idx){
    rtree[id].titik.pb({{x - y,x + y},idx});
    if(l < r){
        int m = (l + r) / 2;
        int chld = id * 2;  
        if(x <= m)  add(chld,l,m,x,y,idx);
        else        add(chld + 1,m + 1,r,x,y,idx);
    }
}

void update(int id,int l,int r,int x,int y,int idx){
    rtree[id].update2({{x,y},idx});
    if(l < r){
        int m = (l + r) / 2;
        int chld = id * 2;
        if(x <= m)  update(chld,l,m,x,y,idx);
        else        update(chld + 1,m + 1,r,x,y,idx);       
    }
}

pii query(int id,int l,int r,int x,int y,pii val,int tipe){
    //cout << id << " " << l << " " << r << " " << x << " " << y << "\n";
    if(x <= l && r <= y){
        //cout << "query\n";
        pii res = rtree[id].query2(val,tipe);
        //cout << "fin\n";
        return res;
    }   
    else{
        int m = (l + r) / 2;
        int chld = id * 2;  
        pii res = {INF,INF};
        if(x <= m) res = min(res,query(chld,l,m,x,y,val,tipe));
        if(y > m)   res = min(res,query(chld + 1,m + 1,r,x,y,val,tipe));
        return res; 
    }   
}

pair<pii,int> arr[N];

bool cmp(pair<pii,int> a,pair<pii,int> b){
    if(a.fi.se == b.fi.se) return a.fi.fi > b.fi.fi;
    return a.fi.se > b.fi.se;
}

int n;
vector<pair<int,pii> > edge;
int pset[N];

void init(){
    for(int i = 0 ; i < n ; i++)
        pset[i] = i;
}

int finds(int x){
    return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

void join(int x,int y){
    pset[finds(x)] = finds(y);
}

set<pii> seen;

int main(){
    scanf("%d",&n);
    int m = 0;
    
    for(int i = 0 ; i < n ; i++){
        scanf("%d %d",&arr[m].fi.fi,&arr[m].fi.se);
        if(!seen.count(arr[m].fi)){
            arr[m].se = m;
            m++;
            seen.insert(arr[m - 1].fi);
        }
    }
    //cout << m << endl;
    n = m;
    for(int times = 0 ; times < 4 ; times++){
        //printf("%d\n",times);
        int mins = 0;
        sort(arr,arr + n,cmp);  
        for(int i = 0 ; i < n ; i++)
            mins = min(mins,arr[i].fi.fi);
        for(int i = 0 ; i < n ; i++){
            arr[i].fi.fi -= mins;
            //cout << arr[i].fi.fi << endl;
        }
        for(int i = 0 ; i < 4 * (MX + 5) ; i++)
            rtree[i].hapus();
        
        for(int i = 0 ; i < n ; i++){
            add(1,0,MX,arr[i].fi.fi,arr[i].fi.se,arr[i].se);
        }
        for(int i = 0 ; i < 4 * (MX + 5) ; i++)
            rtree[i].make();
            
        //cout << "h\n";
        for(int i = 0 ; i < n ; i++){
            //cout << "now " << i << endl;
            if(arr[i].fi.fi < MX){
                pii temen = query(1,0,MX,arr[i].fi.fi + 1,MX,arr[i].fi,1);
                if(temen.fi != INF){
                    int idx = arr[i].se;
                    int id2 = temen.se;
                    edge.pb({temen.fi - (arr[i].fi.fi + arr[i].fi.se),{idx,id2}});
                }
                temen = query(1,0,MX,arr[i].fi.fi + 1,MX,arr[i].fi,0);
                if(temen.fi != INF){
                    int idx = arr[i].se;
                    int id2 = temen.se;
                    edge.pb({temen.fi - (arr[i].fi.fi + arr[i].fi.se),{idx,id2}});
                }               
            }
            //cout << "update\n";
            update(1,0,MX,arr[i].fi.fi,arr[i].fi.se,arr[i].se);
        }
        
        for(int i = 0 ; i < n ; i++)
            arr[i].fi.fi += mins;
        for(int i = 0 ; i < n ; i++){
            int x = -arr[i].fi.se;
            int y = arr[i].fi.fi;
            arr[i].fi.fi = x;
            arr[i].fi.se = y;
        }           
    }
    init();
    sort(edge.begin(),edge.end());
    int ans = 0;
    for(int i = 0 ; i < edge.size() ; i++){
        int u = edge[i].se.fi;
        int v = edge[i].se.se;
        int cost = edge[i].fi;
        if(finds(u) != finds(v)){
            ans += cost;
            join(u,v);
        }
    }
    cout << ans << endl;
    return 0;
}

