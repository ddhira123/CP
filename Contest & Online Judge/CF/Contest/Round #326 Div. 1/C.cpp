#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 100005;

struct fenwick{
	vector< priority_queue<int> > stree;
	int sz;
	
	fenwick(int _sz){
		sz = _sz;
		stree.resize(4 * sz);
		for(int i = 0 ; i < 4 * sz ; i++)
			assert(stree[i].empty());
	}
	
	void update(int x,int val){
		update(1,1,sz,x,val);
	}
	
	void update(int id,int l,int r,int x,int val){
		assert(id < 4 * sz);
		stree[id].push(val);
		if(stree[id].size() > 10){
			stree[id].pop();			
		}	
		if(l < r){
			int mid = (l + r) / 2;
			if(x <= mid) update(id * 2,l,mid,x,val);
			else		 update(id * 2 + 1,mid + 1,r,x,val);
		}	
	}
	
	priority_queue<int> query(int l,int r,int lim){
		return query(1,1,sz,l,r,lim);
	}
	
	priority_queue<int> query(int id,int l,int r,int x,int y,int lim){
		if(x <= l && r <= y)
			return stree[id];
		else{
			int mid = (l + r) / 2;
			int chld = id << 1;
			priority_queue<int> res,tmp;
			assert(res.empty() && tmp.empty());
			if(x <= mid){
				tmp = query(chld,l,mid,x,y,lim);
				int iter = 0;
				while(!tmp.empty() && iter < lim){
					res.push(tmp.top());
					tmp.pop();
					if(res.size() > lim) res.pop();
				}
			}		
			if(y > mid){
				tmp = query(chld + 1,mid + 1,r,x,y,lim);
				int iter = 0;
				while(!tmp.empty() && iter < lim){
					res.push(tmp.top());
					tmp.pop();
					if(res.size() > lim) res.pop();
				}
			}						
			return res;
		}	
	}
};

int heavy[N];
int idx[N], pos[N];
int depth[N];
int sz[N];
int head[N];
int par[N];
vector<fenwick> hld;
vector<int> adj[N];
vector<int> inside[N];
int n,m,q;

void dfs(int now){
	sz[now] = 1;
	heavy[now] = -1;
	for(int nex : adj[now]){
		if(depth[nex] != -1) continue;
		depth[nex] = depth[now] + 1;
		par[nex] = now;
		dfs(nex);
		if(heavy[now] == -1 || sz[heavy[now]] < sz[nex]){
			heavy[now] = nex;
			//printf("%d -> %d\n",now,nex);
		}	
		sz[now] += sz[nex];
	}
}

void build(){
	memset(depth,-1,sizeof depth);
	depth[1] = 0;
	dfs(1);
	int cnt = 0;
	//	printf("%d -> %d\n",i,heavy[i]);
	for(int i = 1 ; i <= n ; i++)
		if(i == 1 || heavy[par[i]] != i){
			int in = 0;
			head[cnt] = i;
			for(int j = i ; j != -1 ; j = heavy[j]){
				in++;
				pos[j] = in;
				idx[j] = cnt;
				//printf("%d -> \n",j);
			}
			hld.pb(fenwick(in));
			in = 0;
			for(int j = i ; j != -1 ; j = heavy[j]){
				in++;
				for(int x : inside[j])
					hld[cnt].update(in,x);	
			}
			//printf("%d finished\n",cnt);
			cnt++;
		}	
}

priority_queue<int> query(int u,int v,int k){
	//printf("query %d %d %d\n",u,v,k);
	priority_queue<int> ans;
	while(idx[u] != idx[v]){
		int hu = head[idx[u]],hv = head[idx[v]];
		if(depth[hu] < depth[hv])
			swap(u,v);
		priority_queue<int> temp = hld[idx[u]].query(1,pos[u],k);
		while(!temp.empty()){
			ans.push(temp.top());
			//printf("%d\n",temp.top());
			temp.pop();
			if(ans.size() > k) ans.pop();
		}	
		//printf("haha %d %d %d %d\n",u,v);
		u = par[head[idx[u]]];
	}
	//printf("%d %d\n",u,v);	
	assert(u != 0 && v != 0 && idx[u] == idx[v]);
	priority_queue<int> temp = hld[idx[u]].query(min(pos[u],pos[v]),max(pos[u],pos[v]),k);
	while(!temp.empty()){
		ans.push(temp.top());
		//printf("%d\n",temp.top());
		temp.pop();
		if(ans.size() > k) ans.pop();
	}	
	return ans;
}

int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i = 1 ; i < n ; i++){
		int u,v;
		scanf("%d %d",&u,&v);
		adj[u].pb(v);
		adj[v].pb(u);
		//printf("add %d %d\n",u,v);
	}
	for(int i = 1 ; i <= m ; i++){
		int x;
		scanf("%d",&x);
		inside[x].pb(i);
	}
	build();
	for(int i = 0 ; i < q ; i++){
		int u,v,k;
		scanf("%d %d %d",&u,&v,&k);
		assert(k != 0);
		priority_queue<int> ans = query(u,v,k);
		printf("%d",(int)ans.size());
		vector<int> haha;
		while(!ans.empty()){
			haha.pb(ans.top());
			ans.pop();
		}
		reverse(haha.begin(),haha.end());
		for(int x : haha)
			printf(" %d",x);
		puts("");
	}
	return 0;
}
