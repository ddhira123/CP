#include <bits/stdc++.h>
using namespace std;

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
            //x -> val += value;
            //x -> sum += value;
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
            return x;
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
    
    int getKth(int kth) {
        if(GetSum(root) < kth) return -1;

        Node *now = root;
        while(now != NULL) {
            if(GetSum(now -> l) >= kth) {
                now = now -> l;
            }
            else if(GetSum(now) - GetSum(now -> r) >= kth){
                return now -> key;
            }
            else {
                kth -= (GetSum(now) - GetSum(now -> r));
                now = now -> r;
            }
        }

        assert(0);
        return -1;
    }

    int getSmaller(int x) {
        int ret = 0;
        Node *now = root;

        while(now != NULL) {
            if(now -> key >= x) {
                now = now -> l;
            }
            else {
                ret += (GetSum(now) - GetSum(now -> r));
                now = now -> r;
            }
        }

        return ret;
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

int main() {
    AVL *tree = new AVL();
    int q; scanf("%d",&q);

    while(q--) {
        char opt[5];
        int x;
        scanf("%s %d",opt,&x);

        if(opt[0] == 'I')
            tree -> Insert(x,1);
        else if(opt[0] == 'D')
            tree -> Remove(x,1);
        else if(opt[0] == 'K') {
            int ret = tree -> getKth(x);
            if(ret == -1) {
                puts("invalid");
            }
            else
                printf("%d\n",ret);
        }
        else {
            printf("%d\n",tree -> getSmaller(x));
        }
    }
    return 0;
}