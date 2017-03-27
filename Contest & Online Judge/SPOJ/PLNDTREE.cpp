#include <bits/stdc++.h>
using namespace std;

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
    else       res = c-'0';
    while(1){
        c = g();
        if(c == ' ' || c == '\n' || c == EOF) break;
        res = (res << 3) + (res << 1) + c - '0';
    }
    return res * sign;
}

const int N = 100005;

int BIT[N];
int in[N],ot[N];
vector<int> adj[N];
int sz;
int n,q;
char s[N];

void dfs(int now,int prv) {
	in[now] = ++sz;
	
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		dfs(nex,now);
	}
	
	ot[now] = sz;
}

void update(int x,int val) {
	val = 1 << val;
	for(; x <= n ; x += x & -x)
		BIT[x] ^= val;
}

int query(int x) {
	int res = 0;
	while(x) {
		res ^= BIT[x];
		x -= x & -x;
	}
	return res;
}

int main() {
	//scanf("%d",&n);
	n = io();
	for(int i = 1 ; i < n ; i++) {
		int u,v;
		//scanf("%d %d",&u,&v);
		u = io(); v = io();
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dfs(1,0);
	//scanf("%s",s);
	for(int i = 0 ; i < n ; i++)
		s[i] = g();
	//s[n] = '\0';
	//printf("%s",s);	
	for(int i = 1 ; i <= n ; i++)
		update(in[i],s[i - 1] - 'a');
	
	//scanf("%d",&q);
	q = io();
	for(int i = 0 ; i < q ; i++) {
		int tipe,x;
		//scanf("%d %d",&tipe,&x);
		tipe = io(); x = io();
		if(tipe == 1) {
			int res = query(ot[x]) ^ query(in[x] - 1);
			printf("%s\n", __builtin_popcount(res) <= 1 ? "YES" : "NO");
		}
		else {
			char ch[3];
			//scanf("%s",ch);
			ch[0] = g();
			update(in[x],s[x - 1] - 'a');
			s[x - 1] = ch[0];
			update(in[x],s[x - 1] - 'a');
		}
	}	
	return 0;
}