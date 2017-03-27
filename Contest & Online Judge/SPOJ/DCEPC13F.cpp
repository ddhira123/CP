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
#define MOD 1000000007
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

const int N = 200005;

struct kuery{
    int pos;
    int time;
    int id;
    int sign;
    
    kuery(){}
    
    kuery(int a,int b,int c,int d){
        pos = a;
        time = b;
        id = c;
        sign = d;
    }
    
    bool operator <(kuery other) const{
        return time < other.time;
    }
};

kuery query[2 * N];
int last_update[N];
int v[N];
int ans[N];
bool is_query[N];

int BIT[N];

vector<int> chld[N];
int in[N],ot[N];
int it[N];
int stek[N];

int n,q;

void Add(int &x,int y){
    x += y;
    if(x >= MOD) x -= MOD;
    if(x < 0) x += MOD;
}

void DFS(){
    int cnt = 0;
    int saiz = 0;
    in[1] = ++cnt;
    stek[saiz++] = 1;
    while(saiz > 0){
        int now = stek[saiz - 1];
        for(; it[now] < chld[now].size() ; ){
            int nxt = chld[now][it[now]];
            if(in[nxt] == 0){
                in[nxt] = ++cnt;
                stek[saiz++] = nxt;
                break;    
            }
            else{
                it[now]++;
            }
        }
        if(it[now] == chld[now].size()){
            ot[now] = cnt;
            saiz--;
        }
    }
}

void Update(int x,int val){
    for(; x <= n ; x += x & -x)
        Add(BIT[x],val);
}

int Query(int x){
    int res = 0;
    for(; x > 0 ; x -= x & -x)
        Add(res,BIT[x]);
    return res;    
}

void Init(){
    int kuery_size = 0;
    n = 1;
    int last = 0;
    //scanf("%d",&q);
    q = io();
    for(int i = 1 ; i <= q ; i++){
        int opt,a,b,c;
        //scanf("%d",&opt);
        opt = io();
        if(opt == 1){
            //scanf("%d %d",&a,&b);
            a = io(); b = io();
            ++n;
            last_update[n] = last;
            v[n] = b;
            chld[a].pb(n); 
        }
        else{
            //scanf("%d %d %d",&a,&b,&c);
            a = io(); b = io(); c = io();
            a = min(a,n); b = min(b,n);
            last = i;
            is_query[i] = 1;
            query[kuery_size++] = kuery(c,a - 1,i,-1);
            query[kuery_size++] = kuery(c,b,i,1);
        }
    }
    sort(query,query + kuery_size);
    DFS();
}

void Solve(){
    int kuery_size = 2 * (q - n + 1);
    int j = 0;
    for(int i = 1 ; i <= n ; i++){
        //printf("Process %d\n",i);
        while(j < kuery_size && query[j].time < i){
            int now = query[j].pos;
            int res = Query(ot[now]);
            Add(res,-Query(in[now] - 1));
            res *= query[j].sign;
            Add(ans[query[j].id],res);
            //printf("COMPLETE %d\n",j);
            j++;
        }
        Add(v[i],ans[last_update[i]]);
        Update(in[i],v[i]);
        //printf("%d val %d\n",i,v[i]);
    }

    while(j < kuery_size){
        int now = query[j].pos;
        int res = Query(ot[now]);
        Add(res,-Query(in[now] - 1));
        res *= query[j].sign;
        Add(ans[query[j].id],res);
        j++;
    }
    
    for(int i = 1 ; i <= q ; i++)
        if(is_query[i])
            printf("%d\n",ans[i]);    
}

int main(){
    Init();
    Solve();
    //puts("ganteng");
    return 0;
}
