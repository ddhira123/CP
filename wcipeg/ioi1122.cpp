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


const int N = 150005;
const int MAXX = 392;

struct Node{
    int pos;
    int length_left;
    int need;
    
    Node(){}
};

Node bucket[MAXX][2 * MAXX];
int bucket_size[MAXX];
int arr[N];
int position[N];
int n,l,m;
int sz;
int last_bucket;

void Print(int x);

void Place(){
    int it = 0;
    for(int i = 0 ; i <= last_bucket ; i++){
        for(int j = 0 ; j < bucket_size[i] ; j++)
            arr[it++] = bucket[i][j].pos;
        bucket_size[i] = 0;    
    }
}

void Bucket_Make(int x){
    int it = bucket_size[x] - 1;
    int last = bucket[x][it].pos;
    while(it >= 0 && bucket[x][it].pos + l >= last){
        bucket[x][it].need = 1;
        bucket[x][it].length_left = bucket[x][it].pos + l - last;
        it--;
    }
    int it2 = it;
    it = bucket_size[x] - 1;
    while(it2 >= 0){
        while(bucket[x][it2].pos + l < bucket[x][it].pos)
            it--;
        bucket[x][it2].need = 1 + bucket[x][it + 1].need;
        bucket[x][it2].length_left = bucket[x][it + 1].length_left;    
        it2--;
    }
}

void Remake(){
    int idx = 0;
    for(int i = 0 ; i < n ; i++){
        if(i % sz == 0){
            Bucket_Make(idx);
            //Print(idx);
            idx++;
        }    
        bucket[idx][ bucket_size[idx] ].pos = arr[i];
        bucket_size[idx]++;    
    }
    Bucket_Make(idx);
    last_bucket = idx;
    //Print(idx);
}

void Remove(int x,int new_pos){
    int old_pos = position[x];
    position[x] = new_pos;
    int it = 1;
    while(1){
        if(bucket[it][0].pos <= old_pos && bucket[it][bucket_size[it] - 1].pos >= old_pos)
            break;
        it++;    
    }
    int it2 = 0;
    while(bucket[it][it2].pos != old_pos)
        it2++;
    while(it2 < bucket_size[it] - 1){
        swap(bucket[it][it2],bucket[it][it2 + 1]);
        it2++;
    }    
    bucket_size[it]--;
    Bucket_Make(it);
}

void Insert(int x,int new_pos){
    int it = 1;
    while(it <= last_bucket){
        if(bucket[it][0].pos > new_pos)
            break;
        it++;    
    }
    if(it > 1) it--;
    bucket[it][bucket_size[it]].pos = new_pos;
    bucket_size[it]++;
    int it2 = bucket_size[it] - 1;
    while(it2 > 0 && bucket[it][it2].pos < bucket[it][it2 - 1].pos){
        swap(bucket[it][it2],bucket[it][it2 - 1]);
        it2--;
    }
    Bucket_Make(it);
}

void Print(int x){
    printf("BUCKET NO. %d\n",x);
    for(int i = 0 ; i < bucket_size[x] ; i++)
        printf("POS %d LEN %d NEED %d\n",bucket[x][i].pos,bucket[x][i].length_left,bucket[x][i].need);
}

int Query(){
    int last = bucket[1][0].pos - 1;
    int len = 0;
    int ans = 0;
    for(int i = 1 ; i <= last_bucket ; i++){
        //Print(i);
        if(bucket_size[i] == 0) continue;
        if(bucket[i][bucket_size[i] - 1].pos <= last + len){
            len -= (bucket[i][bucket_size[i] - 1].pos - last);
        }
        else{
            int lo = 0, hi = bucket_size[i] - 1;
            while(lo < hi){
                int mi = (lo + hi) >> 1;
                if(bucket[i][mi].pos > last + len)
                    hi = mi;
                else
                    lo = mi + 1;    
            }
            ans += bucket[i][lo].need;
            len = bucket[i][lo].length_left;
        }
        last = bucket[i][bucket_size[i] - 1].pos;
    }
    return ans;
}

int main(){
    scanf("%d %d %d",&n,&l,&m);
    sz = (int)sqrt(n);
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&arr[i]);
        position[i] = arr[i];
    }
    sort(arr,arr + n);
    Remake();
    for(int i = 0 ; i < m ; i++){
        if(i % sz == 0){
            Place();
            Remake();
        }
        int x,y;
        scanf("%d %d",&x,&y);
        Insert(x,y);
        Remove(x,y);
        printf("%d\n",Query());
    }
    //puts("ganteng");
    return 0;
}

