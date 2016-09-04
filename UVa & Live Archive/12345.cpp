#include <cstdio>
#include <set>
using namespace std;

const int N = 50000;
const int MX = 1000000;

struct node{
    int sz;
    int val;
    int hi;
    int cnt;
    node *kiri,*kanan;
    
    node(int _val = 0){
        sz = 1;
        val = _val;
        hi = 0;
        cnt = 1;
        kiri = kanan = NULL;
    }
};

struct AVL{
    node *root;
    
    AVL(){
        root = NULL;
    }
    
    void Print(node *x){
        if(x == NULL)
            puts("NULL");
        else{
            printf("sz : %d\n",x -> sz);
            printf("val : %d\n",x -> val);
            printf("hi : %d\n",x -> hi);
            if(x -> kiri == NULL)
                puts("kiri NULL");
            else
                printf("kiri %d\n",x -> kiri -> val);   
            if(x -> kanan == NULL)
                puts("kanan NULL");
            else
                printf("kanan %d\n",x -> kanan -> val);                  
        }    
    }
    
    int GetHeight(node *x){
        return x == NULL ? -1 : x -> hi;
    }  
    
    int GetSize(node *x){
        return x == NULL ? 0 : x -> sz;
    }
    
    node *Update(node *x){
        if(x == NULL) return x;
        x -> hi = 1 + max(GetHeight(x -> kiri),GetHeight(x -> kanan));
        x -> sz = x -> cnt + GetSize(x -> kiri) + GetSize(x -> kanan);
        return x;
    }
    
    node *RotateRight1(node *x){
        node *tmp = x -> kiri;
        x -> kiri = tmp -> kanan;
        tmp -> kanan = x;
        x = Update(x);
        tmp = Update(tmp);
        return tmp;
    }

    node *RotateLeft1(node *x){
        node *tmp = x -> kanan;
        x -> kanan = tmp -> kiri;
        tmp -> kiri = x;
        x = Update(x);
        tmp = Update(tmp);
        return tmp;
    }    
    
    node *RotateRight2(node *x){
        x -> kiri = RotateLeft1(x -> kiri);
        x = RotateRight1(x);
        return x;
    }
    
    node *RotateLeft2(node *x){
        x -> kanan = RotateRight1(x -> kanan);
        x = RotateLeft1(x);
        return x;
    }
    
    node *Rebalance(node *x){
        if(x == NULL) return x;
        node *L = x -> kiri,*R = x -> kanan;
        //printf("rebalancing\n");
        if(GetHeight(L) - GetHeight(R) == 2){
            if(GetHeight(L -> kiri) >= GetHeight(L -> kanan))
                x = RotateRight1(x);
            else
                x = RotateRight2(x);    
        }
        else if(GetHeight(R) - GetHeight(L) == 2){
            if(GetHeight(R -> kanan) >= GetHeight(R -> kiri))
                x = RotateLeft1(x);
            else
                x = RotateLeft2(x);    
        }        
        //puts("success");
        x = Update(x);
        return x;
    }
    
    void Insert(int x){
        //printf("inserting %d\n",x);
        root = Insert(root,x);
    }
    
    node *Insert(node *now,int x){
        //Print(now);
        if(now == NULL){
            now = new node(x);
            //puts("new node created");
        }    
        else if(now -> val < x)
            now -> kanan = Insert(now -> kanan,x);
        else if(now -> val > x)
            now -> kiri = Insert(now -> kiri,x);
        else if(now -> val == x)
            now -> cnt++;               
        now = Update(now);    
        now = Rebalance(now);
        return now;                
    }
    
    node *Successor(node *x){
        while(x -> kiri != NULL) x = x -> kiri;
        return x;
    }
    
    node *Displace(node *x){
        if(x -> kiri == NULL){
            node *tmp = x -> kanan;
            delete(x);
            return tmp;
        }
        x -> kiri = Displace(x -> kiri);
        x = Update(x);
        x = Rebalance(x);
        return x;
    }
    
    void Remove(int x){
        root = Remove(root,x);
    }
    
    node *Remove(node *now,int x){
        if(now -> val < x)
            now -> kanan = Remove(now -> kanan,x);
        else if(now -> val > x)
            now -> kiri = Remove(now -> kiri,x);
        else{
            now -> cnt--;
        } 
        now = Update(now);
        now = Rebalance(now);
        return now;       
    }
    
    int Query(int x){
        node *now = root;
        int ret = 0;
        while(now != NULL){
            if(now -> val >= x){
                ret += GetSize(now) - GetSize(now -> kiri);
                now = now -> kiri;
            }
            else
                now = now -> kanan;
        }
        //printf("ret %d\n",ret);
        return ret;
    }
    
    void Debug(){
        puts("PRINTING");
        Preorder(root);
        puts("-----------");
    }
    
    void Preorder(node *now){
        if(now == NULL)
            return;
        Preorder(now -> kiri);
        printf("%d\n",now -> val);
        Print(now);
        Preorder(now -> kanan);
            
    }
};

int arr[N + 1];
int last[MX + 1];
set<int> s[MX + 1];
int nxt[N + 1];
AVL BIT[N + 1];
int n,m;

void B_Insert(int x,int val){
    for(; x <= n ; x += x & -x){
        //printf("insert at %d\n",x);
        BIT[x].Insert(val);
        //BIT[x].Debug();
    }    
}

void B_Remove(int x,int val){
    for(; x <= n ; x += x & -x){
        //printf("removing at %d val %d\n",x,val);
        BIT[x].Remove(val);
        //BIT[x].Debug();
    }    
}

int B_Query(int x,int val){
    int ret = 0;
    while(x){
        //printf("BIT no. %d\n",x);
        ret += BIT[x].Query(val);
        x -= x & -x;
    }
    return ret;
}

void Update(int pos,int new_val){
    //remove first
    set<int>::iterator it,it2;
    it = s[arr[pos]].lower_bound(pos);
    s[arr[pos]].erase(it);
    B_Remove(pos,nxt[pos]);
    if(!s[arr[pos]].empty()){
        it = s[arr[pos]].lower_bound(pos);
        if(it != s[arr[pos]].begin()){
            it2 = it;
            it--;
            int x = *it;
            B_Remove(x,nxt[x]);
            if(it2 == s[arr[pos]].end())
                nxt[x] = x + 1000000;
            else
                nxt[x] = *it2;
            B_Insert(x,nxt[x]);        
        }
    }
    //puts("remove ok");
    //insert new value
    //change old value first
    if(!s[new_val].empty()){
        it = s[new_val].lower_bound(pos);
        if(it != s[new_val].begin()){
            it--;
            int x = *it;
            //printf("x %d nxt %d\n",x,nxt[x]);
            B_Remove(x,nxt[x]);
            //puts("yes");
            nxt[x] = pos;
            B_Insert(x,nxt[x]);
            //puts("yea");
        }
    }
    //puts("second remove ok");
    s[new_val].insert(pos);
    it = s[new_val].lower_bound(pos);
    it++;
    if(it == s[new_val].end())
        nxt[pos] = pos + 1000000;
    else
        nxt[pos] = *it;
    B_Insert(pos,nxt[pos]); 
    arr[pos] = new_val;     
    //puts("insert ok");  
}

void Init(){
    scanf("%d %d",&n,&m);
    for(int i = 1 ; i <= n ; i++)
        scanf("%d",&arr[i]);
    for(int i = n ; i >= 1 ; i--){
        int x = arr[i];
        if(last[x] == 0)
            nxt[i] = i + 1000000;
        else
            nxt[i] = last[x];
        B_Insert(i,nxt[i]);
        s[x].insert(i);
        last[x] = i;        
    }    
}

void Solve(){
    while(m--){
        char opt[5];
        int x,y;
        scanf("%s %d %d",opt,&x,&y);
        x++;
        if(opt[0] == 'Q'){
            y++;
            int ans = B_Query(y - 1,y) - B_Query(x - 1,y);
            printf("%d\n",ans);
        }
        else
            Update(x,y);
    }
}

int main(){
    Init();
    Solve();
    return 0;
}
