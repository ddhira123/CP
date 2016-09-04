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

const int MAXN = 1000001;


int next[MAXN];
char s[MAXN],t[MAXN];
int back[MAXN];
vector<int> bisa;
bool ada[MAXN];
int lens,lent;
int tc,q;

void Preprocess(){
    lens = strlen(s);
    for(int i = 0 ; i < bisa.size() ; i++){
        ada[bisa[i]] = 0;
    }
    bisa.clear();
    
    lent = strlen(t);
    back[0] = -1;
    int i = 0, j = -1;
    while(i < lent){
        while(j >= 0 && t[i] != t[j]) j = back[j];
        i++; j++;
        back[i] = j;
    }
}

void MakeNext(){
    int j = 0,k = 0;
    int las = 0;
    while(j < lens){
        while(k >= 0 && s[j] != t[k]) k = back[k];
        j++; k++;
        if(k == lent){
            ada[j - lent] = 1;
            bisa.pb(j - lent);
            k = back[k];
        }
    }    
    
    bisa.pb(lens);
    j = 0;
    for(int i = 0 ; i < bisa.size() ; i++){
        while(j < bisa[i]){
            next[j] = bisa[i];
            j++;
        }
        j = bisa[i] + 1;
    }
    j = 0;
    for(int i = 0 ; i + 1 < bisa.size() ; i++){
        while(bisa[j] != lens && bisa[j] - bisa[i] < lent)
            j++;  
        next[bisa[i]] = bisa[j];    
    }
    
}

int Query(int l,int r){
    if(!ada[l]) l = next[l];
    if(l + lent - 1 > r) return 0;
    r = r - lent + 1;
    int ans = 0;
    while(l <= r){
        ans++;
        l = next[l];
    }
    return ans;
}

int main(){
    scanf("%d",&tc);
    for(int T = 1; T <= tc ; T++){
        scanf("%s",s);
        scanf("%s",t);
        Preprocess();
        MakeNext();
        printf("Case %d:\n",T);
        scanf("%d",&q);
        while(q--){
            int l,r;
            scanf("%d %d",&l,&r);
            printf("%d\n",Query(l,r));
        }
    }
    //puts("ganteng");
    return 0;
}

