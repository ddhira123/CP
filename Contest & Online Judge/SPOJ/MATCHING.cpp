
#include <bits/stdc++.h>
using namespace std;

const int N = 50005;

inline void io(int &ptr){
	ptr = 0;
	register char c;
	while(1){
		c = getchar_unlocked();
		if(c != '\n' && c != ' ') break;
	}
	int res = 0, sign = 1;
	if(c=='-') sign = -1;
	else res = c-'0';
	while(1){
		c = getchar_unlocked();
		if(c == ' ' || c == '\n' || c == EOF) break;
		res = (res << 3) + (res << 1) + c - '0';
	}
	ptr = res * sign;
}

int n,m;
int vis[N];
int match[N];
int used[N];
int dist[N];
vector<int> adj[N];

void BFS() {
	queue<int> q;

	for(int i = 1 ; i <= n ; i++)
		if(!used[i]) {
			q.push(i);
			dist[i] = 0;
		}
		else {
			dist[i] = -1;
		}

	while(!q.empty()) {
		int now = q.front();
		q.pop();

		for(int nex : adj[now]) {
			int matched = match[nex];

			if(matched != -1 && dist[matched] == -1) {
				dist[matched] = dist[now] + 1;
				q.push(matched);
			}
		}
	}	
}

int augment(int now) {
	vis[now] = 1;
	for(int nex : adj[now]) {
		int matched = match[nex];

		if(matched == -1 || (vis[matched] == 0 && dist[matched] == dist[now] + 1 && augment(matched))) {
			match[nex] = now;
			used[now] = 1;
			return 1;
		}
	}
	return 0;
}


int bipartiteMatching() {
	int ret = 0;
	memset(match,-1,sizeof match);
	while(1) {
		BFS();
		for(int i = 1 ; i <= n ; i++)
			vis[i] = 0;
		int add = 0;
		for(int i = 1 ; i <= n ; i++)
			if(!used[i] && augment(i)) {
				add++;
			}
		if(add == 0) {
			break;
		}	
		ret += add;
	}
	return ret;
}

int main() {
	int q;
	//io(n); io(m); io(q);
	scanf("%d %d %d",&n,&m,&q);
	for(int i = 0 ; i < q ; i++) {
		int x,y;
		//io(x); io(y);
		scanf("%d %d",&x,&y);
		adj[x].push_back(y);
	}
	printf("%d\n",bipartiteMatching());
	return 0;
}