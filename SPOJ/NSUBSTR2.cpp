#include <bits/stdc++.h>
using namespace std;

const int N = 500005;

char dummy[N];

string readString() {
	scanf("%s",dummy);
	return (string)dummy;
}

void checkChar(char x) {
	assert('a' <= x && x <= 'z');
}

struct AhoCorasick {
	int trie[N][26];
	int fail[N];
	int saiz;
	int ptr;

	AhoCorasick() {
		memset(trie[0],-1,sizeof trie[0]);
		saiz = 0;
		ptr = 0;
	}

	void add(string str) {
		int cur = 0;
		for(int i = 0 ; i < str.length() ; i++) {
			//checkChar(str[i]);
			int nex = str[i] - 'a';
			if(trie[cur][nex] == -1) {
				trie[cur][nex] = ++saiz;
				memset(trie[saiz],-1,sizeof trie[saiz]);
			}
			cur = trie[cur][nex];
		}
	}

	void build() {
		queue<int> q;
		fail[0] = 0;

		for(int i = 0 ; i < 26 ; i++)
			if(trie[0][i] == -1)
				trie[0][i] = 0;
			else {
				int nex = trie[0][i];
				fail[nex] = 0;
				q.push(nex);
			}

		while(!q.empty()) {
			int now = q.front();
			q.pop();

			for(int i = 0 ; i < 26 ; i++)
				if(trie[now][i] == -1)
					trie[now][i] = trie[fail[now]][i];
				else {
					int nex = trie[now][i];
					fail[nex] = trie[fail[now]][i];
					q.push(nex);
				}
		}	
	}

	void move(char x) {
		//checkChar(x);
		ptr = trie[ptr][x - 'a'];
	}

	int getIndex(string str) {
		int cur = 0;
		for(int i = 0 ; i < str.length() ; i++) {
			//checkChar(str[i]);
			cur = trie[cur][str[i] - 'a'];
		}
		return cur;
	}

} aho;

int BIT[N];
vector<int> chld[N];
int in[N];
int ot[N];
int cnt;
string t;
string arr[N];
int n,a,b;

void dfs(int now) {
	in[now] = ++cnt;
	for(int nex : chld[now]) {
		dfs(nex);
	}
	ot[now] = cnt;
}

void update(int x,int val) {
	for(; x <= cnt ; x += x & -x)
		BIT[x] += val;
}

int query(int x) {
	int ret = 0;
	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}
	return ret;
}

void makeTree() {
	for(int i = 1 ; i <= aho.saiz ; i++)
		chld[aho.fail[i]].push_back(i);
	dfs(0);
}

void read() {
	t = readString();
	scanf("%d %d %d",&n,&a,&b);
	for(int i = 0 ; i < n ; i++)
		arr[i] = readString();
}

void build() {
	for(int i = 0 ; i < n ; i++)
		aho.add(arr[i]);
	aho.build();
	makeTree();	
}

void solve() {
	for(int i = 0 ; i < t.length() ; i++) {
		aho.move(t[i]);
		update(in[aho.ptr],1);	
	}
	for(int i = 0 ; i < n ; i++) {
		int idx = aho.getIndex(arr[i]);
		int ans = query(ot[idx]) - query(in[idx] - 1);

		printf("%d\n",ans);

		aho.move('a' + ((ans * a + b) % 26));
		update(in[aho.ptr],1);
	}
}

int main() {
	read();
	build();
	solve();
	return 0;
}