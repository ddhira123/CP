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

const int MAXN = 55;

struct Matrix{
    LL mat[MAXN][MAXN];
    int n;
    
    Matrix(){}
    
    Matrix(int sz){
        n = sz;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < n ; j++)
                mat[i][j] = 0;
    }
    
    Matrix Identity(int sz){
        Matrix res = Matrix(sz);
        for(int i = 0 ; i < sz ; i++)
            res.mat[i][i] = 1;
        return res;    
    }
    
    Matrix operator *(Matrix other){
        Matrix res = Matrix(n);
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < n ; j++)
                for(int k = 0 ; k < n ; k++)
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
        return res;            
    }
    
    Matrix operator ^(int po){
        Matrix base = Matrix(n);
        Matrix res = Identity(n);
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < n ; j++)
                base.mat[i][j] = mat[i][j];
        while(po){
            if(po & 1) res = res * base;
            base = base * base;
            po >>= 1;
        }        
        return res;
    }
};

int tc;
int n,m,k;
LL arr[MAXN];

int main(){
    scanf("%d",&tc);
    while(tc--){
        scanf("%d %d %d",&n,&k,&m);
        for(int i = 0 ; i < n ; i++)
            scanf("%lld",&arr[i]);
        Matrix ans = Matrix(n);    
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < k ; j++){
                int pos = (i + j) % n;
                if(j & 1) ans.mat[i][pos] = -1;
                else      ans.mat[i][pos] = 1;
            }    
        for(int i = 0 ; i < n ; i += 2)
            for(int j = 0 ; j < n ; j++)
                swap(ans.mat[i][j], ans.mat[i + 1][j]);
        ans = ans ^ m;
        for(int i = 0 ; i < n ; i++){
            LL res = 0;
            for(int j = 0 ; j < n ; j++)
                res = (res + ans.mat[i][j] * arr[j]) % MOD;
            if(res < 0) res += MOD;
            printf("%lld%c",res,(i < n - 1) ? ' ' : '\n');    
        }            
    }
    //puts("ganteng");
    return 0;
}

