#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <bitset>
#include <cassert>
//Because defining using namespace std is too mainstream
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<string,string> pss;
typedef pair<int,double> pid;
typedef pair<int,LL> pil;
typedef pair<LL,LL> pll;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define TIE cin.tie(0)
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")

#ifdef _WIN32
    #define getchar_unlocked getchar
#endif

#define g getchar_unlocked

int dx8[8]={-1,-1,0,1,1,1,0,-1},dx4[4]={-1,0,1,0};
int dy8[8]={0,-1,-1,-1,0,1,1,1},dy4[4]={0,-1,0,1};

inline void open(string name){
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

inline void close(){
    fclose(stdin);
    fclose(stdout);
}

inline int io(){
    register char c;
    while(1){
        c = g();
        if(c != '\n' && c != ' ') break;
    }
    int res = 0, sign = 1;
    if(c=='-') sign = -1;
    else       res = c-'0';
    while(1){
        c = g();
        if(c == ' ' || c == '\n' || c == EOF) break;
        res = (res << 3) + (res << 1) + c - '0';
    }
    return res * sign;
}

///////////////////////////////////////////////////
//////            End of Template            /////
/////////////////////////////////////////////////

const int N = 1000005;

struct node{
    int f1;
    int f2;
    int sum;
    
    node(){
        f1 = f2 = 0;
        sum = 0;
    }
};

int mat[N][2][2];
int fibo[N];
int n,q;
node stree[4 * N];

void Precompute(){
    mat[0][0][0] = mat[0][1][1] = 1;
    mat[1][0][0] = mat[1][0][1] = mat[1][1][0] = 1;
    fibo[0] = 0;
    fibo[1] = 1;
    for(int i = 2 ; i <= n + 2 ; i++){
        for(int j = 0 ; j < 2;  j++)
            for(int k = 0 ; k < 2 ; k++)
                for(int l = 0 ; l < 2 ; l++)
                    mat[i][j][k] = ((LL)mat[i][j][k] + (LL)mat[1][j][l] * (LL)mat[i - 1][l][k]) % MOD;
        
        fibo[i] = fibo[i - 1] + fibo[i - 2];
        if(fibo[i] >= MOD)
            fibo[i] -= MOD;            
    }
}

pii Eval(int id,int k){ // raise to kth power
    LL nf1,nf2,tf1,tf2;
    nf1 = nf2 = 0;
    tf1 = stree[id].f1;
    tf2 = stree[id].f2;
    nf2 = tf2 * (LL)mat[k][0][0] + tf1 * (LL)mat[k][0][1];
    nf1 = tf2 * (LL)mat[k][1][0] + tf1 * (LL)mat[k][1][1];
    nf2 %= MOD;
    nf1 %= MOD;
    return mp(nf1,nf2);
}

void Propagate(int id,int l,int r){
    int chld = id << 1, m = (l + r) >> 1;
    
    stree[chld].f1 += stree[id].f1;
    if(stree[chld].f1 >= MOD) stree[chld].f1 -= MOD;
    if(m != l){
        stree[chld].f2 += stree[id].f2;
        if(stree[chld].f2 >= MOD) stree[chld].f2 -= MOD;    
    }
    
    pii tmp = Eval(id,m + 1 - l);
    stree[chld + 1].f1 += tmp.fi;
    if(stree[chld + 1].f1 >= MOD) stree[chld + 1].f1 -= MOD;
    if(m + 1 != r){
        stree[chld + 1].f2 += tmp.se;
        if(stree[chld + 1].f2 >= MOD) stree[chld + 1].f2 -= MOD;    
    }
    
    stree[id].f1 = stree[id].f2 = 0;    
}

void Upd(int id,int l,int r){
    int chld = id << 1, m = (l + r) >> 1;
   
    stree[id].sum = stree[chld].sum + stree[chld + 1].sum;
    if(stree[id].sum >= MOD) stree[id].sum -= MOD;
    
    pii tmp = Eval(chld,m - l + 2);
    stree[id].sum += tmp.fi - stree[chld].f2;
    if(stree[id].sum >= MOD) stree[id].sum -= MOD;
    if(stree[id].sum < 0) stree[id].sum += MOD;
    
    tmp = Eval(chld + 1,r - m + 1);
    stree[id].sum += tmp.fi - stree[chld + 1].f2;
    if(stree[id].sum >= MOD) stree[id].sum -= MOD;
    if(stree[id].sum < 0) stree[id].sum += MOD;      
}

void Update(int id,int l,int r,int x,int y){
    if(x <= l && r <= y){
        stree[id].f1 += fibo[l - x + 1];
        if(stree[id].f1 >= MOD) stree[id].f1 -= MOD;
        
        if(l != r){
            stree[id].f2 += fibo[l - x + 2];
            if(stree[id].f2 >= MOD) stree[id].f2 -= MOD;
        }
    }
    else{
        int chld = id << 1, m = (l + r) >> 1;
        Propagate(id,l,r);
        if(x <= m)  Update(chld,l,m,x,y);
        if(y > m)   Update(chld + 1,m + 1,r,x,y);
        Upd(id,l,r);
    }
}

int Query(int id,int l,int r,int x,int y){
    int res = 0;
    if(x <= l && r <= y){
        pii tmp = Eval(id,r - l + 2);
        res = stree[id].sum + tmp.fi;
        if(res >= MOD)
            res -= MOD;
        res -= stree[id].f2;
        if(res < 0)
            res += MOD;    
    }
    else{
        int chld = id << 1, m = (l + r) >> 1;
        Propagate(id,l,r);
        Upd(id,l,r);
        if(x <= m)  res += Query(chld,l,m,x,y);
        if(y > m)   res += Query(chld + 1,m + 1,r,x,y);
        if(res >= MOD)
            res -= MOD;
    }
    return res;
}

int main(){
    //scanf("%d %d",&n,&q);
    n = io(); q = io();
    Precompute();
    for(int i = 1 ; i <= q ; i++){
        int opt,a,b;
        //scanf("%d %d %d",&opt,&a,&b);
        opt = io(); a = io(); b = io();
        if(opt == 0)
            Update(1,1,n,a,b);
        else
            printf("%d\n",Query(1,1,n,a,b));    
    }
    //puts("ganteng");
    return 0;
}
