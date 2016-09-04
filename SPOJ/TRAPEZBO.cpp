#include <cstdio>
#include <algorithm>
using namespace std;
#define fi first
#define se second
#define mp make_pair

typedef pair<int,int> pii;

#ifdef _WIN32
    #define getchar_unlocked getchar
#endif

#define g getchar_unlocked

inline int io(){
    register char c;
    while(1){
        c = g();
        if(c != '\n' && c != ' ') break;
    }
    int res = 0, sign = 1;
    if(c=='-') sign = -1;
    else res = c-'0';
    while(1){
        c = g();
        if(c == ' ' || c == '\n' || c == EOF) break;
        res = (res << 3) + (res << 1) + c - '0';
    }
    return res * sign;
}

const int MOD = 30013;
const int N = 100005;

struct Trapezoid{
    int aki;
    int bki;
    int aka;
    int bka;
    int id;
};

bool ByKa(Trapezoid a,Trapezoid b){
    return a.bka < b.bka;
}

bool ByKi(Trapezoid a,Trapezoid b){
    return a.bki < b.bki;
}

void Add(pii &x,pii &y){
    if(x.fi < y.fi)
        x = y;
    else if(x.fi == y.fi){
        x.se += y.se;
        if(x.se >= MOD)
            x.se -= MOD;
    }
}

pii BIT[N];
int list[N];
Trapezoid arr[N],arr2[N];
int n;
pii ans[N];

void Update(int x,pii val){
    for(; x <= n ; x += x & -x)
        Add(BIT[x],val);
}

pii Query(int x){
    pii res = mp(0,0);
    for(; x > 0 ; x -= x & -x)
        Add(res,BIT[x]);
    return res;
}

int ID(int x){
    int res = upper_bound(list,list + n + 1,x) - list;
    return res - 1;
}

int main(){
    //scanf("%d",&n);
    n = io();
    list[0] = -1;
    for(int i = 1 ; i <= n ; i++){
        //scanf("%d %d %d %d",&arr[i].aki,&arr[i].aka,&arr[i].bki,&arr[i].bka);
        arr[i].aki = io();
        arr[i].aka = io();
        arr[i].bki = io();
        arr[i].bka = io();
        arr[i].id = i;
        arr2[i] = arr[i];
        list[i] = arr[i].aka;
    }
    sort(arr + 1,arr + n + 1,ByKa);
    sort(arr2 + 1,arr2 + n + 1,ByKi);
    sort(list,list + n + 1);
    int it = 1;
    for(int i = 1 ; i <= n && it <= n; i++){
        while(it <= n && arr2[it].bki <= arr[i].bka){
            int idx = arr2[it].id;
            int pos = ID(arr2[it].aki);
            ans[idx] = Query(pos);
            if(ans[idx].fi == 0)
                ans[idx].se = 1;
            ans[idx].fi++;
            it++;
        }
        int idx = arr[i].id;
        int pos = ID(arr[i].aka);
        Update(pos,ans[idx]);
    }
    pii res = mp(0,0);
    for(int i = 1 ; i <= n ; i++)
        Add(res,ans[i]);
    printf("%d %d\n",res.fi,res.se);
    return 0;
}
