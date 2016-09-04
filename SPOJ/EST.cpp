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

const int N = 2005;
const int K = 30;

int cost[N][N];
int dp[K][N];
int stek[N];
int tp;
int arr[N];
int n,k;

int DP(){
    for(int i = 1 ; i <= n ; i++)
        dp[0][i] = INF;
    dp[0][n + 1] = 0;
    for(int i = 1 ; i <= k ; i++){
        int j = n + 1;
        while(n + 1 - j < i){
            dp[i][j] = INF;
            j--;
        }
        tp = 0;
        stek[++tp] = j + 1;
        while(j >= 1){
            dp[i][j] = INF;
            for(int l = 1 ; l <= tp ; l++)
                dp[i][j] = min(dp[i][j],cost[j][stek[l] - 1] + dp[i - 1][stek[l]]);
            while(tp > 1 && dp[i - 1][j] <= dp[i - 1][stek[tp]]){
                //printf("%d %d : %d <= %d %d : %d\n",i - 1,j,dp[i - 1][j],i - 1,stek[tp],dp[i - 1][stek[tp]]);
                tp--;
            }    
            stek[++tp] = j;    
            j--;    
        }
    }    
    return dp[k][1];
}

void Calculate(){
    for(int i = 1 ; i <= n ; i++){
        priority_queue<int> les,mor;
        int totles = 0,totmor = 0;
        for(int j = i ; j <= n ; j++){
            if((j - i) & 1){
                mor.push(-arr[j]);
                totmor += arr[j];
            }    
            else{
                les.push(arr[j]);
                totles += arr[j];
            }        
            while(!mor.empty() && -mor.top() < les.top()){
                int lol = -mor.top();
                int lol2 = les.top();
                mor.pop();
                les.pop();
                mor.push(-lol2);
                les.push(lol);
                totmor += (lol2 - lol);
                totles += (lol - lol2);
            }
            int szl = (j - i + 2) / 2;
            int szm = j - i + 1 - szl;
            int med = les.top();
            cost[i][j] = szl * med - totles + totmor - szm * med;
        }
    }
}

int main(){
    scanf("%d %d",&n,&k);
    while(n | k){
        for(int i = 1 ; i <= n ; i++)
            scanf("%d",&arr[i]);
        Calculate();
        printf("%d\n",DP());    
        scanf("%d %d",&n,&k);
    }
    //puts("ganteng");
    return 0;
}

