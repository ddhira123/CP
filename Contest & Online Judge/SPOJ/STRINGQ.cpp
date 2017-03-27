#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL MOD = 106109099;
const int N = 50000;
const int LETTER = 26;

struct node {
	int cnt[LETTER];
	int flag;
	
	node() {
		flag = -1;
		memset(cnt,0,sizeof cnt);	
	}
	
	void set(int letter,int val) {
		flag = letter;
		memset(cnt,0,sizeof cnt);
		cnt[flag] = val;
	}
	
	node operator +(node other) const {
		node res;
		
		for(int i = 0 ; i < LETTER ; i++) {
			res.cnt[i] = cnt[i] + other.cnt[i];
		}
		
		return res;
	}
};

node stree[4 * N + 5];
char s[N + 5];
int fact[N / 2 + 5];
int inve[N / 2 + 5];
int n,q,t;

int modPow(LL base,int po) {
	LL ret = 1;
	
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	
	return ret;
}

void precompute() {
	fact[0] = inve[0] = 1;
	for(int i = 1 ; i <= N / 2 ; i++) {
		fact[i] = ((LL)fact[i - 1] * i) % MOD;
		inve[i] = modPow(fact[i],MOD - 2);
	}
	//puts("precompute finished");
}

void build(int id,int l,int r) {
	if(l == r) {
		stree[id].set(s[l - 1] - 'a',1);
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;
		
		build(chld,l,m);
		build(chld + 1,m + 1,r);
		
		stree[id] = stree[chld] + stree[chld + 1];
	}
}

void propagate(int id,int l,int r) {
	if(stree[id].flag == -1) return;
	
	int chld = id << 1;
	int m = (l + r) / 2;
	int flag = stree[id].flag;
	
	stree[chld].set(flag,m - l + 1);
	stree[chld + 1].set(flag,r - m);
}

void update(int id,int l,int r,int x,int y,int flag) {
	if(x <= l && r <= y) {
		stree[id].set(flag,r - l + 1);
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;
		
		propagate(id,l,r);
		if(x <= m)	update(chld,l,m,x,y,flag);
		if(y > m)	update(chld + 1,m + 1,r,x,y,flag);
		
		stree[id] = stree[chld] + stree[chld + 1];
	}
}

node query(int id,int l,int r,int x,int y) {
	if(x <= l && r <= y) {
		return stree[id];
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;
		
		propagate(id,l,r);
		node res;
		if(x <= m)	res = res + query(chld,l,m,x,y);
		if(y > m)	res = res + query(chld + 1,m + 1,r,x,y);
		
		stree[id] = stree[chld] + stree[chld + 1];
		
		return res;
	}
}

void printFinal(int id,int l,int r) {
	if(l == r) {
		printf("%c",stree[id].flag + 'a');
	}
	else {
		int chld = id << 1;
		int m = (l + r) / 2;
		
		propagate(id,l,r);
		printFinal(chld,l,m);
		printFinal(chld + 1,m + 1,r);
	}
}

void updater(node upd,int st) {
	for(int i = 0 ; i < LETTER ; i++)
		if(upd.cnt[i] > 0) {
			update(1,1,n,st,st + upd.cnt[i] - 1,i);
			st += upd.cnt[i];
		}
}

int main() {
	precompute();
	scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%s",s);
		n = strlen(s);
		
		build(1,1,n);
		//puts("build finished");
		
		scanf("%d",&q);
		
		while(q--) {
			char opt[3];
			int a,b;
			node ret;
			
			scanf("%s %d %d",opt,&a,&b);
			assert(a <= b);
			
			ret = query(1,1,n,a,b);	
			
			if(opt[0] == 'U')
				updater(ret,a);
			else {
				int ans = fact[(b - a + 1) / 2];
				int oddCount = 0;
				
				for(int i = 0 ; i < LETTER ; i++) {
					int cnt = ret.cnt[i];
					ans = ((LL)ans * inve[cnt / 2]) % MOD;
					oddCount += (cnt & 1);
				}
				
				if(oddCount > 1)
					ans = 0;
				
				printf("%d\n",ans);	
			}	
		}
		
		printFinal(1,1,n);
		puts("");
	}
	return 0;
}