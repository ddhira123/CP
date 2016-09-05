#include <bits/stdc++.h>
using namespace std;

const int N = 505;

struct node{
    int maks;
    int mins;
    
    node(){
        maks = -(int)(1e9);
        mins = -maks;
    }
    
    node operator +(node other) const{
        node res;
        res.maks = max(maks,other.maks);
        res.mins = min(mins,other.mins);
        return res;
    }
};

int arr[N][N];
node stree[4 * N][4 * N];
int row,col;

void build2(int id,int id2,int leaf,int c1,int c2){
    if(c1 == c2){
        if(leaf){
            stree[id][id2].maks = stree[id][id2].mins = arr[leaf][c1];
        } 
        else{
            int chld = id << 1;
            stree[id][id2] = stree[chld][id2] + stree[chld + 1][id2];  
        }
    }
    else{
        int chld = id2 << 1;
        int m = (c1 + c2) >> 1;
        build2(id,chld,leaf,c1,m);
        build2(id,chld + 1,leaf,m + 1,c2);
        stree[id][id2] = stree[id][chld] + stree[id][chld + 1]; 
    }
}

void build(int id,int r1,int r2){
    if(r1 == r2){
        build2(id,1,r1,1,col);    
    }
    else{
        int chld = id << 1;
        int m = (r1 + r2) >> 1;
        build(chld,r1,m);
        build(chld + 1,m + 1,r2);
        build2(id,1,0,1,col);
    }
}

void update2(int id,int id2,int leaf,int c1,int c2,int cc,int val){
    if(c1 == c2){
        if(leaf)
            stree[id][id2].maks = stree[id][id2].mins = val;
        else{
            int chld = id << 1;
            stree[id][id2] = stree[chld][id2] + stree[chld + 1][id2];
        } 
    }       
    else{
        int chld = id2 << 1;
        int m = (c1 + c2) >> 1;
        if(cc <= m) update2(id,chld,leaf,c1,m,cc,val);
        else        update2(id,chld + 1,leaf,m + 1,c2,cc,val); 
        stree[id][id2] = stree[id][chld] + stree[id][chld + 1];
    }     
}

void update(int id,int r1,int r2,int rr,int cc,int val){
    if(r1 == r2){
        update2(id,1,r1,1,col,cc,val);
    }
    else{
        int chld = id << 1;
        int m = (r1 + r2) >> 1;
        if(rr <= m) update(chld,r1,m,rr,cc,val);
        else        update(chld + 1,m + 1,r2,rr,cc,val);
        update2(id,1,0,1,col,cc,val);
    }
}

node query2(int id,int id2,int c1,int c2,int qc1,int qc2){
    if(qc1 <= c1 && c2 <= qc2)
        return stree[id][id2];
    else{
        node res;
        int chld = id2 << 1;
        int m = (c1 + c2) >> 1;
        if(qc1 <= m) res = res + query2(id,chld,c1,m,qc1,qc2);
        if(qc2 > m)  res = res + query2(id,chld + 1,m + 1,c2,qc1,qc2);
        return res;
    }    
}

node query(int id,int r1,int r2,int qr1,int qr2,int qc1,int qc2){
    if(qr1 <= r1 && r2 <= qr2)
        return query2(id,1,1,col,qc1,qc2);
    else{
        node res;
        int chld = id << 1;
        int m = (r1 + r2) >> 1;
        if(qr1 <= m) res = res + query(chld,r1,m,qr1,qr2,qc1,qc2);
        if(qr2 > m)  res = res + query(chld + 1,m + 1,r2,qr1,qr2,qc1,qc2);
        return res;
    }    
}

void solve(){
    int q;
    scanf("%d",&q);
    for(int i = 0 ; i < q ; i++){
        char opt[5];
        scanf("%s",opt);
        if(opt[0] == 'q'){
            int r1,r2,c1,c2;
            scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
            node res = query(1,1,row,r1,r2,c1,c2);
            printf("%d %d\n",res.maks,res.mins);
        }
        else{
            int r,c,val;
            scanf("%d %d %d",&r,&c,&val);
            update(1,1,row,r,c,val);
        }
    }
}

int main(){
    scanf("%d",&row);
    col = row;
    for(int i = 1 ; i <= row ; i++)
        for(int j = 1 ; j <= col ; j++)
            scanf("%d",&arr[i][j]);
    if(row)
        build(1,1,row);
    solve();            
    return 0;
}
