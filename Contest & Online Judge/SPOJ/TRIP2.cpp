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

const int MAXX = 200005;

int pset[MAXX];
int from[MAXX], to[MAXX];
int n,m;
int deg[MAXX];
int con[MAXX];
vector<int> odd;
vector<int> candidate;
int ans[MAXX][2];
int root;

int finds(int x){
    return pset[x] == x ? x : pset[x] = finds(pset[x]);
}

void Modify(int &x,int &y,int a,int b){
    if(x > a || (x == a && y > b))
        x = a, y = b;
}

int main(){
    int tc = 0;
    while(scanf("%d %d",&n,&m) == 2){
        for(int i = 1 ; i <= n ; i++){
            pset[i] = i;
            deg[i] = 0;
        }
        for(int i = 1 ; i <= m ; i++){
            //scanf("%d %d",&from[i],&to[i]);
            from[i] = io(); to[i] = io();
            deg[from[i]]++;
            deg[to[i]]++;
            pset[finds(from[i])] = finds(to[i]);
        }
        odd.clear();
        bool ok = 1;
        root = finds(1);
        for(int i = 1 ; i <= n ; i++){
            if(deg[i] & 1)
                odd.pb(i);
            ok &= (root == finds(i));    
        }      
        //printf("%d %d\n",odd.size(),ok);
        printf("Case %d: ",++tc);  
        if(!ok || (odd.size() != 2 && odd.size() != 4))
            puts("NO");
        else if(odd.size() == 2){
            int u = odd[0],v = odd[1];
            for(int i = 1 ; i <= n ; i++){
                pset[i] = i;
                con[i] = 0;
                deg[i] = 0;
            }
            for(int i = 1 ; i <= m ; i++){
                if((from[i] == u && to[i] == v) || (from[i] == v && to[i] == u)) continue;
                if(from[i] == u || from[i] == v) con[to[i]]++;
                if(to[i] == u || to[i] == v) con[from[i]]++;
            }
            candidate.clear();
            for(int i = 1 ; i <= n ; i++)
                if(con[i] == 2){
                    candidate.pb(i);
                    ans[i][0] = ans[i][1] = -1;
                 }   
            for(int i = 1 ; i <= m ; i++){
                if((from[i] == u || from[i] == v) && con[to[i]] == 2){
                    if(ans[to[i]][0] == -1)
                        ans[to[i]][0] = i;
                    else
                        ans[to[i]][1] = i;     
                    continue;    
                }
                if((to[i] == u || to[i] == v) && con[from[i]] == 2){
                    if(ans[from[i]][0] == -1)
                        ans[from[i]][0] = i;
                    else
                        ans[from[i]][1] = i;
                    continue;         
                }
                pset[finds(from[i])] = finds(to[i]);
            }
            for(int i = 0 ; i < candidate.size() ; i++)
                deg[finds(candidate[i])]++;
            int ans0 = INF,ans1 = INF;    
            for(int i = 0 ; i < candidate.size() ; i++){
                int w = candidate[i];
                int x = finds(u), y = finds(v), z = finds(w);
                if(z == x && z == y)
                    Modify(ans0,ans1,ans[w][0],ans[w][1]);
                else if((z == x || z == y) && candidate.size() > 1){
                    Modify(ans0,ans1,ans[w][0],ans[w][1]);
                }    
                else if(deg[z] > 1)
                    Modify(ans0,ans1,ans[w][0],ans[w][1]);
            }         
            if(ans0 != INF)
                printf("YES\n%d %d\n",ans0,ans1);
            else
                puts("NO");       
        }
        else if(odd.size() == 4){
            int ans0 = INF,ans1 = INF;
            //sort(odd.begin(),odd.end());
            do{
                if(odd[0] > odd[1] || odd[2] > odd[3]) continue;
                //printf("%d %d %d %d\n",odd[0],odd[1],odd[2],odd[3]);
                int tmp = INF,tmp2 = INF;
                for(int i = 1 ; i <= n ; i++)
                    pset[i] = i;
                for(int i = 1 ; i <= m ; i++)
                    if((from[i] == odd[0] && to[i] == odd[1]) || (from[i] == odd[1] && to[i] == odd[0]))
                        tmp = i;
                    else if((from[i] == odd[2] && to[i] == odd[3]) || (from[i] == odd[3] && to[i] == odd[2]))
                        tmp2 = i;
                    else
                        pset[finds(from[i])] = finds(to[i]);       
                if(tmp > tmp2)
                    swap(tmp,tmp2);
                ok = 1;
                root = finds(1);
                for(int i = 1 ; i <= n ; i++)
                    ok &= (root == finds(i));    
                if(ok && tmp != INF && tmp2 != INF)
                    Modify(ans0,ans1,tmp,tmp2);
            }while(next_permutation(odd.begin(),odd.end()));
            if(ans0 != INF)
                printf("YES\n%d %d\n",ans0,ans1);
            else
                puts("NO");       
        }    
    }
    //puts("ganteng");
    return 0;
}
