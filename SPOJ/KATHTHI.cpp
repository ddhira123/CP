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

const int MAXX = 1005;

struct state{
    int row;
    int col;
    int steps;
    
    state(){}
    
    state(int rr,int cc,int ss){
        row = rr;
        col = cc;
        steps = ss;
    }
};

int dist[MAXX][MAXX];
char s[MAXX][MAXX];
int r,c;
int tc;

void Read(){
    scanf("%d %d",&r,&c);
    for(int i = 0 ; i < r ; i++){
        scanf("%s",s[i]);
        for(int j = 0 ; j < c ; j++)
            dist[i][j] = INF;
    }
}

int Solve(){
    deque<state> dq;
    dq.push_front(state(0,0,0));
    dist[0][0] = 0;
    while(!dq.empty()){
        state now = dq.front();
        dq.pop_front();
        if(dist[now.row][now.col] != now.steps) continue;
        for(int i = 0 ; i < 4 ; i++){
            int nr = now.row + dx4[i];
            int nc = now.col + dy4[i];
            if(nr < 0 || nr == r || nc < 0 || nc == c) continue;
            int ns = now.steps + (s[now.row][now.col] != s[nr][nc]);
            if(ns < dist[nr][nc]){
                dist[nr][nc] = ns;
                if(ns == now.steps) dq.push_front(state(nr,nc,ns));
                else                dq.push_back(state(nr,nc,ns));
            }
        }
    }
    return dist[r - 1][c - 1];
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        Read();
        printf("%d\n",Solve());
    }
    //puts("ganteng");
    return 0;
}

