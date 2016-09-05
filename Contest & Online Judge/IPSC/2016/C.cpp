///////////////////////////////
// Template By: Agus Sentosa //
//       17 - 5 - 2014       //
///////////////////////////////
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <utility>

//I/O
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <istream>
#include <ostream>

//Data Type
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <bitset>

//Data Type
#define pii pair<int,int>
#define pll pair<LL,LL>
#define pdd pair<double,double>
#define LL long long
#define ULL unsigned long long

//Data Type Properties
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define popb pop_back

//Macro
#define sqr(x) ((x) * (x))
#define all(v) (v).begin(),(v).end()
#define sortv(v) sort(all(v))
#define num(x) ((x)-'0')
#define ch(x) ((x)+'0')
#define bit_count __builtin_popcount
#define bit_countll __builtin_popcountll
#define THIS (*this)

//Output
#define endl '\n'

//Compiling & Debugging
#ifdef DEBUG
#define DO_IF_DEBUG_FLAG_IS_ON 1
#else
#define DO_IF_DEBUG_FLAG_IS_ON 0
#endif
#define DoDebug if(DO_IF_DEBUG_FLAG_IS_ON)

//???????????????????
#define Fokus using
#define Tahun_Terakhir namespace std;

Fokus Tahun_Terakhir;

#ifdef _WIN32
#define getchar_unlocked getchar
#endif
#define g getchar_unlocked
template<class T>
bool io(T &res){
    static char c=' ';
    while(c == ' ' || c == '\n')c = g();
    if(c == -1)return 0;
    res = num(c);
    while((c=g()) && c != ' ' && c != '\n' && c!=-1){ res = (res << 3) + (res << 1) + num(c); }
    return 1;
}

template<class T>
string inttostr(T x){
    string res="";
    while(x){
        char t=ch(x%10); x/=10; res=t+res;
    }
    return res;
}

template<class T>
T strtoint(string x){
    T res=0;
    for(int i=0;i<x.size();i++){
        res=(res<<3)+(res<<1)+num(x[i]);
    }
    return res;
}
void open(string a){
    freopen((a+".in").c_str(),"r",stdin);
    freopen((a+".out").c_str(),"w",stdout);
}
void close(){
    fclose(stdin);
    fclose(stdout);
}

//Constant
#define INF 1000000007
#define LINF 1000000000000000007ll
#define DINF 1000000000000000007.00
#define INV (-INF)
#define LINV (-LINF)
#define DINV (-DINF)
#define EPS 1e-9
#define MOD 1000000009
///////////////////////////////
//      End of Template      //
///////////////////////////////

int arr[100005];

long long modexp(LL a, LL b){
	LL res = 1;
	for(;b ; a = (a * a) % MOD, b >>= 1)
		if(b&1)
			res = (res * a) % MOD;
	return res;
}

LL fac(int x){
	LL res = 1;
	for(LL i = 1 ; i <= x ; i ++)
		res = (res * i) % MOD;
	return res;
}

long long solve(){
	int n; cin >> n;
	for(int i = 1 ; i <= n ; i ++)
		cin >> arr[i];
		
	LL res = 1, sum = 0;
		
	for(int i = 1 ; i <= n ; i ++){
		if(arr[i] != -1){
			int len = 0;
			int cur = i;
			while(arr[cur] != -1){
				int nxt = arr[cur];
				arr[cur] = -1;
				cur = nxt;
				len ++;
			}
			if(len > 1){
				LL st = len - 1;
				res = (res * len) % MOD;
				sum += st;
				res = (res * modexp(2, MOD-2)) % MOD;
			}
		}
	}
	
	res = (res * fac(sum)) % MOD;
	
	return res;
}

int main(){
	ios::sync_with_stdio(0);
	
	int t; cin >> t;
	while(t--){
		cout << solve() << endl;
	}

	return 0;
}

