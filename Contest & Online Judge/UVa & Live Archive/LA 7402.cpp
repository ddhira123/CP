#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second

const int N = 100005;

typedef pair<int,int> pii;

struct AVL{
    struct Node{
        int key;
        int height;
        int sum;
        int val;
        Node *l, *r;
        
        Node(){
            key = 0;
            height = 0;
            sum = 0;
            val = 0;
            l = r = NULL;
        }

    };
    
    Node *root;
    
    AVL() {
        root = NULL;
    }

    ~AVL() {
        Clear(root);
    }

    void Clear(Node *x) {
        if(x != NULL) {
            Clear(x -> l);
            Clear(x -> r);
            delete x;
        }
    }

    
    int GetHeight(Node *x){
        return x == NULL ? -1 : x -> height;
    }
    
    int GetSum(Node *x){
        return x == NULL ? 0 : x -> sum;
    }
    
    Node *Update(Node *x){
        if(x == NULL) return x;
        x -> height = 1 + max(GetHeight(x -> l),GetHeight(x -> r));
        x -> sum = x -> val + GetSum(x -> l) + GetSum(x -> r);
        return x;
    }
    
    Node *RotateRight1(Node *x){
        Node *tmp = x -> l;
        x -> l = tmp -> r;
        tmp -> r = x;
        x = Update(x);
        tmp = Update(tmp);
        return tmp;
    }
    
    Node *RotateLeft1(Node *x){
        Node *tmp = x -> r;
        x -> r = tmp -> l;
        tmp -> l = x;
        x = Update(x);
        tmp = Update(tmp);
        return tmp;
    }
    
    Node *RotateRight2(Node *x){
        x -> l = RotateLeft1(x -> l);
        x = RotateRight1(x);
        return x;
    }
    
    Node *RotateLeft2(Node *x){
        x -> r = RotateRight1(x -> r);
        x = RotateLeft1(x);
        return x;
    }
    
    Node *Rebalance(Node *x){
        if(x == NULL) return x;
        x = Update(x);
        Node *L = x -> l, *R = x -> r;
        if(GetHeight(L) - GetHeight(R) == 2){
            if(GetHeight(L -> l) > GetHeight(L -> r))
                x = RotateRight1(x);
            else
                x = RotateRight2(x);    
        }
        else if(GetHeight(R) - GetHeight(L) == 2){
            if(GetHeight(R -> r) > GetHeight(R -> l))
                x = RotateLeft1(x);
            else
                x = RotateLeft2(x);    
        }
        x = Update(x);
        return x;
    }
    
    void Insert(int nkey,int value){
        root = Insert(root,nkey,value);
    }
    
    Node *Insert(Node *x,int nkey,int value){
        if(x == NULL){
            x = new Node();
            x -> val = x -> sum = value;
            x -> key = nkey;
        }
        else if(x -> key < nkey)
            x -> r = Insert(x -> r,nkey,value);
        else if(x -> key > nkey)
            x -> l = Insert(x -> l,nkey,value);
        else{
            x -> val += value;
            x -> sum += value;
        }      
        x = Rebalance(x);
        return x;
    }
    
    Node *Successor(Node *x){
        while(x -> l != NULL) x = x -> l;
        return x;
    }
    
    Node *Displace(Node *x){
        if(x -> l == NULL) return x -> r;
        x -> l = Displace(x -> l);
        x = Rebalance(x);
        return x;
    }
    
    void Remove(int nkey,int value){
        root = Remove(root,nkey,value);
    }
    
    Node *Remove(Node *x,int nkey,int value){
        if(x == NULL){
            assert(0);
        }
        //printf("key %d nkey %d value %lld\n",x -> key,nkey,value);    
        if(x -> key < nkey)
            x -> r = Remove(x -> r,nkey,value);
        else if(x -> key > nkey)
            x -> l = Remove(x -> l,nkey,value);
        else{
            x -> val -= value;
            x -> sum -= value;
            if(x -> val == 0){
            	if(x -> l == NULL && x -> r == NULL)
            		x = NULL;
                else if(x -> l != NULL && x -> r != NULL){
                    Node *tmp = Successor(x -> r);
                    x -> r = Displace(x -> r);
                    tmp -> l = x -> l;
                    tmp -> r = x -> r;
                    x = tmp;
                }
                else
                    x = (x -> l == NULL) ? x -> r : x -> l;
            }
        }
        x = Rebalance(x);
        return x;            
    }
    
    int Query(int nkey){
        int res = 0;
        Node *x = root;
        while(x != NULL){
            if(x -> key <= nkey)
                x = x -> r;
            else{
                res += GetSum(x) - GetSum(x -> l);
                x = x -> l;
            }    
        }
        return res;
    }

    void Print() {
        Print(root);
    }

    void Print(Node *now) {
        if(now == NULL) return;
        Print(now -> l);
        printf("key %d val %d\n",now -> key,now -> val);
        Print(now -> r);
    }

    void PrintStat(Node *x) {
        if(x == NULL) {
            puts("NULL!");
        }
        else {
            printf("STAT %d %d\n",x -> key, x -> val);
        }
    }
};

AVL *BIT[N];
set<pair<pii,int> > interval;
set<pii> akhir;
set<pii> byPos;

int in[N], ot[N];
int inve[N];
int cnt;
vector<int> adj[N];
int initialColor[N];

int n,q;

void add(int x,int key) {
    for( ; x <= n ; x += x & -x)
        BIT[x] -> Insert(key,1);
}

void remove(int x,int key) {
    for( ; x <= n ; x += x & -x)
        BIT[x] -> Remove(key,1);
}

int query(int x,int y) {
    int res = 0;
    while(x) {
        res += BIT[x] -> Query(y);
        x -= x & -x;
    }
    return res;
}

void dfs(int now,int prv) {
    in[now] = ++cnt;
    inve[cnt] = now;

    for(int nex : adj[now]) {
        if(nex == prv) continue;
        dfs(nex,now);
    }

    ot[now] = cnt;
}

// nasty things begin

int getNext(pii x) {
    int ret;
    auto it = akhir.upper_bound(x);
    if(it == akhir.end() || (*it).fi != x.fi) 
        ret = N;
    else {
        ret = (*it).se;
    }
    return ret;    
}

int getPrev(pii x) {
    int ret;
    auto it = akhir.lower_bound(x);
    if(it == akhir.begin()) 
        ret = -1;
    else {
        it--;
        if((*it).fi != x.fi)
            ret = -1;
        else
            ret = (*it).se;
    }
    return ret;    
}

void addValue(pii x) {
    int nxt = getNext(x);
    add(x.se,nxt);
}

void removeValue(pii x) {
    int nxt = getNext(x);
    //printf("%d %d\n",x.se,nxt);
    remove(x.se,nxt);
}

// hapus interval ini
void hapus(pair<pii,int> x) {
    int st = x.fi.fi;
    int en = x.fi.se;
    int color = x.se;
    int prv = getPrev({color,en});
    int nxt = getNext({color,en});

    //printf("%d %d %d %d %d\n",st,en,color,prv,nxt);
    removeValue({color,en});

    //printf("%d %d %d\n",prv,nxt,en);

    if(prv != -1) {
        remove(prv,en);
        add(prv,nxt);
        //printf("%d -> from %d now %d\n",prv,en,nxt);
    }

    if(interval.count(x))
        interval.erase(x);
    akhir.erase({color,en});
    byPos.erase({en,color});

}

void split(pair<pii,int> x,int st,int en) {
    int color = x.se;
    interval.erase(x);

    if(x.fi.fi == st && x.fi.se == en) {
        hapus(x);
    }
    else if(x.fi.fi == st) {
        // hapus prefix
        // it's very easy!
        x.fi.fi = en + 1;
        interval.insert(x);
    }
    else if(x.fi.se == en) {
        // hapus suffix
        // it's not very easy..
        //printf("TRY\n");
        removeValue({color,x.fi.se});
        int prv = getPrev({color,x.fi.se});
        akhir.erase({color,x.fi.se});
        byPos.erase({x.fi.se,color});

        if(prv != -1) {
            remove(prv,x.fi.se);
            add(prv,st - 1);
        }

        akhir.insert({color,st - 1});
        byPos.insert({st - 1,color});
        x.fi.se = st - 1;
        int nxt = getNext({color,st - 1});
        add(st - 1,nxt);

        interval.insert(x);
    }
    else {
        assert(0);
    }

}

void updateWorker(int st,int en,int color) {
    //printf("st %d en %d color %d\n",st,en,color);
    vector<pair<pii,int> > intervalAffected;
    pair<pii,int> temp = {{st,-1},-1};

    /*for(auto it : interval) {
        printf("%d %d %d\n",it.fi.fi,it.fi.se,it.se);
    }*/

    auto haha = interval.lower_bound(temp);
    while(haha != interval.begin()) {
        haha--;
        if((*haha).fi.se >= st) {
            intervalAffected.push_back(*haha);
        }
        else {
            break;
        }
    }

    temp.fi.fi = st;
    haha = interval.lower_bound(temp);
    while(haha != interval.end()) {
        if((*haha).fi.fi <= en) {
            intervalAffected.push_back(*haha);
            haha++;
        }
        else
            break;
    }

    sort(intervalAffected.begin(),intervalAffected.end());
    /*puts("FINISHED GRABBING INTERVAL!");
    for(auto it : intervalAffected)
        printf("%d %d %d\n",it.fi.fi,it.fi.se,it.se);*/
    for(int i = 1 ; i + 1 < intervalAffected.size() ; i++)
        hapus(intervalAffected[i]);

    if(intervalAffected.size() == 1) {
        auto cur = intervalAffected[0];
        int start = cur.fi.fi;
        int enn = cur.fi.se;
        int curColor = cur.se;

        if(start == st && enn == en) {
            hapus(cur);
        }
        else if(start == st || enn == en){
            split(cur,max(start,st),min(enn,en));
        }
        else {
            int prv = getPrev({curColor,enn});
            if(prv != -1) {
                remove(prv,enn);
                add(prv,st - 1);
            }

            interval.erase(cur);
            akhir.insert({curColor,st - 1});
            byPos.insert({st - 1,curColor});
            
            add(st - 1,enn);

            interval.insert({{start,st - 1},curColor});
            interval.insert({{en + 1,enn},curColor});
        }
    }
    else {
        //puts("MORE THAN 1 CASE");
        split(intervalAffected[0],st,intervalAffected[0].fi.se);
        split(intervalAffected.back(),(intervalAffected.back()).fi.fi,en);
    }

    akhir.insert({color,en});
    byPos.insert({en,color});
    interval.insert({{st,en},color});

    int prv = getPrev({color,en});
    int nxt = getNext({color,en});

    if(prv != -1) {
        remove(prv,nxt);
        add(prv,en);
        //printf("%d %d %d\n",prv,nxt,en);
    }

    add(en,nxt);
    //puts("UPDATE OK!");
}

void queryWorker() {
    scanf("%d",&q);
    for(int i = 1 ; i <= q ; i++) {
        int opt,u,c;
        scanf("%d %d",&opt,&u);
        if(opt == 0) {
            scanf("%d",&c);
            //printf("UPDATE %d %d\n",u,c);
            updateWorker(in[u],ot[u],c);
        }
        else {
            //printf("QUERY %d\n",u);
            auto temp = byPos.lower_bound({ot[u],-1});
            int color = (*temp).se;
            int pos = (*temp).fi;
            int ans = 0;

            if(ot[u] != pos) {
                int prv = getPrev({color,pos});
                if(prv != -1) {
                    remove(prv,pos);
                    add(prv,ot[u]);
                }
                add(ot[u],pos);
            }

            ans = query(ot[u],ot[u]) - query(in[u] - 1,ot[u]);
            printf("%d\n",ans);

            if(ot[u] != pos) {
                int prv = getPrev({color,pos});
                if(prv != -1) {
                    remove(prv,ot[u]);
                    add(prv,pos);
                }
                remove(ot[u],pos);                
            }
        }
    }
}

void read() {
    scanf("%d",&n);
    for(int i = 1 ; i < n ; i++) {
        int u,v;
        scanf("%d %d",&u,&v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 1 ; i <= n ; i++)
        scanf("%d",initialColor + i);

    //puts("FINISHED READING");
}

void init() {
    dfs(1,0);

    for(int i = 1 ; i <= n ; ) {
        int j = i;

        while(j <= n && initialColor[inve[i]] == initialColor[inve[j]])
            j++;
        j--;

        interval.insert( { {i,j} ,initialColor[inve[i]] } );
        akhir.insert( { initialColor[inve[j]], j } );
        byPos.insert({j,initialColor[inve[j]]});
        i = j + 1;
    }

    for(int i = 1 ; i <= n ; i++)
        BIT[i] = new AVL();

    for(auto it = akhir.begin() ; it != akhir.end() ; it++) {
        pii now = *it;
        addValue(now);
    }

    //puts("FINISHED INIT");
}

void reset() {
    for(int i = 1 ; i <= n ; i++) {
        delete BIT[i];
        adj[i].clear();
    }

    akhir.clear();
    byPos.clear();
    interval.clear();

    cnt = 0;
}


int main() {
    int t; scanf("%d",&t);
    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        init();
        printf("Case #%d:\n",tc);
        queryWorker();
        reset();
    }
    return 0;
}