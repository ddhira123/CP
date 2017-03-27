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

const int N = 100005;
const int MX = 1000000;

struct kuery{
    int tipe; // -1 : delete, 1 : add,2 : query
    LL x;
    int y1;
    int y2;
    
    kuery(){}
    
    kuery(int a,LL b,int c,int d){
        tipe = a;
        x = b;
        y1 = c;
        y2 = d;
    }
    
    bool operator <(kuery other) const{
        if(x == other.x)
            return tipe < other.tipe;
        return x < other.x;    
    }
};

int BIT[MX + 5];
kuery query[4 * N];
int saiz;
int tc,n;
LL x;
int y;
char s[105];
LL ans;

void Update(int z,int val){
    for(; z <= MX ; z += z & -z)
        BIT[z] += val;
}

int Query(int z){
    int res = 0;
    for(; z > 0 ; z -= z & -z)
        res += BIT[z];
    return res;    
}

void Init(){
    ans = 0;
    saiz = 0;
    memset(BIT,0,sizeof BIT);
    scanf("%s",s);
    for(int i = 0 ; i < 2 ; i++){
        scanf("%lld %d %d",&x,&y,&n);
        char last = 'A';
        ans++;
        for(int j = 0 ; j < n ; j++){
            LL z,nx;
            int ny;
            char opt[3];
            scanf("%s %lld",opt,&z);
            if(opt[0] == 'U'){
                nx = x;
                ny = y + z;
                query[saiz++] = kuery(2,nx,y,ny);
            }
            else if(opt[0] == 'D'){
                nx = x;
                ny = y - z;
                query[saiz++] = kuery(2,nx,ny,y);
            }
            else if(opt[0] == 'L'){
                nx = x - z;
                ny = y;
                query[saiz++] = kuery(1,nx,y,y);
                query[saiz++] = kuery(-1,x + 1,y,y);
            }
            else{
                nx = x + z;
                ny = y;
                query[saiz++] = kuery(1,x,y,y);
                query[saiz++] = kuery(-1,nx + 1,y,y);
            }
            if(last != opt[0])
                ans--;
            last = opt[0];    
            x = nx;
            y = ny;
        }
    }
}

void Solve(){
    sort(query,query + saiz);
    for(int i = 0 ; i < saiz ; i++)
        if(query[i].tipe == 2){
            int res = Query(query[i].y2);
            res -= Query(query[i].y1 - 1);
            ans += res;
        }
        else
            Update(query[i].y1,query[i].tipe);
    printf("%lld\n",ans);        
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        Init();
        Solve();
    }
    //puts("ganteng");
    return 0;
}
