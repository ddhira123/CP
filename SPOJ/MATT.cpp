#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int SIZE = 161;
const int N = 10;
const LL MOD = (LL)1e9 + 7;

struct matrix{
    LL mat[SIZE][SIZE];
    
    matrix(){
        memset(mat,0,sizeof mat);
    }
    
    matrix operator *(matrix other) const{
        matrix res;
        for(int i = 0 ; i < SIZE ; i++)
            for(int j = 0 ; j < SIZE ; j++)
                for(int k = 0 ; k < SIZE ; k++)
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
        return res;            
    }
    
    matrix operator ^(int po) const{
        matrix res;
        matrix base;
        for(int i = 0 ; i < SIZE ; i++){
            res.mat[i][i] = 1;
            for(int j = 0 ; j < SIZE ; j++)
                base.mat[i][j] = mat[i][j];
        }
        int lol = 0;
        for(int i = 0 ; po > 0 ; i++){
            if(po & 1){
                res = res * base;
            }
            base = base * base;
            po >>= 1;
        }
        return res;
    }
} ans;

int ID(int pos,int water,int food){
    if(food < 0 || water < 0) return -1;
    return food + 4 * water + 16 * pos;
}

int P[N],W[N],F[N];
int n,s,e,h,m,mf,mw;

void add(int u,int v){
    for(int times = 0 ; times < 2 ; times++){
        for(int food = 0 ; food < 4 ; food++)
            for(int water = 0 ; water < 4 ; water++){
                int nf = food,nw = water;
                if(F[v])
                    nf = mf - 1;
                else
                    nf--;
                if(W[v])
                    nw = mw - 1;
                else
                    nw--;
                int fr = ID(u,water,food);
                int to = ID(v,nw,nf);
                if(to != -1){
                    ans.mat[fr][to] = 1;
                }                    
            }
        swap(u,v);
    }
}

void print(){
    for(int i = 0 ; i < n ; i++){
        for(int water = 0 ; water < mw ; water++)
            for(int food = 0 ; food < mf ; food++){
                printf("%d %d %d ID %d\n",i,water,food,ID(i,water,food));
                for(int i2 = 0 ; i2 < n ; i2++)
                    for(int w2 = 0 ; w2 < mw ; w2++)
                        for(int f2 = 0 ; f2 < mf ; f2++){
                            printf("%d %d %d ID %d val %lld\n",i2,w2,f2,ID(i2,w2,f2),ans.mat[ID(i,water,food)][ID(i2,w2,f2)]);
                        }
            }
    }        
}

int main(){
    scanf("%d %d %d",&n,&m,&h);
    scanf("%d %d %d %d",&s,&e,&mf,&mw);
    for(int i = 0 ; i < n ; i++)
        scanf("%d %d %d",&F[i],&W[i],&P[i]);
    for(int i = 0 ; i < m ; i++){
        int u,v;
        scanf("%d %d",&u,&v);
        u--; v--;
        add(u,v);
    }    
        
    s--;
    e--;
    h++;
    
    int source = ID(s,mw - 1,mf - 1);
    int sink = ID(e,mw - 1,mf - 1);
    ans.mat[sink][SIZE - 1] = 1;
    ans.mat[SIZE - 1][SIZE - 1] = 1;
    ans = ans^(h);


    printf("%lld\n",ans.mat[source][SIZE - 1]);
    return 0;
}
