#include <bits/stdc++.h>

#define __INIT_CC__ ios::sync_with_stdio(false); \
	cin.tie(0);

#ifdef __WIN32__
	char getchar_unlocked() {return getchar();}
#endif

#define FOR(_i,_n,_m) for(int (_i)=(_n),_t=(_m);_i<(_t);++(_i))
#define FORN(_i,_n,_m) for(int (_i)=(_n),_t=(_m);_i<=(_t);++(_i))
#define FORD(_i,_n,_m) for(int (_i)=(_n),_t=(_m);_i>=(_t);--(_i))
#define FORLL(_i,_n,_m) for(long long (_i)=(_n),_t=(_m);_i<(_t);++(_i))
#define FORNLL(_i,_n,_m) for(long long (_i)=(_n),_t=(_m);(_i)<=(_t);++(_i))
#define FORDLL(_i,_n,_m) for(long long (_i)=(_n),_t=(_m);(_i)>=(_t);--(_i))
#define FOREACH(_i,_a) for (__typeof(_a.begin()) _i=_a.begin();_i!=_a.end();++_i)
#define RESET(_a,_value) memset(_a,_value,sizeof(_a))
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define ff first
#define ss second
#define mp make_pair
#define SIZE(_a) (int)_a.size()
#define VSORT(_a) sort(_a.begin(),_a.end())
#define SSORT(_a,_val) sort(_a,_a+(_val))
#define ALL(_a) _a.begin(),_a.end()
#define mt make_tuple
#define _get(_tuple,_i) get<_i>(_tuple)
#define eb emplace_back
 
using namespace std;
 
const int dr[] = { 1, 0,-1, 0, 1, 1,-1,-1};
const int dc[] = { 0, 1, 0,-1, 1,-1,-1, 1};
const double eps = 1e-9;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> pll;
typedef vector<pll> vpll;
typedef vector<ll> vll;
typedef pair<double,double> pdd;
typedef vector<pdd> vpdd;
const int INF = 0x7FFFFFFF;
const ll INFLL = 0x7FFFFFFFFFFFFFFFLL;
const double pi = acos(-1);

template <class T> T take(queue<T> &O) {T tmp=O.front();O.pop();return tmp;}
template <class T> T take(stack<T> &O) {T tmp=O.top();O.pop();return tmp;}
template <class T> T take(priority_queue<T> &O) {T tmp=O.top();O.pop();return tmp;}
template <class T> inline void getint(T &num)
{
	bool neg = 0;
	num = 0;
	char c;
	while ((c = getchar_unlocked()) && (!isdigit(c) && c != '-'));
	if (c == '-')
	{
		neg = 1;
		c = getchar_unlocked();
	}
	do num = num * 10 + c - '0';
	while ((c = getchar_unlocked()) && isdigit(c));
	if (neg) num = -num;
}

template <class T> inline bool inRange(T z, T a, T b){return a <= z && z <= b;}

void OPEN(string in = "input.txt",string out = "output.txt")
{
	freopen(in.c_str(), "r", stdin);
	freopen(out.c_str(), "w", stdout);
	return ;
}

//using sokokaleb's template v3.1

#define N 250005
const int OFFSET = 252 * 500 + 10;;
int n;
vi vc[2];
bool dp[2][2 * OFFSET + 100];

int proc(const vi& vc)
{
	int tot = 0;
	dp[0][OFFSET] = 1;
	for(int i = 0 ; i < vc.size() ; i++) {
		int bit = i & 1;
		int nbit = bit ^ 1;
		int ntot = tot + abs(vc[i]);
		for(int j = -ntot ; j <= ntot ; j++)
			dp[nbit][j + OFFSET] = 0;
		for(int j = -tot ; j <= tot ; j++) {
			bool bol = dp[bit][j + OFFSET];
			dp[nbit][j + OFFSET - vc[i]] |= bol;
			dp[nbit][j + OFFSET + vc[i]] |= bol; 
		}
		tot = ntot;
	}
	int mins = 1000;
	int bit = vc.size() & 1;
	for(int i = 0 ; i <= min(1000,tot) ; i++)
		if(dp[bit][i + OFFSET] || dp[bit][OFFSET - i]) {
			mins = abs(i);
			break;
		}	
	return mins == 1000 ? -1 : mins;
}

int main(int argc, const char *argv[])
{
	__INIT_CC__
	cin >> n;
	FOR (tc, 0, n)
	{
		cin >> n;
		vc[0].clear();
		vc[1].clear();
		int dir = 0; // 0 north, 1 east, 2 south, 3 west
		FOR (i, 0, n)
		{
			int tmp;
			string s;
			cin >> tmp >> s;
			if (dir > 1) tmp = -tmp;
			
			vc[dir&1].pb(tmp);

			if (s == "L") dir = (dir + 3) & 3;
			else dir = (dir + 1) & 3;
		}
		int tmp;
		cin >> tmp;
		if (dir > 1) tmp = -tmp;
		vc[dir&1].pb(tmp);

		if (n < 3)
		{
			cout << "NO\n";
			continue;
		}

		//for (const auto& v : vc[0]) cerr << v << " ";
		//cerr << "\n";

		//for (const auto& v : vc[1]) cerr << v << " ";
		//cerr << "\n";

		ll A = proc(vc[0]);
		ll B = proc(vc[1]);
		if (A == -1LL || B == -1LL) cout << "NO\n";
		else cout << A + B << "\n";
	}
	return 0;
}
