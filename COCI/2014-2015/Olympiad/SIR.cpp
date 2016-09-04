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
//nyampah
const int N = 3005;

struct point{
    LL x;
    LL y;
    int tipe;
    
    point(){
        tipe = 0;
    }
    
    bool operator ==(point other) const{
        return x == other.x && y == other.y && tipe == other.tipe;
    }
};

LL cross(point p,point q,point r){
    LL dx1 = q.x - p.x;
    LL dy1 = q.y - p.y;
    LL dx2 = r.x - p.x;
    LL dy2 = r.y - p.y;
    return dx1 * dy2 - dx2 * dy1;
}

point pivot;

bool cmp(point a,point b){
    if(cross(pivot,a,b) == 0)
        return a.tipe == 1;
    return cross(pivot,a,b) < 0;    
}

LL Area(vector<point> &v){
    LL tot = 0;
    //DEBUG;
    for(int i = 0 ; i + 1 < v.size() ; i++){
        tot += v[i].x * v[i + 1].y - v[i].y *v[i + 1].x;
        //printf("x %lld y %lld\n",v[i].x,v[i].y);
    }    
    //printf("%lld\n",abs(tot));
    return abs(tot);    
}

point ori[N];
point arr[2 * N],arr2[2 * N];
int n,m;

int main(){
    scanf("%d",&n);
    assert(n < N);
    for(int i = 0 ; i < n ; i++){
        scanf("%lld %lld",&ori[i].x,&ori[i].y);
        arr[i] = ori[i];
    }
    scanf("%d",&m);
    assert(m < N);
    for(int i = 0 ; i < m ; i++){
        scanf("%lld %lld",&arr[n + i].x,&arr[n + i].y);
        arr[n + i].tipe = 1; 
    }
    LL ans = 0;
    for(int i = 0 ; i < n ; i++){
        pivot = ori[i];
        //printf("ori %d x %lld y %lld tipe %d\n",i,ori[i].x,ori[i].y,ori[i].tipe);
        for(int j = 0 ; j < n + m ; j++)
            arr2[j] = arr[j];
        bool bol = 0;    
        for(int j = 0 ; j < n + m ; j++)
            if(pivot == arr2[j]){
                swap(arr2[j],arr2[0]);
                bol = 1;
                break;
            }    
        assert(bol);    
        sort(arr2 + 1,arr2 + n + m,cmp);
        for(int j = 1 ; j < n + m ;){
            if(arr2[j].tipe == 0)
                j++;
            else{
                int k = j;
                while(j < n + m && cross(pivot,arr2[k],arr2[j]) == 0){
                    arr2[j].tipe = 1;
                    j++;
                }
            }    
        }
        //printf("URUTAN pivot %d\n",i);
        //for(int j = 0 ; j < n + m ; j++)
        //    printf("x %lld y %lld tipe %d\n",arr2[j].x,arr2[j].y,arr2[j].tipe);        
        vector<point> hull;
        hull.pb(pivot);
        for(int j = 1 ; j < n + m ; j++)
            if(arr2[j].tipe == 1)
                break;
            else if(arr2[j].x != pivot.x || arr2[j].y != pivot.y)
                hull.pb(arr2[j]); 
        hull.pb(pivot);
        //reverse(hull.begin(),hull.end());        
        LL ret = Area(hull);
        ans = max(ans,ret); 
        
        hull.clear();  

        hull.pb(pivot);
        for(int j = n + m - 1 ; j > 0 ; j--)
            if(arr2[j].tipe == 1)
                break;
            else if(arr2[j].x != pivot.x || arr2[j].y != pivot.y)
                hull.pb(arr2[j]);
        hull.pb(pivot);
        //reverse(hull.begin(),hull.end());
        ret = Area(hull);         
        ans = max(ans,ret);                     
    }
    printf("%lld\n",ans);
    //puts("ganteng");
    return 0;
}

