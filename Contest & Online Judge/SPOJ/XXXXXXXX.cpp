#include <cstdio>
#include <set>
#include <map>
#include <cassert>
using namespace std;

typedef long long LL;

const int N = 50005;
const int Q = 100005;
const int INF = 1000000000;

struct AVL{
    struct Node{
        int key;
        int height;
        LL sum;
        LL val;
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
    
    AVL(){
        root = NULL;
    }
    
    int GetHeight(Node *x){
        return x == NULL ? -1 : x -> height;
    }
    
    LL GetSum(Node *x){
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
    
    void Insert(int nkey,LL value){
        root = Insert(root,nkey,value);
    }
    
    Node *Insert(Node *x,int nkey,LL value){
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
    
    void Remove(int nkey,LL value){
        root = Remove(root,nkey,value);
    }
    
    Node *Remove(Node *x,int nkey,LL value){
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
            	/*if(x -> l == NULL && x -> r == NULL)
            		x = NULL;*/
                if(x -> l != NULL && x -> r != NULL){
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
    
    LL Query(int nkey){
        LL res = 0;
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
};

map<int,int> compress;
int distinct;
set<int> pos[N + Q];
AVL BIT[N];
int arr[N];
int nxt[N];

int n,q;


void Add(int x,int nkey,LL value){
    for(; x <= n ; x += x & -x)
        BIT[x].Insert(nkey,value);
}

void Delete(int x,int nkey,LL value){
    for(; x <= n ; x += x & -x)
        BIT[x].Remove(nkey,value);
}

LL Query(int x,int y){
    LL res = 0;
    for(; x ; x -= x & -x)
        res += BIT[x].Query(y);
    return res;    
}

void Change(int place,int new_key){
    //remove first
    int idx = compress[arr[place]];
    set<int>::iterator before,now,after;
    //puts("Try deleting");
    //printf("%d nxt %d arr %d\n",place,nxt[place],arr[place]);
    Delete(place,nxt[place],arr[place]);
    //puts("Success");
    now = pos[idx].lower_bound(place);
    if(now != pos[idx].begin()){
        after = now;
        before = now;
        after++;
        before--;
        int x = *before;
        Delete(x,nxt[x],arr[x]);
        if(after == pos[idx].end())
            nxt[x] = INF;
        else
            nxt[x] = *after;
        Add(x,nxt[x],arr[x]);        
    }
    pos[idx].erase(now);
    //insert new_key
    if(compress.count(new_key) == 0)
        compress[new_key] = ++distinct;
    //puts("DEBUG");    
    arr[place] = new_key;
    idx = compress[arr[place]];
    pos[idx].insert(place);
    now = pos[idx].lower_bound(place);
    before = after = now;
    if(now != pos[idx].begin()){
        before--;
        int x = *before;
        Delete(x,nxt[x],arr[x]);
        nxt[x] = place;
        Add(x,nxt[x],arr[x]);
    }    
    after++;
    if(after == pos[idx].end())
        nxt[place] = INF;
    else
        nxt[place] = *after;
    Add(place,nxt[place],arr[place]);        
}

void Init(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++){
        scanf("%d",&arr[i]);
        if(compress.count(arr[i]) == 0)
            compress[arr[i]] = ++distinct;
        pos[compress[arr[i]]].insert(i);    
    }
    for(int i = 1 ; i <= n ; i++){
        int idx = compress[arr[i]];
        set<int>::iterator now,after;
        now = pos[idx].lower_bound(i);
        after = now;
        after++;
        if(after == pos[idx].end())
            nxt[i] = INF;
        else
            nxt[i] = *after;
        Add(i,nxt[i],arr[i]);
        //printf("i %d nxt %d\n",i,nxt[i]);        
    }
}

void Solve(){
    scanf("%d",&q);
    while(q--){
        char opt[5];
        int u,v;
        scanf("%s %d %d",opt,&u,&v);
        if(opt[0] == 'Q')
            printf("%lld\n",Query(v,v) - Query(u - 1,v));
        else
            Change(u,v);    
    }
}

int main(){
    Init();
    Solve();
    return 0;
}